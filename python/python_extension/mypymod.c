#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *
testfunc(PyObject *self, PyObject *args)
{

    unsigned long c = 13; 
    PyObject * res = NULL;
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
