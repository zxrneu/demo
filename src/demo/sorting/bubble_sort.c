#include "algo.h"

PyObject* py_bubble_sort(PyObject* self, PyObject* args, PyObject* kwargs)
{
    (void)self;  // 避免未使用参数的警告
    PyObject* list;
    static char* kwlist[] = {"array", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!", kwlist, 
                                    &PyList_Type, &list)) {
        return NULL;
    }
    
    Py_ssize_t n = PyList_Size(list);
    if (n < 0) {
        return NULL;
    }
    
    // 创建新列表作为返回值
    PyObject* result = PyList_New(n);
    if (result == NULL) {
        return NULL;
    }
    
    // 复制原始列表的内容
    for (Py_ssize_t i = 0; i < n; i++) {
        PyObject* item = PyList_GetItem(list, i);
        if (!item) {
            Py_DECREF(result);
            return NULL;
        }
        Py_INCREF(item);  // 因为PyList_SET_ITEM会偷走引用
        PyList_SET_ITEM(result, i, item);
    }
    
    // 对新列表进行排序
    for (Py_ssize_t i = 0; i < n-1; i++) {
        for (Py_ssize_t j = 0; j < n-i-1; j++) {
            PyObject *a = PyList_GetItem(result, j);
            PyObject *b = PyList_GetItem(result, j+1);
            
            if (!a || !b) {
                Py_DECREF(result);
                PyErr_SetString(PyExc_RuntimeError, "Failed to get list items");
                return NULL;
            }
            
            int cmp_result = PyObject_RichCompareBool(a, b, Py_GT);
            if (cmp_result == -1) {
                Py_DECREF(result);
                return NULL;
            }
            
            if (cmp_result == 1) {
                PyObject *temp = PyList_GET_ITEM(result, j);
                PyObject *next = PyList_GET_ITEM(result, j+1);
                PyList_SET_ITEM(result, j, next);
                PyList_SET_ITEM(result, j+1, temp);
            }
        }
    }
    
    return result;
}