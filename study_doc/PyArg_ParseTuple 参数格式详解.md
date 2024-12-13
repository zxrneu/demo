

# PyArg_ParseTuple 参数格式详解

`PyArg_ParseTuple` 是用于解析 Python 参数的关键函数。以下是常用格式代码的详细说明：

## 基础格式代码

```c
// 基本类型
"i"    // int
"l"    // long
"f"    // float
"d"    // double
"s"    // char* (字符串)
"b"    // char (单字符)
"O"    // PyObject* (任意Python对象)
"S"    // PyStringObject*
"U"    // PyUnicodeObject*
```

## 常用组合格式

```c
"s#"   // char*, int* (字符串和长度)
"z#"   // char*, int* (可以为NULL的字符串和长度)
"O!"   // PyTypeObject*, PyObject* (特定类型的对象)
"()"   // 表示元组
"[]"   // 表示列表
"{}"   // 表示字典
```

## 示例代码

```c
static PyObject* example_function(PyObject* self, PyObject* args) {
    // 1. 基本类型解析
    int number;
    if (!PyArg_ParseTuple(args, "i", &number)) {
        return NULL;
    }

    // 2. 多参数解析
    char *string;
    double value;
    if (!PyArg_ParseTuple(args, "sd", &string, &value)) {
        return NULL;
    }

    // 3. 带长度的字符串
    char *buffer;
    Py_ssize_t length;
    if (!PyArg_ParseTuple(args, "s#", &buffer, &length)) {
        return NULL;
    }

    // 4. 特定类型对象
    PyListObject *list;
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &list)) {
        return NULL;
    }
}
```

## 可选参数

```c
// "|" 后面的参数是可选的
static PyObject* optional_args(PyObject* self, PyObject* args) {
    int required;
    int optional = 0;  // 默认值
    if (!PyArg_ParseTuple(args, "i|i", &required, &optional)) {
        return NULL;
    }
}
```

## 关键字参数

```c
static PyObject* keyword_args(PyObject* self, PyObject* args, PyObject* kwargs) {
    int x, y = 0;
    static char* kwlist[] = {"x", "y", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i|i", kwlist, 
                                    &x, &y)) {
        return NULL;
    }
}
```

## 格式代码修饰符

```c
"b"    // unsigned char
"h"    // short
"H"    // unsigned short
"i"    // int
"I"    // unsigned int
"l"    // long
"k"    // unsigned long
"L"    // long long
"K"    // unsigned long long
"n"    // Py_ssize_t
"c"    // char
"C"    // unsigned char
"f"    // float
"d"    // double
"D"    // Py_complex
"O"    // object (PyObject*)
"S"    // string object (PyStringObject*)
"U"    // Unicode object (PyUnicodeObject*)
"y"    // bytes object
```

## 错误处理示例

```c
static PyObject* safe_parsing(PyObject* self, PyObject* args) {
    int value;
    PyObject* obj;
    
    // 检查参数解析
    if (!PyArg_ParseTuple(args, "iO", &value, &obj)) {
        PyErr_SetString(PyExc_TypeError, 
                       "参数必须是: 整数和对象");
        return NULL;
    }
    
    // 检查对象类型
    if (!PyList_Check(obj)) {
        PyErr_SetString(PyExc_TypeError, 
                       "第二个参数必须是列表");
        return NULL;
    }
    
    // ... 处理参数 ...
    Py_RETURN_NONE;
}
```

这些格式代码和示例涵盖了大多数常见的参数解析场景。正确使用这些函数可以使 C 扩展更加健壮和安全。
