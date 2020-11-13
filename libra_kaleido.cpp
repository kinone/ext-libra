//
// Created by 王振浩 on 2020/11/9.
//
#include "libra_kaleido.h"

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

ZEND_BEGIN_ARG_INFO_EX(kaleido_no_args, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(kaleido, __construct) {
    int64_t width;
    int64_t height;
    int64_t direction = libra::Kaleido::Horizontal;

    ZEND_PARSE_PARAMETERS_START(2, 3)
    Z_PARAM_LONG(width)
    Z_PARAM_LONG(height)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(direction)
    ZEND_PARSE_PARAMETERS_END();

    kaleido_t *obj = Z_KALEIDO_P(getThis());
    obj->proto = new libra::Kaleido(width, height, direction);
}

PHP_METHOD(kaleido, __destruct) {
    kaleido_t *obj = Z_KALEIDO_P(getThis());
    delete obj->proto;
}

PHP_METHOD(kaleido, add) {
    char* file;
    size_t len = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(file, len)
    ZEND_PARSE_PARAMETERS_END();

    kaleido_t *k = Z_KALEIDO_P(getThis());
    zend_bool ret = k->proto->add(file);

    RETURN_BOOL(ret);
}

PHP_METHOD(kaleido, quality) {
    int64_t q;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(q)
    ZEND_PARSE_PARAMETERS_END();

    kaleido_t *k = Z_KALEIDO_P(getThis());
    bool b = k->proto->setQuality(q);

    RETURN_BOOL(b);
}

PHP_METHOD(kaleido, imageDelay) {
    int64_t delay;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(delay)
    ZEND_PARSE_PARAMETERS_END();

    kaleido_t *k = Z_KALEIDO_P(getThis());
    bool b = k->proto->setImageStay(delay);

    RETURN_BOOL(b);
}

PHP_METHOD(kaleido, animateTime) {
    int64_t time;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(time)
    ZEND_PARSE_PARAMETERS_END();

    kaleido_t *k = Z_KALEIDO_P(getThis());
    bool b = k->proto->setAnimateTime(time);

    RETURN_BOOL(b);
}

PHP_METHOD(kaleido, animateFrameCount) {
    int64_t count;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(count)
    ZEND_PARSE_PARAMETERS_END();

    kaleido_t *k = Z_KALEIDO_P(getThis());
    bool b = k->proto->setFrameCount(count);

    RETURN_BOOL(b);
}

PHP_METHOD(kaleido, generate) {
    char *dst;
    size_t len = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(dst, len)
    ZEND_PARSE_PARAMETERS_END();

    kaleido_t *k = Z_KALEIDO_P(getThis());
    k->proto->generate(dst);

    RETURN_NULL();
}

PHP_METHOD(kaleido, clear) {
    ZEND_PARSE_PARAMETERS_NONE();

    kaleido_t *k = Z_KALEIDO_P(getThis());
    k->proto->clear();

    RETURN_NULL();
}

static const zend_function_entry kaleido_functions[] = {
    PHP_ME(kaleido, __construct, kaleido_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(kaleido, add, kaleido_add, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, generate, kaleido_generate, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, quality, kaleido_set_quality, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, imageDelay, kaleido_image_delay, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, animateTime, kaleido_animate_time, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, animateFrameCount, kaleido_animate_frame_count, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, clear, kaleido_no_args, ZEND_ACC_PUBLIC)
    PHP_ME(kaleido, __destruct, kaleido_no_args, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    {NULL, NULL, NULL}
};

static zend_object* libra_kaleido_new(zend_class_entry *ce)  {
    kaleido_t *k = (kaleido_t*)emalloc(sizeof(kaleido_t) + zend_object_properties_size(ce));

    memset(k, 0, XtOffsetOf(kaleido_t, std));
    zend_object_std_init(&k->std, ce);

    k->std.handlers = &kaleido_object_handlers;
    if (UNEXPECTED(ce->default_properties_count)) {
        object_properties_init(&k->std, ce);
    }

    return &k->std;
}

static void libra_kaleido_free(zend_object *object) {
    zend_object_std_dtor(object);
}

LIBRA_STARTUP_FUNCTION(kaleido) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Libra\\Kaleido", kaleido_functions);
    kaleido_ce = zend_register_internal_class(&ce TSRMLS_CC);
    kaleido_ce->create_object = libra_kaleido_new;

    memcpy(&kaleido_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

    kaleido_object_handlers.free_obj = libra_kaleido_free;
    kaleido_object_handlers.clone_obj = NULL;

    zend_declare_class_constant_long(kaleido_ce, "HORIZENTAL", sizeof("HORIZENTAL") - 1, libra::Kaleido::Horizontal TSRMLS_CC);
    zend_declare_class_constant_long(kaleido_ce, "VERTICAL", sizeof("VERTICAL") - 1, libra::Kaleido::Vertical TSRMLS_CC);

    return SUCCESS;
}
