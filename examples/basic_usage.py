from demo import (
    Math,
    bubble_sort,
    quick_sort,
    linear_search,
    binary_search
)

def main():
    # Math operations
    math = Math()
    print("Math operations:")
    print(f"5 + 3 = {math.add(5, 3)}")
    print(f"10 - 4 = {math.sub(10, 4)}")
    print(f"GCD of 12 and 18 = {math.gcd(12, 18)}")
    print(f"LCM of 12 and 18 = {math.lcm(12, 18)}")
    
    # Sorting
    numbers = [5, 2, 8, 1, 9]
    print("\nSorting:")
    print(f"Original list: {numbers}")
    print(f"Bubble sort: {bubble_sort(numbers.copy())}")
    print(f"Quick sort: {quick_sort(numbers.copy())}")

    # Searching
    sorted_numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    print("\nSearching:")
    print(f"Linear search for 5: {linear_search(sorted_numbers, 5)}")  # Should print 4
    print(f"Binary search for 7: {binary_search(sorted_numbers, 7)}")  # Should print 6

if __name__ == "__main__":
    main() 