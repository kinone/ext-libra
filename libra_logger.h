//
// Created by 王振浩 on 2020/11/18.
//

#ifndef LIBRA_LIBRA_LOGGER_H
#define LIBRA_LIBRA_LOGGER_H

#include "php_libra.h"

extern zend_class_entry *libra_logger_interface_ce;

LIBRA_STARTUP_FUNCTION(logger_interface);

#endif //LIBRA_LIBRA_LOGGER_H
