#include "algo.h"

extern long gcd_calc(long a, long b);

PyObject* py_lcm(PyObject* self, PyObject* args) {
    long a, b;
    if (!PyArg_ParseTuple(args, "ll", &a, &b)) {
        return NULL;
    }
    long gcd_value = gcd_calc(a, b);
    if (gcd_value == 0) {
        PyErr_SetString(PyExc_ValueError, "Cannot calculate LCM when GCD is 0");
        return NULL;
    }
    return PyLong_FromLong((a * b) / gcd_value);
} 