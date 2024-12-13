# 这个文件可以为空，但需要存在来标记这是一个Python包 
from .demo import (
    Math,
    bubble_sort,
    quick_sort,
    linear_search,
    binary_search
)

__all__ = [
    'Math',
    'bubble_sort',
    'quick_sort',
    'linear_search',
    'binary_search'
] 