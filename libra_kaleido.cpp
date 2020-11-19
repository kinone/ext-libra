//
// Created by 王振浩 on 2020/11/9.
//
#include "libra_kaleido.h"
#include "libra_logger.h"

zend_class_entry *kaleido_ce;

zend_object_handlers kaleido_object_handlers;

ZEND_BEGIN_ARG_INFO_EX(kaleido_construct, 0, 0, 3)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, direction)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(kaleido_add, 0, 0, 1)
    ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(kaleido_generate, 0, 0, 1)
    ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(kaleido_image_delay, 0, 0, 1)
    ZEND_ARG_INFO(0, delay)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(kaleido_animate_time, 0, 0, 1)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(kaleido_animate_frame_count, 0, 0, 1)
    ZEND_ARG_INFO(0, count)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(kaleido_set_quality, 0, 0, 1)
    ZEND_ARG_INFO(0, quality)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(kaleido_set_loop, 0, 0, 1)
    ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(kaleido_no_args, 0, 0, 0)
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

PHP_METHOD(kaleido, add) {
    char* file;
    size_t len = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(file, len)
    ZEND_PARSE_PARAMETERS_END();

    libra::Kaleido *k = Z_KALEIDO_P(getThis());
    bool b = k->add(file);

    RETURN_BOOL(b);
}

PHP_METHOD(kaleido, quality) {
    zend_long q;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(q)
    ZEND_PARSE_PARAMETERS_END();

    libra::Kaleido *k = Z_KALEIDO_P(getThis());
    bool b = k->setQuality(q);

    RETURN_BOOL(b);
}

PHP_METHOD(kaleido, imageDelay) {
    zend_long delay;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(delay)
    ZEND_PARSE_PARAMETERS_END();

    libra::Kaleido *k = Z_KALEIDO_P(getThis());
    bool b = k->setImageStay(delay);

    RETURN_BOOL(b);
}

PHP_METHOD(kaleido, animateTime) {
    zend_long time;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(time)
    ZEND_PARSE_PARAMETERS_END();

    libra::Kaleido *k = Z_KALEIDO_P(getThis());
    bool b = k->setAnimateTime(time);

    RETURN_BOOL(b);
}

PHP_METHOD(kaleido, animateFrameCount) {
    zend_long count;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(count)
    ZEND_PARSE_PARAMETERS_END();

    libra::Kaleido *k = Z_KALEIDO_P(getThis());
    bool b = k->setFrameCount(count);

    RETURN_BOOL(b);
}

PHP_METHOD(kaleido, loop) {
    zend_long loop;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(loop)
    ZEND_PARSE_PARAMETERS_END();

    libra::Kaleido *k = Z_KALEIDO_P(getThis());
    bool b = k->setLoop(loop);

    RETURN_BOOL(b);
}

PHP_METHOD(kaleido, generate) {
    char *dst;
    size_t len = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(dst, len)
    ZEND_PARSE_PARAMETERS_END();

    libra::Kaleido *k = Z_KALEIDO_P(getThis());
    k->generate(dst);

    RETURN_NULL();
}

PHP_METHOD(kaleido, clear) {
    ZEND_PARSE_PARAMETERS_NONE();

    libra::Kaleido *k = Z_KALEIDO_P(getThis());
    k->clear();

    RETURN_NULL();
}

PHP_METHOD(kaleido, setLogger) {
    zval *logger;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS(logger, libra_logger_interface_ce);
    ZEND_PARSE_PARAMETERS_END();

    libra::Kaleido *k = Z_KALEIDO_P(getThis());
    k->registerLogger(logger);

    RETURN_NULL();
}

static const zend_function_entry kaleido_functions[] = {
    PHP_ME(kaleido, __construct, kaleido_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(kaleido, add, kaleido_add, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, generate, kaleido_generate, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, quality, kaleido_set_quality, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, loop, kaleido_set_loop, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, imageDelay, kaleido_image_delay, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, animateTime, kaleido_animate_time, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, animateFrameCount, kaleido_animate_frame_count, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, clear, kaleido_no_args, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, setLogger, libra_set_logger, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, __destruct, kaleido_no_args, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    {NULL, NULL, NULL}
};

static zend_object* libra_kaleido_new(zend_class_entry *ce)  {
    return libra_object_new(ce, &kaleido_object_handlers);
}

LIBRA_STARTUP_FUNCTION(kaleido) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra", "Kaleido", kaleido_functions);
    kaleido_ce = zend_register_internal_class(&ce TSRMLS_CC);
    kaleido_ce->create_object = libra_kaleido_new;

    libra_object_handlers_init(&kaleido_object_handlers);

    zend_declare_class_constant_long(kaleido_ce, "HORIZENTAL", sizeof("HORIZENTAL") - 1, libra::Kaleido::Horizontal TSRMLS_CC);
    zend_declare_class_constant_long(kaleido_ce, "VERTICAL", sizeof("VERTICAL") - 1, libra::Kaleido::Vertical TSRMLS_CC);

    return SUCCESS;
}
