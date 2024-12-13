#!/bin/bash

# 清理旧的构建文件
echo "清理旧的构建文件..."
rm -rf build/ dist/ *.egg-info/

# 确保目录结构正确
echo "检查目录结构..."
mkdir -p src/demo

# 确保必要的文件存在
echo "检查必要文件..."
touch src/demo/py.typed
touch src/demo/__init__.py

# 构建 wheel 包
echo "构建 wheel 包..."
python -m build --wheel

# 显示生成的文件
echo "生成的文件："
ls dist/

# 验证 wheel 包
echo "验证 wheel 包..."
pip install twine
twine check dist/*

echo "构建完成！"
echo "你可以使用以下命令安装："
echo "pip install dist/demo-1.0-*.whl"
echo
echo "或者使用以下命令上传到 PyPI："
echo "twine upload dist/*" 