#!/bin/bash

# 设置颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

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

# 清理旧的构建文件
info "清理旧的构建文件..."
rm -rf build/
rm -rf dist/
rm -rf *.egg-info/

# 确保目录结构正确
info "设置目录结构..."
mkdir -p src/demo

# 确保必要的文件存在
info "检查必要文件..."
touch src/demo/py.typed
touch src/demo/__init__.py

# 卸载已安装的包
info "卸载已安装的包..."
pip uninstall -y demo

# 安装构建工具
info "安装构建工具..."
pip install --upgrade pip build

# 构建包
info "构建包..."
python -m build

# 安装包
info "安装包..."
pip install dist/*.whl

# 运行测试
info "运行测试..."
if [ -f "tests/test.py" ]; then
    PYTHONPATH=. python -X faulthandler tests/test.py
    if [ $? -ne 0 ]; then
        error "测试失败"
        exit 1
    fi
    success "测试通过"
else
    info "未找到测试文件，跳过测试"
fi

# 验证类型提示文件是否正确安装
info "验证类型提示文件安装..."
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

success "构建过程完成！"
info "你可以现在使用 demo 包了"
# 卸载已安装的包
info "卸载已安装的包..."
pip uninstall -y demo