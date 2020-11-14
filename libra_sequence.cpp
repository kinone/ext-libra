//
// Created by 王振浩 on 2020/11/14.
//
#include "libra_sequence.h"
#include <iostream>

zend_class_entry *libra_sequence_ce;
zend_object_handlers libra_sequence_object_handlers;

ZEND_BEGIN_ARG_INFO_EX(sequence_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(sequence_destruct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(sequence_add, 0, 0, 1)
    ZEND_ARG_INFO(0, "file")
ZEND_END_ARG_INFO()

PHP_METHOD(sequence, __construct) {
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();

    std::cout << "sequence::__construct" << std::endl;
    libra_object *obj = Z_LIBRA_P(getThis());
    obj->ptr = new libra::Sequence();
}

PHP_METHOD(sequence, __destruct) {
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();

    std::cout << "sequence::__destruct" << std::endl;
    delete LIBRA_SEQUENCE_P(getThis());
}

PHP_METHOD(sequence, add) {
    char *file;
    size_t len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(file, len);
    ZEND_PARSE_PARAMETERS_END();

    libra::Sequence *s = LIBRA_SEQUENCE_P(getThis());
    s->add(std::string(file));

    RETURN_NULL();
}

static const zend_function_entry libra_sequence_functions[] = {
    PHP_ME(sequence, __construct, sequence_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(sequence, __destruct, sequence_destruct, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    PHP_ME(sequence, add, sequence_add, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_object *libra_sequence_new(zend_class_entry *ce)  {
    return libra_object_new(ce, &libra_sequence_object_handlers);
}

LIBRA_STARTUP_FUNCTION(sequence) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Libra\\Sequence", libra_sequence_functions);
    libra_sequence_ce = zend_register_internal_class(&ce TSRMLS_CC);
    libra_sequence_ce->create_object = libra_sequence_new;

    libra_object_handlers_init(&libra_sequence_object_handlers);

    return SUCCESS;
}

