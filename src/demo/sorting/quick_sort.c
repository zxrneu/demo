#include "algo.h"

// 分区函数
static long partition(long arr[], long low, long high) {
    long pivot = arr[high];
    long i = (low - 1);
    
    for (long j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            long temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    long temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// 快速排序的递归实现
static void quick_sort_recursive(long arr[], long low, long high) {
    if (low < high) {
        long pi = partition(arr, low, high);
        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

// Python绑定的快速排序函数
PyObject* py_quick_sort(PyObject* self, PyObject* args, PyObject* kwargs) {
    PyObject *listObj;
    static char* kwlist[] = {"array", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!", kwlist,
                                    &PyList_Type, &listObj)) {
        return NULL;
    }

    Py_ssize_t size = PyList_Size(listObj);
    long *arr = (long *)malloc(sizeof(long) * size);
    if (arr == NULL) {
        PyErr_NoMemory();
        return NULL;
    }

    for (Py_ssize_t i = 0; i < size; i++) {
        PyObject *item = PyList_GetItem(listObj, i);
        if (!PyLong_Check(item)) {
            free(arr);
            PyErr_SetString(PyExc_TypeError, "List items must be integers");
            return NULL;
        }
        arr[i] = PyLong_AsLong(item);
    }

    quick_sort_recursive(arr, 0, size - 1);

    PyObject *sortedList = PyList_New(size);
    if (sortedList == NULL) {
        free(arr);
        return NULL;
    }

    for (Py_ssize_t i = 0; i < size; i++) {
        PyObject *num = PyLong_FromLong(arr[i]);
        if (num == NULL) {
            Py_DECREF(sortedList);
            free(arr);
            return NULL;
        }
        PyList_SET_ITEM(sortedList, i, num);
    }

    free(arr);
    return sortedList;
}
