//
// Created by 王振浩 on 2020/11/18.
//
#include "libra_logger.h"

zend_class_entry *libra_logger_ce;

ZEND_BEGIN_ARG_INFO_EX(logger_log, 0, 0, 3)
    ZEND_ARG_INFO(0, level)
    ZEND_ARG_INFO(0, message)
    ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(logger_level_log, 0, 0, 2)
    ZEND_ARG_INFO(0, message)
    ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

static const zend_function_entry libra_logger_functions[] = {
    ZEND_ABSTRACT_ME(logger, log, logger_log)
    ZEND_ABSTRACT_ME(logger, debug, logger_level_log)
    ZEND_ABSTRACT_ME(logger, info, logger_level_log)
    ZEND_ABSTRACT_ME(logger, notice, logger_level_log)
    ZEND_ABSTRACT_ME(logger, warning, logger_level_log)
    ZEND_ABSTRACT_ME(logger, error, logger_level_log)
    ZEND_ABSTRACT_ME(logger, critical, logger_level_log)
    ZEND_ABSTRACT_ME(logger, alert, logger_level_log)
    ZEND_ABSTRACT_ME(logger, emergency, logger_level_log)
    {NULL, NULL, NULL}
};

LIBRA_STARTUP_FUNCTION(logger) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra", "LoggerInterface", libra_logger_functions);
    libra_logger_ce = zend_register_internal_interface(&ce);

    return SUCCESS;
}