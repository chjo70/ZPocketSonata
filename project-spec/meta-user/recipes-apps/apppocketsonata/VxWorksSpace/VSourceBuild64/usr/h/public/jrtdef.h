/*	Implementation module : jrtdef.h

	Copyright 1998 Diab Data Inc, USA

	Description :
	Java runtime support

	History :
	When    Who     What
*/
#ifndef _JRTDEF_H
#define _JRTDEF_H
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>


#define	isArray(CLASSP)		((CLASSP)->element_classp != 0)
#define	isInterface(CLASSP)	((CLASSP) != &__class__void && (CLASSP)->size == 0)
#define	isPrimitive(CLASSP)	((CLASSP)->class_list_cnt == 0 && !isInterface(CLASSP))

#if defined(GC_INCREMENTAL)
#define MARK_OBJECT_GREY(x) (x != NULL ? x->gc_info[0] = 0 :  0);
#else
#define MARK_OBJECT_GREY(x)
#endif

typedef int jboolean;
typedef signed char jbyte;
typedef short jshort;
typedef unsigned short jchar;
typedef int jint;
typedef long long jlong;
typedef float jfloat;
typedef double jdouble;
typedef struct java_object *jobject;

typedef union {
	jboolean	z;
	jbyte		b;
	jchar		c;
	jshort		s;
	jint		i;
	jlong		j;
	jfloat		f;
	jdouble		d;
	jobject		l;
} jvalue;

typedef	int (*vtable_entry)();

struct java_object {
	struct java_class	*classp;	/* Pointer to java.lang.Class */
	void			*synchronize;	/* Synchronization information */
	char			gc_info[8];	/* Garbage collection specific */
};

struct interface_info {
	struct java_class	*classp;	/* Pointer to java.lang.Class */
	struct interface_info	**interface_implementation_list_ptr;/* Array of interfaces */
	vtable_entry		vtable[1];	/* Virtual method table */
};

/* NOTE: these have to match the ones in jtree.h in jparse directory */
#define MOD_PUBLIC			0x1
#define MOD_PRIVATE			0x2
#define MOD_PROTECTED			0x4
#define MOD_STATIC			0x8
#define MOD_FINAL			0x10
#define MOD_SYNCHRONIZED		0x20
#define MOD_VOLATILE			0x40
#define MOD_TRANSIENT			0x80
#define MOD_NATIVE			0x100
#define MOD_INTERFACE			0x200
#define MOD_ABSTRACT			0x400
#define MOD_CONSTRUCTOR			0x800	/* set on constructors */
/* Note MOD_HIDDEN conflicts with MOD_METHOD_HAS_THROW_OR_CALL in the compiler but
   that's okay since MOD_METHOD_HAS_THROW_OR_CALL is internal to the compiler */
#define MOD_HIDDEN                      0x1000  /* special don't let reflections see this */

struct __java_field_entry {
	char			*name;		/* Name of field */
	char			*type;		/* Type descriptor */
	unsigned int		modifiers;	/* Field flags */
	unsigned int		offset;		/* Offset from class */
};

struct __java_method_entry {
	char			*name;		/* Name of method */
	char			*type;		/* Type descriptor */
	unsigned int		modifiers;	/* Method flags */
	unsigned int		offset;		/* Vtable index */
	int			(*addr)();	/* Address of method */
};

struct java_class {
	struct java_object	super;		/* Super class java.lang.Object */
	char			gc_info[16];	/* Garbage collection specific */
	unsigned int		magic;		/* Magic number class objects */
	unsigned int		*offsets;	/* Offsetof all references in class */
	struct java_class	*array_classp;	/* Pointer to java.lang.Class array of type */
	struct java_class	*element_classp;/* Pointer to java.lang.Class for element */
	unsigned int		init_state;	/* Class initialization state */
	unsigned int		size;		/* Size of class - size of array element */
	unsigned int		modifiers;	/* Class flags */
	char			*name;		/* Name of class */
	unsigned int		class_list_cnt;	/* Entries in class_list_ptr */
	struct java_class	**class_list_ptr;/* Array of class objects for supers */
	struct interface_info	**interface_implementation_list_ptr;/* Array of interfaces */
	struct __java_field_entry *field_ptr;	/* Field information pointer */
	struct __java_method_entry *method_ptr;	/* Method information pointer */
	vtable_entry		vtable[1];	/* Virtual method table */
};

struct java_class_5 {
	struct java_object	super;		/* Super class java.lang.Object */
	char			gc_info[16];	/* Garbage collection specific */
	unsigned int		magic;		/* Magic number class objects */
	unsigned int		*offsets;	/* Offsetof all references in class */
	struct java_class	*array_classp;	/* Pointer to java.lang.Class array of type */
	struct java_class	*element_classp;/* Pointer to java.lang.Class for element */
	unsigned int		init_state;	/* Class initialization state */
	unsigned int		size;		/* Size of class - size of array element */
	unsigned int		modifiers;	/* Class flags */
	char			*name;		/* Name of class */
	unsigned int		class_list_cnt;	/* Entries in class_list_ptr */
	struct java_class	**class_list_ptr;/* Array of class objects for supers */
	struct interface_info	**interface_implementation_list_ptr;/* Array of interfaces */
	struct __java_field_entry *field_ptr;	/* Field information pointer */
	struct __java_method_entry *method_ptr;	/* Method information pointer */
	vtable_entry		vtable[5];	/* Virtual method table */
};

typedef struct java_throwable {
	struct java_object	super;		/* Super class java.lang.Object */
	struct java_string	*msg;
	struct java_string	*_stTrace;
} *jthrowable;

struct java_array {
	struct java_object	super;		/* Super class java.lang.Object */
	int			length;
	union {
		jboolean	z[1];
		jbyte		b[1];
		jchar		c[1];
		jshort		s[1];
		jint		i[1];
		jlong		j[1];
		jfloat		f[1];
		jdouble		d[1];
		jobject		l[1];
	} elements;
};

#define	java_zero_array_size	((int)&((struct java_array *)0)->elements)

struct java_string {
	struct java_object	super;		/* Super class java.lang.Object */
	int			len;
	struct java_array	*datap;
};

extern struct java_class __class__char;
extern struct java_class __class__byte;
extern struct java_class __class__short;
extern struct java_class __class__int;
extern struct java_class __class__long;
extern struct java_class __class__float;
extern struct java_class __class__double;
extern struct java_class __class__boolean;
extern struct java_class __class__void;
extern struct java_class __class__Java_java_lang_Class;
extern struct java_class __class__Java_java_lang_Comparable;
extern struct java_class __class__Java_java_lang_Object;
extern struct java_class __class__Java_java_lang_String;
extern struct java_class __class__Java_java_lang_Boolean;
extern struct java_class __class__Java_java_lang_Integer;
extern struct java_class __class__Java_java_lang_Cloneable;
extern struct java_class __class__Java_java_lang_OutOfMemoryError;
extern struct java_class __class__Java_java_lang_NoSuchMethodError;
extern struct java_class __class__Java_java_lang_NoSuchFieldException;
extern struct java_class __class__Java_java_lang_NoSuchMethodException;
extern struct java_class __class__Java_java_lang_ClassCastException;
extern struct java_class __class__Java_java_lang_InstantiationException;
extern struct java_class __class__Java_java_lang_NullPointerException;
extern struct java_class __class__Java_java_lang_ArrayStoreException;
extern struct java_class __class__Java_java_lang_IndexOutOfBoundsException;
extern struct java_class __class__Java_java_lang_ArrayIndexOutOfBoundsException;
extern struct java_class __class__Java_java_lang_ArithmeticException;
extern struct java_class __class__Java_java_lang_UnsatisfiedLinkError;
extern struct java_class __class__Java_java_lang_ClassNotFoundException;
extern struct java_class __class__Java_java_lang_NegativeArraySizeException;
extern struct java_class __class__Java_java_lang_UnsupportedOperationException;
extern struct java_class __class__Java_java_lang_CloneNotSupportedException;
extern struct java_class __class__Java_java_lang_NumberFormatException;
extern struct java_class __class__Java_java_lang_InternalError;
extern struct java_class __class__Java_java_lang_IllegalArgumentException;
extern struct java_class __class__Java_java_lang_IllegalAccessException;
extern struct java_class __class__Java_java_io_IOException;
extern struct java_class __class__Java_java_net_UnknownHostException;
extern struct java_class __class__Java_java_net_ConnectException;
extern struct java_class __class__Java_java_lang_IllegalMonitorStateException;
extern struct java_class __class__Java_java_lang_InterruptedException;
extern struct java_class __class__Java_java_lang_DiabProcess;
extern struct java_class __class__Java_java_lang_IllegalThreadStateException;
extern struct java_class __class__Java_java_io_FileDescriptor;
extern struct java_class __class__Java_java_lang_ThreadGroup;
extern struct java_class __class__Java_java_lang_Thread;
extern struct java_class __class__Java_java_lang_ThreadLocal;
extern struct java_class __class__Java_java_io_FilenameFilter;
extern struct java_class __class__Java_java_util_Comparator;
extern struct java_class __class__Java_java_lang_reflect_Field;
extern struct java_class __class__Java_java_lang_reflect_Method;
extern struct java_class __class__Java_java_lang_reflect_Constructor;
extern struct java_class __class__Java_java_util_Properties;
extern struct java_class __class__Java_com_ddi_fastj_Main;
extern struct java_class __class__Java_java_io_Serializable;
extern struct java_class __class__Java_java_io_File_FileNameList;
extern jobject Java_com_ddi_fastj_Main__0003Cinit_0003E___3Ljava_lang_String_2(jobject, struct java_array *);
extern jobject Java_java_io_File_FileNameList_00024_0003Cinit_0003E__(jobject);
extern void *__java_new(struct java_class *classp);
extern void *__java_array_new(struct java_class *classp, int dims, int newdim, ...);
extern void *__java_array_new1(struct java_class *classp, int dims, int newdim, int *indp);
extern void *__java_string_from_cstring(const char *);
extern void *__java_string_const(const char *, struct java_string **);
extern jboolean Java_java_lang_Class_isArray(struct java_class *this);
extern void Java_java_lang_String__0003Cclinit_0003E__(void);
extern struct java_string *Java_java_lang_String_intern__(struct java_string *);
extern struct java_class *__java_array_class(struct java_class *classp, int dims);
extern struct java_array *__java_array_clone(struct java_array *);
extern void __java_throw(struct java_object *);
extern void __java_throw_OutOfMemoryError(void);
extern void __java_throw_NoSuchMethodError(void);
extern void __java_throw_NoSuchFieldException(void);
extern void __java_throw_NoSuchMethodException(void);
extern void __java_throw_ClassCastException(void);
extern void __java_throw_NegativeArraySizeException(void);
extern void __java_throw_ClassNotFoundException(void);
extern void __java_throw_UnsupportedOperationException(void);
extern void __java_throw_InstantiationException(void);
extern void __java_throw_NullPointerException(void);
extern void __java_throw_ArrayStoreException(void);
extern void __java_throw_IndexOutOfBoundsException(void);
extern void __java_throw_ArrayIndexOutOfBoundsException(void);
extern void __java_throw_CloneNotSupportedException(void);
extern void __java_throw_NumberFormatException(void);
extern void __java_throw_InternalError(void);
extern void __java_throw_IllegalArgumentException(void);
extern void __java_throw_IOException(const char *);
extern void __java_throw_UnknownHostException(const char *);
extern void __java_throw_ConnectException(const char *);
extern void __java_throw_IllegalMonitorStateException(void);
extern void __java_throw_InterruptedException(void);
extern void __java_throw_IllegalThreadStateException(void);
extern void __java_throw_IllegalAccessException(void);

extern struct interface_info *__java_find_interface_implementation(struct java_object *, struct java_class *, jint);
extern struct interface_info *__java_find_class_interface_implementation(struct java_class *, struct java_class *, jint);
extern jlong Java_java_lang_System_currentTimeMillis(void);
extern int __java_copyShortToChar(char *dest, unsigned short *src, int length);
extern jboolean Java_java_lang_Class_isPrimitive(struct java_class *this);
extern int __java_check_assignable2(struct java_class *toclass, struct java_class *fromclass);
extern jint Java_java_lang_Object_hashCode(struct java_object *this);

/* NOTE: should match the definition in FileDescriptor.java */
typedef struct file_descr {
	struct java_object super;
	jint fd;
	jint kind;
} file_descr, *jfile_descr;

extern jobject __java_create_process(jint pid, int in, int out, int err);
extern void __java_main(struct java_array *arg);
extern void *Java_java_lang_Thread_dummyRun__Ljava_lang_Thread_2(void *);
extern int Java_java_lang_System__0003Cclinit_0003E__(void);
extern int Java_java_io_FileDescriptor__0003Cclinit_0003E__(void);
extern struct java_class *Java_java_lang_Class_forName(struct java_string *name);
extern jboolean Java_java_lang_Class_isInterface(struct java_class *this);
extern struct java_string *Java_java_lang_Long_toString__JIZ(jlong i, jint radix,
						      jboolean treatUnsigned);
extern struct java_class *__java_get_type_from_name(const char **sp);
extern jboolean Java_java_lang_reflect_Modifier_isStatic__I(jint mod);
extern struct java_class *Java_java_lang_Class_getSuperclass(struct java_class *this);
extern int __get_vtable_index(struct java_class *for_class, vtable_entry for_func);
extern void Java_java_lang_Object_notifyAll(jobject o);
extern void __java_monitor_enter(jobject o);
extern void __java_monitor_exit(jobject o);
extern void Java_java_lang_System_arraycopy(
	struct java_array *src, int srcoffset,
	struct java_array *dst, int dstoffset,
	int length);
extern jobject Java_java_lang_System_in;
extern jobject Java_java_lang_System_out;
extern jobject Java_java_lang_System_err;

struct java_AccessibleObject {
	struct java_object super;
};

struct java_Boolean {
	struct java_object super;
	jboolean val;
};

struct java_Integer {
	struct java_object super;
	jint val;
};

#define	MODE_READ	1
#define	MODE_WRITE	2

struct java_iomem_address {
	void			*loadr;
	void			*hiadr;
	int			sizes;
	int			mode;
};

typedef struct diab_process {
	struct java_object super;
	jint pid;
} diab_process, *jdiabprocess;

extern struct java_iomem_address __java_io_memory[];

extern void *__java_alloc(int size);
extern void __java_free(void *p);
extern struct java_object *__java_gc_allocate(struct java_class *, int, int);
extern void Java_java_lang_Object_invoke_1finalize__Ljava_lang_Object_2(jobject);
extern void __java_lock_thread_list(void);
extern void __java_unlock_thread_list(void);
extern void __java_run_finalizer(void);
extern void __java_run_gc(void);
extern int __diab_socket_close(int fd);

extern void __java_throw2(struct java_class *, const char*);

#endif
