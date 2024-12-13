#include "algo.h"

PyObject* py_linear_search(PyObject* self, PyObject* args, PyObject* kwargs) {
    PyObject* list;
    long target;
    static char* kwlist[] = {"array", "target", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!l", kwlist,
                                    &PyList_Type, &list, &target)) {
        return NULL;
    }
    
    // 获取列表大小
    Py_ssize_t size = PyList_Size(list);
    if (size < 0) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to get list size");
        return NULL;
    }
    
    // 线性查找
    for (Py_ssize_t i = 0; i < size; i++) {
        PyObject* item = PyList_GetItem(list, i);
        if (!item) {
            PyErr_SetString(PyExc_RuntimeError, "Failed to get list item");
            return NULL;
        }
        
        if (!PyLong_Check(item)) {
            PyErr_SetString(PyExc_TypeError, "List items must be integers");
            return NULL;
        }
        
        long value = PyLong_AsLong(item);
        if (value == target) {
            return PyLong_FromSsize_t(i);
        }
    }
    
    return PyLong_FromLong(-1);
} 