//
// Created by 王振浩 on 2020/11/20.
//

#include "libra_container.h"
#include "libra_logger.h"
#include <iostream>

zend_class_entry *libra_container_ce;
zend_object_handlers libra_container_object_handlers;

ZEND_BEGIN_ARG_INFO_EX(libra_container_set_logger, 0, 0, 1)
    ZEND_ARG_INFO(0, logger)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(libra_container_no_args, 0, 0, 0)
    ZEND_ARG_INFO(0, logger)
ZEND_END_ARG_INFO()

PHP_METHOD(container, __construct) {
}

PHP_METHOD(container, instance) {
    ZEND_PARSE_PARAMETERS_NONE();
    zval *container = libra_container_instance();

    ZVAL_OBJ(return_value, &Z_LIBRA_P(container)->std);
    Z_ADDREF_P(return_value);
}

PHP_METHOD(container, setLogger) {
    zval *logger;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS(logger, libra_logger_interface_ce)
    ZEND_PARSE_PARAMETERS_END();

    zval *container = libra_container_instance();
    libra::Container *c = Z_LIBRA_CONTAINER_P(container);

    c->setLogger(new libra::Logger(logger));
}

zend_function_entry libra_container_functions[] = {
    PHP_ME(container, __construct, libra_container_no_args, ZEND_ACC_PRIVATE|ZEND_ACC_CTOR)
    PHP_ME(container, instance, libra_container_no_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
    PHP_ME(container, setLogger, libra_container_set_logger, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
    {NULL, NULL, NULL}
};

static zval *libra_container_instance()  {
    if (EXPECTED(Z_TYPE(LIBRA_G(container)) == IS_OBJECT)) {
        return &LIBRA_G(container);
    }

    libra_object *container;
    container = (libra_object *)zend_object_alloc(sizeof(libra_object), libra_container_ce);
    zend_object_std_init(&container->std, libra_container_ce);

    container->std.handlers = &libra_container_object_handlers;
    container->ptr = libra::Container::instance();

    ZVAL_OBJ(&LIBRA_G(container), &container->std);

    return &LIBRA_G(container);
}

LIBRA_STARTUP_FUNCTION(container) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra", "Container", libra_container_functions);
    libra_container_ce = zend_register_internal_class(&ce TSRMLS_CC);
    libra_container_ce->ce_flags |= ZEND_ACC_FINAL;

    libra_object_handlers_init(&libra_container_object_handlers);

    return SUCCESS;
}
