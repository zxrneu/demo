from typing import List, TypeVar, Optional

T = TypeVar('T', int, float)  # 用于排序函数的类型变量

class Math:
    def add(self, a: int, b: int) -> int:
        """Add two numbers.
        
        Args:
            a: First number
            b: Second number
            
        Returns:
            Sum of a and b
        """
        ...
    
    def sub(self, a: int, b: int) -> int:
        """Subtract two numbers.
        
        Args:
            a: First number
            b: Second number
            
        Returns:
            Difference of a and b
        """
        ...
    
    def gcd(self, a: int, b: int) -> int:
        """Calculate the Greatest Common Divisor of two numbers.
        
        Args:
            a: First number
            b: Second number
            
        Returns:
            Greatest Common Divisor of a and b
        """
        ...
    
    def lcm(self, a: int, b: int) -> int:
        """Calculate the Least Common Multiple of two numbers.
        
        Args:
            a: First number
            b: Second number
            
        Returns:
            Least Common Multiple of a and b
            
        Raises:
            ValueError: If GCD is 0
        """
        ...

def bubble_sort(array: List[T], /) -> List[T]:
    """Sort a list using bubble sort algorithm.
    
    Args:
        array: List to sort
        
    Returns:
        New sorted list
    """
    ...

def quick_sort(array: List[T], /) -> List[T]:
    """Sort a list using quick sort algorithm.
    
    Args:
        array: List to sort
        
    Returns:
        New sorted list
    """
    ... 

def linear_search(array: List[int], target: int) -> int:
    """Linear search in a list.
    
    Args:
        array: List to search in
        target: Value to find
        
    Returns:
        Index of target if found, -1 otherwise
    """
    ...

def binary_search(array: List[int], target: int) -> int:
    """Binary search in a sorted list.
    
    Args:
        array: Sorted list to search in
        target: Value to find
        
    Returns:
        Index of target if found, -1 otherwise
        
    Raises:
        TypeError: If list items are not integers
    """
    ... 