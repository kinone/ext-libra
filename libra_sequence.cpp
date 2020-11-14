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

PHP_METHOD(sequence, __construct) {
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();

    std::cout << "sequence::__construct" << std::endl;
    libra_sequence_t *obj = Z_LIBRA_SEQUENCE_P(getThis());
    obj->files = new std::vector<std::string>();
}

PHP_METHOD(sequence, __destruct) {
    std::cout << "sequence::__destruct" << std::endl;
    libra_sequence_t *obj = Z_LIBRA_SEQUENCE_P(getThis());
    obj->files->clear();
}

static const zend_function_entry libra_sequence_functions[] = {
    PHP_ME(sequence, __construct, sequence_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(sequence, __destruct, sequence_destruct, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    {NULL, NULL, NULL}
};

static zend_object* libra_sequence_new(zend_class_entry *ce)  {
    std::cout << "libra_sequence_new" << std::endl;
    libra_sequence_t *k = (libra_sequence_t *)emalloc(sizeof(libra_sequence_t) + zend_object_properties_size(ce));

    memset(k, 0, XtOffsetOf(libra_sequence_t , std));
    zend_object_std_init(&k->std, ce);

    k->std.handlers = &libra_sequence_object_handlers;
    if (UNEXPECTED(ce->default_properties_count)) {
        object_properties_init(&k->std, ce);
    }

    return &k->std;
}

static void libra_sequence_free(zend_object *object) {
    std::cout << "libra_sequence_free" << std::endl;
    zend_object_std_dtor(object);
}

LIBRA_STARTUP_FUNCTION(sequence) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Libra\\Sequence", libra_sequence_functions);
    libra_sequence_ce = zend_register_internal_class(&ce TSRMLS_CC);
    libra_sequence_ce->create_object = libra_sequence_new;

    memcpy(&libra_sequence_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

    libra_sequence_object_handlers.free_obj = libra_sequence_free;
    libra_sequence_object_handlers.clone_obj = NULL;

    return SUCCESS;
}

