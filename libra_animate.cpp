//
// Created by 王振浩 on 2020/11/20.
//

#include "libra_animate.h"
#include "libra_interface.h"
#include "src/Animate.h"

zend_class_entry* libra_animate_ce;
zend_object_handlers libra_animate_object_handlers;

PHP_METHOD(animate, add) {
    char* file;
    size_t len = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(file, len)
    ZEND_PARSE_PARAMETERS_END();

    libra::Animate* a = Z_LIBRA_ANIMATE_P(getThis());
    bool b = a->add(file);

    RETURN_BOOL(b)
}

PHP_METHOD(animate, quality) {
    zend_long q;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(q)
    ZEND_PARSE_PARAMETERS_END();

    libra::Animate* a = Z_LIBRA_ANIMATE_P(getThis());
    bool b = a->setQuality(q);

    RETURN_BOOL(b)
}

PHP_METHOD(animate, frameCount) {
    zend_long q;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(q)
    ZEND_PARSE_PARAMETERS_END();

    libra::Animate* a = Z_LIBRA_ANIMATE_P(getThis());
    bool b = a->setFrameCount(q);

    RETURN_BOOL(b)
}

PHP_METHOD(animate, duration) {
    zend_long time;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(time)
        ZEND_PARSE_PARAMETERS_END();

    libra::Animate* a = Z_LIBRA_ANIMATE_P(getThis());
    bool b = a->setDuration(time);

    RETURN_BOOL(b)
}

PHP_METHOD(animate, loop) {
    zend_long l;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(l)
    ZEND_PARSE_PARAMETERS_END();

    libra::Animate* a = Z_LIBRA_ANIMATE_P(getThis());
    bool b = a->setLoop(l);

    RETURN_BOOL(true)
}

PHP_METHOD(animate, clear) {
    ZEND_PARSE_PARAMETERS_NONE();

    libra::Animate* a = Z_LIBRA_ANIMATE_P(getThis());
    a->clear();

    RETURN_NULL()
}

PHP_METHOD(animate, errorCode) {
    ZEND_PARSE_PARAMETERS_NONE();

    libra::Animate* a = Z_LIBRA_ANIMATE_P(getThis());
    int64_t code = a->lastErrorCode();

    RETURN_LONG(code)
}

PHP_METHOD(animate, errorInfo) {
    ZEND_PARSE_PARAMETERS_NONE();

    libra::Animate* a = Z_LIBRA_ANIMATE_P(getThis());
    const std::string& msg = a->lastError();

    RETURN_STRINGL(msg.data(), msg.length())
}

static const zend_function_entry libra_animate_functions[] = {
    PHP_ME(animate, add, animate_add, ZEND_ACC_PUBLIC)
    PHP_ME(animate, loop, animate_loop, ZEND_ACC_PUBLIC)
    PHP_ME(animate, quality, animate_quality, ZEND_ACC_PUBLIC)
    PHP_ME(animate, frameCount, animate_frame_count, ZEND_ACC_PUBLIC)
    PHP_ME(animate, duration, animate_duration, ZEND_ACC_PUBLIC)
    PHP_ME(animate, clear, animate_noargs, ZEND_ACC_PUBLIC)
    PHP_ME(animate, errorCode, animate_noargs, ZEND_ACC_PUBLIC)
    PHP_ME(animate, errorInfo, animate_noargs, ZEND_ACC_PUBLIC)
    PHP_ABSTRACT_ME(animate, generate, animate_generate)
    { NULL, NULL, NULL}
};

static zend_object* libra_animate_new(zend_class_entry* ce) {
    return libra_object_new(ce, &libra_animate_object_handlers);
}

LIBRA_STARTUP_FUNCTION(animate) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra", "Animate", libra_animate_functions);
    libra_animate_ce = zend_register_internal_class(&ce TSRMLS_CC);
    libra_animate_ce->create_object = libra_animate_new;

    zend_class_implements(libra_animate_ce, 1, libra_animate_interface_ce);
    libra_object_handlers_init(&libra_animate_object_handlers);

    return SUCCESS;
}