from setuptools import setup, Extension
import sys
from pathlib import Path

# 添加调试信息
print("Python version:", sys.version)
print("Platform:", sys.platform)

# 确保 py.typed 文件存在
Path('src/demo/py.typed').touch()

demo_module = Extension(
    'demo.demo',
    sources=[
        'src/demo/algoModule.c',
        'src/demo/math/add.c',
        'src/demo/math/sub.c',
        'src/demo/math/gcd.c',
        'src/demo/math/lcm.c',
        'src/demo/sorting/quick_sort.c',
        'src/demo/sorting/bubble_sort.c',
        'src/demo/searching/linear_search.c',
        'src/demo/searching/binary_search.c'
    ],
    include_dirs=['src/demo/include'],
    define_macros=[('PY_SSIZE_T_CLEAN', '1')],
    extra_compile_args=['-Wall', '-Wextra', '-Wno-unused-parameter']
)

setup(
    name='demo',
    version='1.0',
    description='Python package demo with C extensions',
    ext_modules=[demo_module],
    package_dir={'': 'src'},
    packages=['demo'],
    package_data={
        'demo': ['*.pyi', 'py.typed'],
    },
    zip_safe=False,
    python_requires='>=3.7'
)
