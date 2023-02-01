#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *
testfunc(PyObject *self, PyObject *args)
{
    
    PyObject * res = NULL;
    unsigned long c = PyTuple_Size(args);
    if (c < 1) {
        printf("must give one argument.\n");
        return res;
    }
    
    PyObject * arg1 = PyTuple_GetItem(args, 0);
    if (!PyList_Check(arg1)) {
        printf("arg1 should be list PyList_Type.\n");
        return res;
    }
    unsigned long list_len = PyList_Size(arg1);
    unsigned long i = 0;
    long num = 0;
    PyObject * list_ele = NULL; 
    for (i = 0; i < list_len; i++) {
        list_ele = PyList_GetItem(arg1, i);
        num = PyLong_AsLong(list_ele);
        printf("%ld ", num);
    }
    printf("\b\n");
    res = PyLong_FromLong(c);
    return res;
}


static PyMethodDef mypymod_method[] = {
    {"testfunc", testfunc, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef mypymod = {
    PyModuleDef_HEAD_INIT,
    "mypymod",
    NULL,
    -1,
    mypymod_method
};


PyMODINIT_FUNC
PyInit_mypymod(void)
{
    return PyModule_Create(&mypymod);
}
