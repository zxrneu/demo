#ifndef ALGO_H
#define ALGO_H

#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#endif
#include <Python.h>

// Math类的方法声明
PyObject* py_add(PyObject* self, PyObject* args);
PyObject* py_sub(PyObject* self, PyObject* args);
PyObject* py_gcd(PyObject* self, PyObject* args);
PyObject* py_lcm(PyObject* self, PyObject* args);
long gcd_calc(long a, long b);

// 排序算法声明
PyObject* py_quick_sort(PyObject* self, PyObject* args, PyObject* kwargs);
PyObject* py_bubble_sort(PyObject* self, PyObject* args, PyObject* kwargs);

// 搜索算法声明
PyObject* py_linear_search(PyObject* self, PyObject* args, PyObject* kwargs);
PyObject* py_binary_search(PyObject* self, PyObject* args, PyObject* kwargs);

#endif /* ALGO_H */ 