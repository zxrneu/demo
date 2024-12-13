# Demo 包

一个用 C 语言实现的 Python 扩展包，提供高性能的数学运算、排序算法和搜索算法。

## 功能特性

- 数学运算（Math 类）
  - 加法运算
  - 减法运算
  - 最大公约数 (GCD)
  - 最小公倍数 (LCM)
- 排序算法
  - 冒泡排序
  - 快速排序
- 搜索算法
  - 线性搜索
  - 二分搜索

## 安装方式

### 方式一：使用 pip 安装（推荐）

```bash
pip install demo
```

### 方式二：使用 wheel 包安装

下载 wheel 包后本地安装：

```bash
pip install demo-1.0-*.whl
```

### 方式三：从源码构建

#### 使用 setup.py 构建（推荐给 Python 开发者）

```bash
git clone https://github.com/zxrneu/demo.git
cd demo
python setup.py build
python setup.py install
```

#### 使用 CMake 构建（适合 C/C++ 开发者）

```bash
git clone https://github.com/zxrneu/demo.git
cd demo
mkdir build && cd build
cmake ..
make
make install
```

## 开发指南

### 环境要求

- Python 3.7 或更高版本
- C 编译器 (GCC/Clang)
- CMake 3.10 或更高版本（可选，用于 CMake 构建）
- pip
- build（用于构建 wheel 包）
- twine（用于发布包）

### 构建和测试

#### 构建 wheel 包

```bash
# 安装必要的工具
pip install wheel build twine

# 运行构建脚本
chmod +x build_wheel.sh
./build_wheel.sh
```

生成的 wheel 包将位于 `dist` 目录下。

#### 发布包

发布到 PyPI：
```bash
twine upload dist/*
```

发布到测试 PyPI：
```bash
twine upload --repository-url https://test.pypi.org/legacy/ dist/*
```

#### 运行测试

```bash
python tests/test.py
```

## 使用示例

```python
from demo import (
    Math,
    bubble_sort,
    quick_sort,
    linear_search,
    binary_search
)

# 数学运算
math = Math()
print(f"5 + 3 = {math.add(5, 3)}")          # 输出: 8
print(f"10 - 4 = {math.sub(10, 4)}")        # 输出: 6
print(f"GCD(12, 18) = {math.gcd(12, 18)}")  # 输出: 6
print(f"LCM(12, 18) = {math.lcm(12, 18)}")  # 输出: 36

# 排序
numbers = [5, 2, 8, 1, 9]
sorted_bubble = bubble_sort(numbers)  # 返回: [1, 2, 5, 8, 9]
sorted_quick = quick_sort(numbers)    # 返回: [1, 2, 5, 8, 9]

# 搜索
numbers = [1, 3, 5, 7, 9]
index = linear_search(numbers, 5)     # 返回: 2
index = binary_search(numbers, 7)     # 返回: 3（要求列表已排序）
```

## 项目结构

```
demo/
├── LICENSE
├── README.md
├── MANIFEST.in          # 包含文件清单
├── setup.cfg           # 包配置
├── setup.py           # 构建脚本
├── build_wheel.sh     # wheel 包构建脚本
├── examples/          # 示例代码
│   └── basic_usage.py
├── src/               # 源代码
│   └── demo/
│       ├── __init__.py
│       ├── algo.pyi    # 类型提示
│       ├── py.typed    # 类型提示标记
│       ├── include/    # 头文件
│       ├── math/       # 数学运算
│       ├── sorting/    # 排序算法
│       └── searching/  # 搜索算法
└── tests/             # 测试代码
    └── test.py
```

## 类型提示

本包包含类型提示，完全兼容 mypy 和其他类型检查器：

```python
from demo import Math, bubble_sort, linear_search
from typing import List

def example(numbers: List[int]) -> int:
    math = Math()
    # IDE 将提供类型提示和文档
    result = math.add(5, 3)
    sorted_list = bubble_sort(numbers)
    return linear_search(sorted_list, result)
```

## 常见问题

### 常见错误

1. **构建时提示 "Python.h not found"**
   - 确保已安装 Python 开发文件
   - Ubuntu/Debian 系统：`sudo apt-get install python3-dev`
   - CentOS/RHEL 系统：`sudo yum install python3-devel`

2. **CMake 找不到 Python**
   - 设置 `Python3_ROOT_DIR` 为 Python 安装路径
   - 如果使用 conda，请在运行 cmake 前激活环境

3. **安装后导入错误**
   - 尝试重新安装包：`pip install --force-reinstall demo`
   - 检查 Python 版本兼容性

## 贡献指南

1. Fork 本仓库
2. 创建功能分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

## 版本历史

- 1.0.0
  - 初始发布
  - 基础数学运算
  - 排序算法
  - 搜索算法
  - 类型提示支持

## 作者

你的名字 - [@zxrneu](https://github.com/zxrneu)

## 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件