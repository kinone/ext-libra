//
// Created by 王振浩 on 2020/11/18.
//
#include "libra_logger.h"

zend_class_entry *libra_logger_interface_ce;

ZEND_BEGIN_ARG_INFO_EX(logger_level_log, 0, 0, 1)
    ZEND_ARG_INFO(0, message)
    ZEND_ARG_ARRAY_INFO(0, context, false)
ZEND_END_ARG_INFO()

static const zend_function_entry libra_logger_interface_functions[] = {
    ZEND_ABSTRACT_ME(logger_interface, debug, logger_level_log)
    ZEND_ABSTRACT_ME(logger_interface, info, logger_level_log)
    ZEND_ABSTRACT_ME(logger_interface, error, logger_level_log)
    {NULL, NULL, NULL}
};

LIBRA_STARTUP_FUNCTION(logger_interface) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra", "LoggerInterface", libra_logger_interface_functions);
    libra_logger_interface_ce = zend_register_internal_interface(&ce);

    return SUCCESS;
}