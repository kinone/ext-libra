//
// Created by 王振浩 on 2020/11/18.
//

#ifndef LIBRA_LIBRA_INTERFACE_H
#define LIBRA_LIBRA_INTERFACE_H

#include "php_libra.h"

extern zend_class_entry *libra_logger_interface_ce;
extern zend_class_entry *libra_animate_interface_ce;

LIBRA_STARTUP_FUNCTION(logger_interface);

ZEND_BEGIN_ARG_INFO_EX(logger_level_log, 0, 0, 1)
    ZEND_ARG_INFO(0, message)
    ZEND_ARG_ARRAY_INFO(0, context, false)
ZEND_END_ARG_INFO()

LIBRA_STARTUP_FUNCTION(animate_interface);

ZEND_BEGIN_ARG_INFO_EX(animate_loop, 0, 0, 1)
    ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(animate_quality, 0, 0, 1)
    ZEND_ARG_INFO(0, quality)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(animate_frame_count, 0, 0, 1)
    ZEND_ARG_INFO(0, count)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(animate_add, 0, 0, 1)
    ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(animate_generate, 0, 0, 1)
    ZEND_ARG_INFO(0, result)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(animate_noargs, 0, 0, 0)
ZEND_END_ARG_INFO()

#endif //LIBRA_LIBRA_INTERFACE_H
