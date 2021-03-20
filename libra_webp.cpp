//
// Created by 王振浩 on 2021/03/20.
//

#include "libra_webp.h"

zend_class_entry* libra_webpanim_ce;
zend_object_handlers libra_webpanim_object_handlers;

ZEND_BEGIN_ARG_INFO_EX(webpanim_construct, 0, 0, 1)
ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(webpanim_no_args, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(webpanim, __construct) {
    char* filename;
    size_t len = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(filename, len)
        ZEND_PARSE_PARAMETERS_END();

    libra_object* obj = Z_LIBRA_P(getThis());
    obj->ptr = new libra::WebpAnim(filename);
}

PHP_METHOD(webpanim, __destruct) {
    ZEND_PARSE_PARAMETERS_NONE();

    delete Z_LIBRA_WEBPANIM_P(getThis());
}

PHP_METHOD(webpanim, width) {
    ZEND_PARSE_PARAMETERS_NONE();
    libra::WebpAnim* obj = Z_LIBRA_WEBPANIM_P(getThis());

    RETURN_LONG(obj->width());
}

PHP_METHOD(webpanim, height) {
    ZEND_PARSE_PARAMETERS_NONE();
    libra::WebpAnim* obj = Z_LIBRA_WEBPANIM_P(getThis());

    RETURN_LONG(obj->height());
}

PHP_METHOD(webpanim, frameCount) {
    ZEND_PARSE_PARAMETERS_NONE();
    libra::WebpAnim* obj = Z_LIBRA_WEBPANIM_P(getThis());

    RETURN_LONG(obj->frameCount());
}

PHP_METHOD(webpanim, loopCount) {
    ZEND_PARSE_PARAMETERS_NONE();
    libra::WebpAnim* obj = Z_LIBRA_WEBPANIM_P(getThis());

    RETURN_LONG(obj->loopCount());
}

static const zend_function_entry libra_webpanim_functions[] = {
    PHP_ME(webpanim, __construct, webpanim_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(webpanim, width, webpanim_no_args, ZEND_ACC_PUBLIC)
    PHP_ME(webpanim, height, webpanim_no_args, ZEND_ACC_PUBLIC)
    PHP_ME(webpanim, frameCount, webpanim_no_args, ZEND_ACC_PUBLIC)
    PHP_ME(webpanim, loopCount, webpanim_no_args, ZEND_ACC_PUBLIC)
    PHP_ME(webpanim, __destruct, webpanim_no_args, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
    {
NULL, NULL, NULL
}
};

static zend_object* libra_webpanim_new(zend_class_entry* ce) {
    return libra_object_new(ce, &libra_webpanim_object_handlers);
}

LIBRA_STARTUP_FUNCTION(webp) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra\\Webp", "Animation", libra_webpanim_functions);
    libra_webpanim_ce = zend_register_internal_class(&ce TSRMLS_CC);
    libra_webpanim_ce->create_object = libra_webpanim_new;

    libra_object_handlers_init(&libra_webpanim_object_handlers);

    return SUCCESS;
}