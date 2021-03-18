//
// Created by 王振浩 on 2020/11/20.
//

#ifndef EXT_LIBRA_LIBRA_ANIMATE_H
#define EXT_LIBRA_LIBRA_ANIMATE_H

#include "php_libra.h"

extern zend_class_entry* libra_animate_ce;
extern zend_object_handlers libra_animate_object_handlers;

#define Z_LIBRA_ANIMATE_P(zv) ((libra::Animate *)Z_LIBRA_INNER_P(zv))

LIBRA_STARTUP_FUNCTION(animate);

ZEND_BEGIN_ARG_INFO_EX(animate_construct, 0, 0, 2)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(animate_destruct, 0, 0, 0)
ZEND_END_ARG_INFO()

#endif