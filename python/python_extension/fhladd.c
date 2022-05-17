#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *
fhladd_add(PyObject *self, PyObject *args)
{
    int a = 0, b = 0;

    if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
        return NULL;
    }
    int c = a + b;
    PyObject * res = NULL;
    res = PyLong_FromLong(c);

    return res;
}


static PyMethodDef fhladd_method[] = {
    {"add", fhladd_add, METH_VARARGS},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef fhladd = {
    PyModuleDef_HEAD_INIT,
    "fhladd",
    NULL,
    -1,
    fhladd_method
};


PyMODINIT_FUNC
PyInit_fhladd(void)
{
    return PyModule_Create(&fhladd);
}
