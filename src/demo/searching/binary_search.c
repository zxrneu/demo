#include "algo.h"

PyObject* py_binary_search(PyObject* self, PyObject* args, PyObject* kwargs) {
    PyObject* list;
    long target;
    static char* kwlist[] = {"array", "target", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!l", kwlist,
                                    &PyList_Type, &list, &target)) {
        return NULL;
    }
    
    Py_ssize_t size = PyList_Size(list);
    if (size < 0) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to get list size");
        return NULL;
    }
    
    Py_ssize_t left = 0;
    Py_ssize_t right = size - 1;
    
    while (left <= right) {
        Py_ssize_t mid = left + (right - left) / 2;
        PyObject* item = PyList_GetItem(list, mid);
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
            return PyLong_FromSsize_t(mid);
        }
        if (value < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return PyLong_FromLong(-1);
} 