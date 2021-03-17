//
// Created by 王振浩 on 2021/3/16.
//
#include "libra_roller.h"
#include "libra_interface.h"

zend_class_entry *libra_roller_ce;

zend_object_handlers libra_roller_object_handlers;

ZEND_BEGIN_ARG_INFO_EX(roller_construct, 0, 0, 2)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(roller_destruct, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(roller, __construct) {
    int64_t width;
    int64_t height;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();

    libra_object *obj = Z_LIBRA_P(getThis());
    obj->ptr = new libra::Roller(width, height);
}

PHP_METHOD(roller, __destruct) {
    ZEND_PARSE_PARAMETERS_NONE();

    delete Z_LIBRA_ROLLER_P(getThis());
}

PHP_METHOD(roller, add) {
    char* file;
    size_t len = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(file, len)
    ZEND_PARSE_PARAMETERS_END();

    libra::Roller *r = Z_LIBRA_ROLLER_P(getThis());
    bool b = r->add(file);

    RETURN_BOOL(b)
}

PHP_METHOD(roller, quality) {
    zend_long q;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(q)
    ZEND_PARSE_PARAMETERS_END();

    libra::Roller *r = Z_LIBRA_ROLLER_P(getThis());
    bool b = r->setQuality(q);

    RETURN_BOOL(b)
}

PHP_METHOD(roller, frameCount) {
    zend_long q;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(q)
    ZEND_PARSE_PARAMETERS_END();

    libra::Roller *r = Z_LIBRA_ROLLER_P(getThis());
    bool b = r->setFrameCount(q);

    RETURN_BOOL(b)
}

PHP_METHOD(roller, loop) {
    zend_long q;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(q)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(true)
}

PHP_METHOD(roller, generate) {
    char *up, *down;
    size_t lenUp = 0, lenDown = 0;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(up, lenUp)
        Z_PARAM_STRING(down, lenDown)
    ZEND_PARSE_PARAMETERS_END();

    libra::Roller *r = Z_LIBRA_ROLLER_P(getThis());
    bool b = r->generate(up, down);

    RETURN_BOOL(b)
}

PHP_METHOD(roller, clear) {
    ZEND_PARSE_PARAMETERS_NONE();

    libra::Roller *r = Z_LIBRA_ROLLER_P(getThis());
    r->clear();

    RETURN_NULL()
}

PHP_METHOD(roller, errorCode) {
    ZEND_PARSE_PARAMETERS_NONE();

    libra::Roller *r = Z_LIBRA_ROLLER_P(getThis());
    int64_t code = r->lastErrorCode();

    RETURN_LONG(code)
}

PHP_METHOD(roller, errorInfo) {
    ZEND_PARSE_PARAMETERS_NONE();

    libra::Roller *r = Z_LIBRA_ROLLER_P(getThis());
    const std::string& msg = r->lastError();

    RETURN_STRINGL(msg.data(), msg.length())
}

static const zend_function_entry libra_roller_functions[] = {
    PHP_ME(roller, __construct, roller_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(roller, __destruct, roller_destruct, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    PHP_ME(roller, add, animate_add, ZEND_ACC_PUBLIC)
    PHP_ME(roller, generate, animate_generate, ZEND_ACC_PUBLIC)
    PHP_ME(roller, loop, animate_loop, ZEND_ACC_PUBLIC)
    PHP_ME(roller, quality, animate_quality, ZEND_ACC_PUBLIC)
    PHP_ME(roller, frameCount, animate_frame_count, ZEND_ACC_PUBLIC)
    PHP_ME(roller, clear, animate_noargs, ZEND_ACC_PUBLIC)
    ZEND_ME(roller, errorCode, animate_noargs, ZEND_ACC_PUBLIC)
    ZEND_ME(roller, errorInfo, animate_noargs, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_object *libra_roller_new(zend_class_entry *ce)  {
    return libra_object_new(ce, &libra_roller_object_handlers);
}

LIBRA_STARTUP_FUNCTION(roller) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra", "Roller", libra_roller_functions);
    libra_roller_ce = zend_register_internal_class(&ce TSRMLS_CC);
    libra_roller_ce->create_object = libra_roller_new;

    zend_class_implements(libra_roller_ce, 1, libra_animate_interface_ce);
    libra_object_handlers_init(&libra_roller_object_handlers);

    return SUCCESS;
}