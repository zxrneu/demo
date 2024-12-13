#!/bin/bash

# 设置颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# 默认配置
CMAKE_BUILD_TYPE="Release"
CLEAN_ONLY=0
SKIP_TESTS=0
VERBOSE=0

# 显示帮助信息
show_help() {
    echo "用法: $0 [选项]"
    echo
    echo "选项:"
    echo "  --debug        构建调试版本"
    echo "  --clean        仅清理构建文件"
    echo "  --no-tests     跳过测试"
    echo "  --verbose      显示详细输出"
    echo "  --help         显示此帮助信息"
}

# 打印带颜色的信息
info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# 检查必要的命令是否存在
check_commands() {
    info "检查必要的命令..."
    commands=("cmake" "make" "python3" "pip")
    for cmd in "${commands[@]}"; do
        if ! command -v $cmd &> /dev/null; then
            error "$cmd 未找到，请先安装"
            exit 1
        fi
    done
    success "所有必要的命令都已安装"
}

# 清理旧的构建文件
cleanup() {
    info "清理旧的构建文件..."
    
    # 如果存在构建目录，尝试卸载包
    if [ -f "build/Makefile" ]; then
        cd build
        make pip_uninstall || true  # 忽略卸载错误
        cd ..
    else
        # 如果没有构建目录，直接用 pip 卸载
        pip uninstall -y demo || true
    fi
    
    # 手动清理所有构建文件
    rm -rf build/
    rm -rf dist/
    rm -rf *.egg-info/
    rm -rf src/demo/__pycache__/
    rm -rf tests/__pycache__/
    find . -name "*.pyc" -delete
    find . -name "*.pyo" -delete
    find . -name "*.so" -delete
    find . -name "*.pyd" -delete
    
    success "清理完成"
}

# 创建并进入构建目录
setup_build_dir() {
    info "创建构建目录..."
    mkdir -p build
    cd build
    success "创建完成"
}

# 运行 CMake 配置
run_cmake() {
    info "运行 CMake 配置..."
    local cmake_args="-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
    
    if [ -n "$CONDA_PREFIX" ]; then
        info "检测到 Conda 环境: $CONDA_PREFIX"
        cmake_args="$cmake_args -DPython3_ROOT_DIR=$CONDA_PREFIX"
    fi
    
    if [ $VERBOSE -eq 1 ]; then
        info "CMake 参数: $cmake_args"
    fi
    
    cmake .. $cmake_args
    
    if [ $? -ne 0 ]; then
        error "CMake 配置失败"
        exit 1
    fi
    success "CMake 配置完成"
}

# 构建项目
build_project() {
    info "构建项目..."
    local make_args="-j$(nproc)"
    
    if [ $VERBOSE -eq 1 ]; then
        make_args="$make_args VERBOSE=1"
    fi
    
    make $make_args
    if [ $? -ne 0 ]; then
        error "构建失败"
        exit 1
    fi
    success "构建完成"
}

# 安装项目
install_project() {
    info "安装项目..."
    make pip_install
    if [ $? -ne 0 ]; then
        error "安装失败"
        exit 1
    fi
    success "安装完成"
}

# 运行测试
run_tests() {
    if [ $SKIP_TESTS -eq 1 ]; then
        info "跳过测试..."
        return
    fi
    
    info "运行测试..."
    cd ..
    if [ -f "tests/test.py" ]; then
        if [ $VERBOSE -eq 1 ]; then
            PYTHONPATH=. python -X faulthandler tests/test.py
        else
            PYTHONPATH=. python -X faulthandler tests/test.py
        fi
        
        if [ $? -ne 0 ]; then
            error "测试失败"
            exit 1
        fi
        success "测试通过"
    else
        info "未找到测试文件，跳过测试"
    fi
}

# 验证安装
verify_installation() {
    info "验证安装..."
    python -c "
import demo
from pathlib import Path
site_packages = Path(demo.__file__).parent
print('包目录:', site_packages)
print('目录中的文件:', list(site_packages.glob('*')))
print('类型提示文件:', list(site_packages.glob('*.pyi')))
assert (site_packages / 'py.typed').exists(), 'py.typed 文件未找到'
assert (site_packages / 'algo.pyi').exists(), 'algo.pyi 文件未找到'
"
    if [ $? -eq 0 ]; then
        success "安装验证通过"
    else
        error "安装验证失败"
        exit 1
    fi
}

# 参数处理
while [[ $# -gt 0 ]]; do
    case $1 in
        --debug)
            CMAKE_BUILD_TYPE="Debug"
            shift
            ;;
        --clean)
            CLEAN_ONLY=1
            shift
            ;;
        --no-tests)
            SKIP_TESTS=1
            shift
            ;;
        --verbose)
            VERBOSE=1
            shift
            ;;
        --help)
            show_help
            exit 0
            ;;
        *)
            error "未知选项: $1"
            echo
            show_help
            exit 1
            ;;
    esac
done

# 主函数
main() {
    info "开始构建流程..."
    info "构建类型: ${CMAKE_BUILD_TYPE}"
    
    check_commands
    cleanup
    
    if [ $CLEAN_ONLY -eq 1 ]; then
        success "清理完成！"
        exit 0
    fi
    
    setup_build_dir
    run_cmake
    build_project
    install_project
    run_tests
    verify_installation
    
    success "构建流程完成！"
    info "你可以现在使用 demo 包了"
}

# 运行主函数
main