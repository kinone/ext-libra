//
// Created by 王振浩 on 2020/11/10.
//
#include "libra_image.h"

zend_class_entry *libra_image_ce;

zend_object_handlers libra_image_object_handlers;

PHP_METHOD(image, __construct) {
    char *file;
    size_t len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(file, len)
    ZEND_PARSE_PARAMETERS_END();

    libra_image_t *obj = Z_LIBRA_IMAGE_P(getThis());
    obj->origin = new libra::Image(file);
}

PHP_METHOD(image, __destruct) {
    libra_image_t *obj = Z_LIBRA_IMAGE_P(getThis());
    delete(obj->origin);
}

PHP_METHOD(image, resize) {
    int64 width;
    int64 height;

    ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_LONG(width);
    Z_PARAM_LONG(height);
    ZEND_PARSE_PARAMETERS_END();

    libra_image_t *obj = Z_LIBRA_IMAGE_P(getThis());
    obj->origin->resize(width, height);

    RETURN_NULL();
}

PHP_METHOD(image, download) {
    char *file;
    size_t len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(file, len);
    ZEND_PARSE_PARAMETERS_END();

    libra_image_t *obj = Z_LIBRA_IMAGE_P(getThis());
    obj->origin->download(file);

    RETURN_NULL();
}

PHP_METHOD(image, compressJpeg) {
    char *file;
    size_t len;
    int64 q;

    ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_STRING(file, len)
    Z_PARAM_LONG(q);
    ZEND_PARSE_PARAMETERS_END();

    libra_image_t *obj = Z_LIBRA_IMAGE_P(getThis());
    obj->origin->compressJpeg(file, q);

    RETURN_NULL();
}

PHP_METHOD(image, compressPng) {
    char *file;
    size_t len;
    int64 level;

    ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_STRING(file, len)
    Z_PARAM_LONG(level);
    ZEND_PARSE_PARAMETERS_END();

    libra_image_t *obj = Z_LIBRA_IMAGE_P(getThis());
    obj->origin->compressPng(file, level);

    RETURN_NULL();
}

PHP_METHOD(image, getWidth) {
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();

    libra_image_t *obj = Z_LIBRA_IMAGE_P(getThis());

    RETURN_LONG(obj->origin->getWidth());
}

PHP_METHOD(image, getHeight) {
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();

    libra_image_t *obj = Z_LIBRA_IMAGE_P(getThis());

    RETURN_LONG(obj->origin->getHeight());
}

static const zend_function_entry libra_image_functions[] = {
    PHP_ME(image, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(image, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    PHP_ME(image, compressPng, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(image, compressJpeg, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(image, getWidth, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(image, getHeight, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(image, resize, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(image, download, NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_object* libra_image_new(zend_class_entry *ce)  {
    libra_image_t *k = (libra_image_t*)emalloc(sizeof(libra_image_t) + zend_object_properties_size(ce));

    memset(k, 0, XtOffsetOf(libra_image_t, std));
    zend_object_std_init(&k->std, ce);
    k->std.handlers = &libra_image_object_handlers;
    if (UNEXPECTED(ce->default_properties_count)) {
        object_properties_init(&k->std, ce);
    }

    return &k->std;
}

static void libra_image_free(zend_object *object) {
    zend_object_std_dtor(object);
}

LIBRA_STARTUP_FUNCTION(image) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Libra\\Image", libra_image_functions);
    libra_image_ce = zend_register_internal_class(&ce TSRMLS_CC);
    libra_image_ce->create_object = libra_image_new;

    memcpy(&libra_image_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

    libra_image_object_handlers.free_obj = libra_image_free;
    libra_image_object_handlers.clone_obj = NULL;

    return SUCCESS;
}

