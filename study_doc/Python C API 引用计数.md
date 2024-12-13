

# Python C API 引用计数教程

## 1. Python中的引用计数

Python 使用引用计数来管理内存。每个对象都有一个引用计数，表示有多少个指针指向它。

````c
PyObject* obj = PyLong_FromLong(42);
// 此时 obj 的引用计数为 1

Py_INCREF(obj);  // 引用计数 +1
Py_DECREF(obj);  // 引用计数 -1

// 当引用计数降为 0 时，对象被销毁
````

## 2. 拥有规则

基本规则：
1. **借用引用**：不需要管理引用计数
2. **偷取引用**：需要自己减少引用计数
3. **新引用**：需要在不再使用时减少引用计数

示例：
````c
static PyObject* example_function(PyObject* self, PyObject* args) {
    PyObject* obj;
    
    // 借用引用 - 不需要管理引用计数
    obj = PyTuple_GetItem(args, 0);
    
    // 新引用 - 需要管理引用计数
    PyObject* new_obj = PyLong_FromLong(42);
    if (new_obj == NULL) {
        return NULL;
    }
    
    // 使用完后减少引用计数
    Py_DECREF(new_obj);
    
    Py_RETURN_NONE;
}
````

## 3. 危险的薄冰

常见陷阱和解决方案：

````c
static PyObject* dangerous_function(PyObject* self, PyObject* args) {
    PyObject *list, *item;
    
    // 1. 内存泄漏
    list = PyList_New(1);
    item = PyLong_FromLong(42);
    PyList_SetItem(list, 0, item);  // PyList_SetItem 偷取引用
    // 不需要 Py_DECREF(item)
    
    // 2. 过早释放
    PyObject* temp = PyLong_FromLong(100);
    Py_DECREF(temp);  // 错误！过早释放
    // PyList_SetItem(list, 1, temp);  // temp 可能已被销毁
    
    // 3. 正确的做法
    PyObject* safe_temp = PyLong_FromLong(100);
    if (PyList_SetItem(list, 0, safe_temp) < 0) {
        Py_DECREF(safe_temp);
        Py_DECREF(list);
        return NULL;
    }
    // PyList_SetItem 偷取了 safe_temp 的引用
    
    return list;
}
````

## 4. NULL指针处理

安全的 NULL 指针处理：

````c
static PyObject* safe_function(PyObject* self, PyObject* args) {
    PyObject *obj1 = NULL, *obj2 = NULL, *result = NULL;
    
    // 1. 创建对象
    obj1 = PyLong_FromLong(42);
    if (obj1 == NULL) {
        goto error;
    }
    
    obj2 = PyLong_FromLong(100);
    if (obj2 == NULL) {
        goto error;
    }
    
    // 2. 使用对象
    result = PyNumber_Add(obj1, obj2);
    if (result == NULL) {
        goto error;
    }
    
    // 3. 清理并返回
    Py_DECREF(obj1);
    Py_DECREF(obj2);
    return result;
    
error:
    // 安全的清理
    Py_XDECREF(obj1);  // Py_XDECREF 安全处理 NULL
    Py_XDECREF(obj2);
    Py_XDECREF(result);
    return NULL;
}
````

## 5. 最佳实践

1. **使用 Py_XDECREF 而不是 Py_DECREF**：
````c
Py_XDECREF(obj);  // 安全处理 NULL
// 等价于
if (obj) {
    Py_DECREF(obj);
}
````

2. **使用清理代码块**：
````c
static PyObject* cleanup_example(PyObject* self, PyObject* args) {
    PyObject *obj1 = NULL, *obj2 = NULL;
    
    obj1 = PyLong_FromLong(42);
    if (obj1 == NULL) {
        goto cleanup;
    }
    
    obj2 = PyLong_FromLong(100);
    if (obj2 == NULL) {
        goto cleanup;
    }
    
    // 成功路径
    Py_DECREF(obj2);
    return obj1;
    
cleanup:
    Py_XDECREF(obj1);
    Py_XDECREF(obj2);
    return NULL;
}
````




# 偷取引用示例

最典型的偷取引用例子是 `PyList_SetItem` 和 `PyTuple_SetItem`。这些函数会"偷取"对象的引用计数管理权：

````c
static PyObject* stealing_example(PyObject* self, PyObject* args) {
    // 1. 基本示例
    PyObject* list = PyList_New(2);
    if (!list) return NULL;
    
    PyObject* num = PyLong_FromLong(42);  // 引用计数 = 1
    // PyList_SetItem 偷取了 num 的引用
    PyList_SetItem(list, 0, num);  
    // 不需要 Py_DECREF(num)，因为引用已被偷取
    
    // 2. 错误示例
    PyObject* str = PyUnicode_FromString("hello");
    Py_DECREF(str);  // 错误！不要在偷取前减少引用
    PyList_SetItem(list, 1, str);  // 危险：str可能已被销毁
    
    // 3. 正确的错误处理
    PyObject* value = PyLong_FromLong(100);
    if (!value) {
        Py_DECREF(list);
        return NULL;
    }
    
    if (PyList_SetItem(list, 1, value) < 0) {
        // 如果设置失败，需要手动清理value
        Py_DECREF(value);
        Py_DECREF(list);
        return NULL;
    }
    
    return list;
}
````

关键点：
1. `PyList_SetItem` 接管了对象的所有权
2. 不需要对被偷取的对象调用 `Py_DECREF`
3. 在偷取前不要减少引用计数
4. 如果偷取失败，需要手动清理对象

3. **记住引用规则**：
- 创建新对象：拥有一个引用
- 借用引用：不需要管理
- 偷取引用：函数会接管引用计数管理
- 增加引用：必须相应减少

这些规则和实践可以帮助你避免内存泄漏和段错误，编写更可靠的 Python C 扩展。
