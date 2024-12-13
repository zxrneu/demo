from demo import (
    Math,
    bubble_sort,
    quick_sort,
    linear_search,
    binary_search
)
import sys
import faulthandler
faulthandler.enable()

def test_math():
    print("测试数学运算...")
    try:
        math = Math()
        print(f"5 + 3 = {math.add(5, 3)}")
        print(f"12 和 18 的最大公约数是 {math.gcd(12, 18)}")
        print(f"12 和 18 的最小公倍数是 {math.lcm(12, 18)}")
    except Exception as e:
        print(f"数学运算测试失败: {e}", file=sys.stderr)
        raise

def test_sorting():
    print("\n测试排序算法...")
    try:
        numbers = [5, 2, 8, 1, 9]
        print(f"原始列表: {numbers}")
        print(f"冒泡排序: {bubble_sort(numbers)}")
        print(f"快速排序: {quick_sort(numbers)}")
    except Exception as e:
        print(f"排序测试失败: {e}", file=sys.stderr)
        raise

def test_search():
    print("\n测试搜索算法...")
    try:
        numbers = [1, 3, 5, 7, 9]
        print(f"测试列表: {numbers}")
        
        # 分步测试，每步都打印详细信息
        print("测试线性搜索...")
        result = linear_search(numbers, 5)
        print(f"线性搜索 5 的结果: {result}")
        
        print("测试二分搜索...")
        result = binary_search(numbers, 7)
        print(f"二分搜索 7 的结果: {result}")
        
    except Exception as e:
        print(f"搜索测试失败: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc()
        raise

def main():
    try:
        test_math()
        test_sorting()
        test_search()
        print("\n所有测试通过！")
    except Exception as e:
        print(f"\n测试失败: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
