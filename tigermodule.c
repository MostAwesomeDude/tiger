/* Copyright 2008 Corbin Simpson
 * <cds@corbinsimpson.com>
 * This code is provided under the terms of the GNU Public License, version 3.
 */

#include <Python.h>

typedef struct {
	PyObject_HEAD
	char* message;
	Py_ssize_t msize;
} tiger_TigerObject;

static PyObject* tiger_new(PyTypeObject* type, PyObject* args,
							PyObject* kwds) {
	tiger_TigerObject* self;

	self = (tiger_TigerObject*)type->tp_alloc(type, 0);
	if (self != NULL)
		self->message = NULL;

	return (PyObject*)self;
}

static int tiger_init(tiger_TigerObject* self, PyObject* args,
							PyObject* kwds) {
	char* message = NULL;
	Py_ssize_t msize = 0;

	if (!PyArg_ParseTuple(args, "|s#", &message, &msize))
		return -1;

	if (message != NULL) {
		char* temp;
		self->message = malloc(self->msize);
		memcpy(((tiger_TigerObject*)self)->message, temp, self->msize);
	}

	((tiger_TigerObject*)self)->message = message;
	((tiger_TigerObject*)self)->msize = msize;

	return 0;
}

static PyObject* tiger_dealloc(tiger_TigerObject* self) {
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject* tiger_update(PyObject* self, PyObject* args) {
	char* str;
	Py_ssize_t msize;
	if (!PyArg_ParseTuple(args, "s#", &str, &msize))
		return NULL;

	if (((tiger_TigerObject*)self)->message == NULL) {
		((tiger_TigerObject*)self)->message = malloc(msize);
		memcpy(((tiger_TigerObject*)self)->message, str, msize);
	} else {
		((tiger_TigerObject*)self)->message = realloc(
				((tiger_TigerObject*)self)->message, msize);
		memcpy(((tiger_TigerObject*)self)->message
			+ ((tiger_TigerObject*)self)->msize, str, msize);
	}
	((tiger_TigerObject*)self)->msize += msize;

	Py_RETURN_NONE;
}

static PyObject* tiger_digest(PyObject* self, PyObject* args) {
	unsigned long long int result[3];
	
	char* message = ((tiger_TigerObject*)self)->message;
	unsigned long long int msize = ((tiger_TigerObject*)self)->msize;

	if (message)
		tiger((unsigned long long int*)message, msize, &result);
	else
		tiger((unsigned long long int*)"", 0, &result);

	return PyString_FromStringAndSize((char*)result, 24);
}

static PyObject* tiger_hexdigest(PyObject* self, PyObject* args) {
	unsigned char result[24];
	char hex[48];
	
	char* message = ((tiger_TigerObject*)self)->message;
	unsigned long long int msize = ((tiger_TigerObject*)self)->msize;

	if (message)
		tiger((unsigned long long int*)message, msize, &result);
	else
		tiger((unsigned long long int*)"", 0, &result);

	sprintf(hex, "%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x"
			"%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x",
			result[0], result[1], result[2], result[3],
			result[4], result[5], result[6], result[7],
			result[8], result[9], result[10], result[11],
			result[12], result[13], result[14], result[15],
			result[16], result[17], result[18], result[19],
			result[20], result[21], result[22], result[23]);

	return PyString_FromStringAndSize((char*)hex, 48);
}

static PyMethodDef TigerMethods[] = {
	{"digest", tiger_digest, METH_NOARGS, "Hash current message and "
		"return the result."},
	{"hexdigest", tiger_hexdigest, METH_NOARGS, "Hash current message and "
		"return the result as a hexidecimal string."},
	{"update", tiger_update, METH_VARARGS, "Update current hash string."},
	{NULL, NULL, 0, NULL}
};

static PyMethodDef TigerModuleMethods[] = {
	{NULL, NULL, 0, NULL}
};

static PyTypeObject tiger_TigerType = {
	PyObject_HEAD_INIT(NULL)
	0,						/* ob_size */
	"tiger.tiger",					/* tp_name */
	sizeof(tiger_TigerObject),			/* tp_basicsize */
	0,						/* tp_itemsize */
	(destructor)tiger_dealloc,			/* tp_dealloc */
	0,						/* tp_print */
	0,						/* tp_getattr */
	0,						/* tp_setattr */
	0,						/* tp_compare */
	0,						/* tp_repr */
	0,						/* tp_as_number */
	0,						/* tp_as_sequence */
	0,						/* tp_as_mapping */
	0,						/* tp_hash */
	0,						/* tp_call */
	0,						/* tp_str */
	0,						/* tp_getattro */
	0,						/* tp_setattro */
	0,						/* tp_as_buffer */
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,	/* tp_flags */
	"Tiger objects",				/* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	TigerMethods,					/* tp_methods */
	0,						/* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)tiger_init,				/* tp_init */
	0,						/* tp_alloc */
	tiger_new,					/* tp_new */
};

PyMODINIT_FUNC inittiger() {
	PyObject* module;

	if (PyType_Ready(&tiger_TigerType) < 0)
		return;

	module = Py_InitModule3("tiger", TigerModuleMethods,
						"Tiger hash module.");
	if (module == NULL)
		return;

	Py_INCREF(&tiger_TigerType);
	PyModule_AddObject(module, "new", (PyObject*)&tiger_TigerType);
	PyModule_AddObject(module, "tiger", (PyObject*)&tiger_TigerType);
}
