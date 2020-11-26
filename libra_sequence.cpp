//
// Created by 王振浩 on 2020/11/14.
//
#include "libra_sequence.h"
#include "libra_interface.h"

zend_class_entry *libra_sequence_ce;
zend_object_handlers libra_sequence_object_handlers;

ZEND_BEGIN_ARG_INFO_EX(sequence_construct, 0, 0, 2)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(sequence_destruct, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(sequence, __construct) {
    int64_t width;
    int64_t height;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(width)
        Z_PARAM_LONG(height)
    ZEND_PARSE_PARAMETERS_END();

    libra_object *obj = Z_LIBRA_P(getThis());
    obj->ptr = new libra::Sequence(width, height);
}

PHP_METHOD(sequence, __destruct) {
    ZEND_PARSE_PARAMETERS_NONE();

    delete Z_LIBRA_SEQUENCE_P(getThis());
}

PHP_METHOD(sequence, add) {
    char *file;
    size_t len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(file, len);
    ZEND_PARSE_PARAMETERS_END();

    libra::Sequence *s = Z_LIBRA_SEQUENCE_P(getThis());
    bool b = s->add(std::string(file));

    RETURN_BOOL(b)
}

PHP_METHOD(sequence, generate) {
    char *file;
    size_t len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(file, len);
    ZEND_PARSE_PARAMETERS_END();

    libra::Sequence *s = Z_LIBRA_SEQUENCE_P(getThis());
    bool b = s->generate(std::string(file));

    RETURN_BOOL(b)
}

PHP_METHOD(sequence, loop) {
    int64_t l;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(l)
    ZEND_PARSE_PARAMETERS_END();

    libra::Sequence *s = Z_LIBRA_SEQUENCE_P(getThis());
    bool b = s->setLoop(l);

    RETURN_BOOL(b)
}

PHP_METHOD(sequence, quality) {
    int64_t q;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(q)
    ZEND_PARSE_PARAMETERS_END();

    libra::Sequence *s = Z_LIBRA_SEQUENCE_P(getThis());
    bool b = s->setQuality(q);

    RETURN_BOOL(b)
}

PHP_METHOD(sequence, frameCount) {
    int64_t c;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(c)
    ZEND_PARSE_PARAMETERS_END();

    libra::Sequence *s = Z_LIBRA_SEQUENCE_P(getThis());
    bool b = s->setFrameCount(c);

    RETURN_BOOL(b)
}

PHP_METHOD(sequence, clear) {
    ZEND_PARSE_PARAMETERS_NONE();

    libra::Sequence *s = Z_LIBRA_SEQUENCE_P(getThis());
    s->clear();

    RETURN_NULL()
}

PHP_METHOD(sequence, errorCode) {
    ZEND_PARSE_PARAMETERS_NONE();

    libra::Sequence *s = Z_LIBRA_SEQUENCE_P(getThis());
    int64_t code = s->lastErrorCode();

    RETURN_LONG(code)
}

PHP_METHOD(sequence, errorInfo) {
    ZEND_PARSE_PARAMETERS_NONE();

    libra::Sequence *s = Z_LIBRA_SEQUENCE_P(getThis());
    const std::string& msg = s->lastError();

    RETURN_STRINGL(msg.data(), msg.length())
}

static const zend_function_entry libra_sequence_functions[] = {
    PHP_ME(sequence, __construct, sequence_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(sequence, __destruct, sequence_destruct, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    PHP_ME(sequence, add, animate_add, ZEND_ACC_PUBLIC)
    PHP_ME(sequence, generate, animate_generate, ZEND_ACC_PUBLIC)
    PHP_ME(sequence, loop, animate_loop, ZEND_ACC_PUBLIC)
    PHP_ME(sequence, quality, animate_quality, ZEND_ACC_PUBLIC)
    PHP_ME(sequence, frameCount, animate_frame_count, ZEND_ACC_PUBLIC)
    PHP_ME(sequence, clear, animate_noargs, ZEND_ACC_PUBLIC)
    PHP_ME(sequence, errorCode, animate_noargs, ZEND_ACC_PUBLIC)
    PHP_ME(sequence, errorInfo, animate_noargs, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_object *libra_sequence_new(zend_class_entry *ce)  {
    return libra_object_new(ce, &libra_sequence_object_handlers);
}

LIBRA_STARTUP_FUNCTION(sequence) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra", "Sequence", libra_sequence_functions);
    libra_sequence_ce = zend_register_internal_class(&ce TSRMLS_CC);
    libra_sequence_ce->create_object = libra_sequence_new;

    zend_class_implements(libra_sequence_ce, 1, libra_animate_interface_ce);
    libra_object_handlers_init(&libra_sequence_object_handlers);

    return SUCCESS;
}

