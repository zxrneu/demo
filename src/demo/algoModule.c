// addmodule.c
#include <Python.h>
#include "algo.h"

// Math类的方法定义
static PyMethodDef MathMethods[] = {
    {"add", py_add, METH_VARARGS, "Add two numbers"},
    {"sub", py_sub, METH_VARARGS, "Sub two numbers"},
    {"gcd", py_gcd, METH_VARARGS, "GCD of two numbers"},
    {"lcm", py_lcm, METH_VARARGS, "LCM of two numbers"},
    {NULL, NULL, 0, NULL}
};

// Math类的定义
static PyTypeObject MathType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "demo.Math",
    .tp_doc = "Math operations",
    .tp_basicsize = sizeof(PyObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = MathMethods,
    .tp_new = PyType_GenericNew,
};

// 模块级方法定义
static PyMethodDef ModuleMethods[] = {
    {"bubble_sort", (PyCFunction)(void(*)(void))py_bubble_sort,
     METH_VARARGS | METH_KEYWORDS, "Bubble sort implementation"},
    {"quick_sort", (PyCFunction)(void(*)(void))py_quick_sort,
     METH_VARARGS | METH_KEYWORDS, "Quick sort implementation"},
    {"linear_search", (PyCFunction)(void(*)(void))py_linear_search,
     METH_VARARGS | METH_KEYWORDS, "Linear search implementation"},
    {"binary_search", (PyCFunction)(void(*)(void))py_binary_search,
     METH_VARARGS | METH_KEYWORDS, "Binary search implementation"},
    {NULL, NULL, 0, NULL}
};

// 模块定义
static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "demo",
    "Demo module containing math and sorting algorithms",
    -1,
    ModuleMethods,
    NULL,  // m_slots
    NULL,  // m_traverse
    NULL,  // m_clear
    NULL   // m_free
};

// 模块初始化函数
PyMODINIT_FUNC PyInit_demo(void)
{
    PyObject *m;
    
    // 准备Math类型
    if (PyType_Ready(&MathType) < 0)
        return NULL;

    // 创建模块
    m = PyModule_Create(&module);
    if (m == NULL)
        return NULL;

    // 添加Math类到模块
    Py_INCREF(&MathType);
    if (PyModule_AddObject(m, "Math", (PyObject *) &MathType) < 0) {
        Py_DECREF(&MathType);
        Py_DECREF(m);
        return NULL;
    }

    // 添加版本信息
    if (PyModule_AddStringConstant(m, "__version__", "1.0.0") < 0) {
        Py_DECREF(&MathType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}