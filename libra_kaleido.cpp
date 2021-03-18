//
// Created by 王振浩 on 2020/11/9.
//
#include "libra_kaleido.h"
#include "libra_interface.h"
#include "libra_animate.h"

zend_class_entry *kaleido_ce;

zend_object_handlers kaleido_object_handlers;

ZEND_BEGIN_ARG_INFO_EX(kaleido_construct, 0, 0, 3)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, direction)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(kaleido_image_stay, 0, 0, 1)
    ZEND_ARG_INFO(0, duration)
ZEND_END_ARG_INFO()

PHP_METHOD(kaleido, __construct) {
    zend_long width;
    zend_long height;
    zend_long direction = libra::Kaleido::Horizontal;

    ZEND_PARSE_PARAMETERS_START(2, 3)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(direction)
    ZEND_PARSE_PARAMETERS_END();

    libra_object *obj = Z_LIBRA_P(getThis());
    obj->ptr = new libra::Kaleido(width, height, direction);
}

PHP_METHOD(kaleido, __destruct) {
    delete Z_KALEIDO_P(getThis());
}

PHP_METHOD(kaleido, imageStay) {
    zend_long duration;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(duration)
    ZEND_PARSE_PARAMETERS_END();

    libra::Kaleido *k = Z_KALEIDO_P(getThis());
    bool b = k->setImageStay(duration);

    RETURN_BOOL(b)
}

PHP_METHOD(kaleido, generate) {
    char *dst;
    size_t len = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(dst, len)
    ZEND_PARSE_PARAMETERS_END();

    libra::Kaleido *k = Z_KALEIDO_P(getThis());
    bool b = k->generate(dst);

    RETURN_BOOL(b)
}

static const zend_function_entry kaleido_functions[] = {
    PHP_ME(kaleido, __construct, kaleido_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(kaleido, generate, animate_generate, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, imageStay, kaleido_image_stay, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, __destruct, animate_destruct, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    {NULL, NULL, NULL}
};

static zend_object* libra_kaleido_new(zend_class_entry *ce)  {
    return libra_object_new(ce, &kaleido_object_handlers);
}

LIBRA_STARTUP_FUNCTION(kaleido) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra", "Kaleido", kaleido_functions);
    kaleido_ce = zend_register_internal_class_ex(&ce, libra_animate_ce TSRMLS_CC);
    kaleido_ce->create_object = libra_kaleido_new;

    libra_object_handlers_init(&kaleido_object_handlers);

    zend_declare_class_constant_long(kaleido_ce, "HORIZENTAL", sizeof("HORIZENTAL") - 1, libra::Kaleido::Horizontal TSRMLS_CC);
    zend_declare_class_constant_long(kaleido_ce, "VERTICAL", sizeof("VERTICAL") - 1, libra::Kaleido::Vertical TSRMLS_CC);

    return SUCCESS;
}
