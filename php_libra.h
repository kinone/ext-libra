/* libra extension for PHP */

#ifndef PHP_LIBRA_H
# define PHP_LIBRA_H

extern "C" {
#include "php.h"
#include "ext/standard/info.h"
};

# define phpext_libra_ptr &libra_module_entry

# define PHP_LIBRA_VERSION "0.1.1"

# if defined(ZTS) && defined(COMPILE_DL_LIBRA)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#define LIBRA_STARTUP_FUNCTION(module)    ZEND_MINIT_FUNCTION(libra_##module)
#define LIBRA_STARTUP(module)             ZEND_MINIT(libra_##module)(INIT_FUNC_ARGS_PASSTHRU)

typedef struct {
    void        *ptr;
    zend_object std;
} libra_object;

#define Z_LIBRA_T(zv)                   (libra_fetch_object(Z_OBJ(zv)))
#define Z_LIBRA_P(zv)                   Z_LIBRA_T(*zv)
#define Z_LIBRA_INNER_P(zv)             (Z_LIBRA_P(zv)->ptr)

static zend_always_inline libra_object *libra_fetch_object(zend_object *obj) {
    return (libra_object *)((char*)(obj) - XtOffsetOf(libra_object, std));
}

static zend_object *libra_object_new(zend_class_entry *ce, zend_object_handlers *h)  {
    libra_object *obj = (libra_object *)zend_object_alloc(sizeof(libra_object), ce);

    zend_object_std_init(&obj->std, ce);
    object_properties_init(&obj->std, ce);
    rebuild_object_properties(&obj->std);

    obj->std.handlers = h;

    return &obj->std;
}

static void libra_object_free_storage(zend_object *std) {
    zend_object_std_dtor(std);
}

static void libra_object_handlers_init(zend_object_handlers *h) {
    memcpy(h, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

    h->offset = XtOffsetOf(libra_object, std);
    h->dtor_obj = zend_objects_destroy_object;
    h->free_obj = libra_object_free_storage;
    h->clone_obj = NULL;
}

PHP_RINIT_FUNCTION(libra);

PHP_RSHUTDOWN_FUNCTION(libra);

PHP_MINFO_FUNCTION(libra);

PHP_MINIT_FUNCTION(libra);

PHP_MSHUTDOWN_FUNCTION(libra);

#endif    /* PHP_LIBRA_H */

