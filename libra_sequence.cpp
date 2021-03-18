//
// Created by 王振浩 on 2020/11/14.
//
#include "libra_sequence.h"
#include "libra_interface.h"
#include "libra_animate.h"

zend_class_entry *libra_sequence_ce;
zend_object_handlers libra_sequence_object_handlers;

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

static const zend_function_entry libra_sequence_functions[] = {
    PHP_ME(sequence, __construct, animate_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(sequence, generate, animate_generate, ZEND_ACC_PUBLIC)
    PHP_ME(sequence, __destruct, animate_destruct, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    {NULL, NULL, NULL}
};

static zend_object *libra_sequence_new(zend_class_entry *ce)  {
    return libra_object_new(ce, &libra_sequence_object_handlers);
}

LIBRA_STARTUP_FUNCTION(sequence) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra", "Sequence", libra_sequence_functions);
    libra_sequence_ce = zend_register_internal_class_ex(&ce, libra_animate_ce TSRMLS_CC);
    libra_sequence_ce->create_object = libra_sequence_new;

    libra_object_handlers_init(&libra_sequence_object_handlers);

    return SUCCESS;
}

