//
// Created by 王振浩 on 2020/11/18.
//

#ifndef LIBRA_LIBRA_LOGGER_H
#define LIBRA_LIBRA_LOGGER_H

#include "php_libra.h"

extern zend_class_entry *libra_logger_interface_ce;

LIBRA_STARTUP_FUNCTION(logger_interface);

ZEND_BEGIN_ARG_INFO_EX(libra_set_logger, 0, 0, 1)
    ZEND_ARG_INFO(0, logger)
ZEND_END_ARG_INFO()

#endif //LIBRA_LIBRA_LOGGER_H
