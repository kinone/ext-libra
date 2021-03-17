//
// Created by 王振浩 on 2021/3/16.
//

#ifndef EXT_LIBRA_LIBRA_ROLLER_H
#define EXT_LIBRA_LIBRA_ROLLER_H

#include "php_libra.h"
#include "src/Roller.h"

extern zend_object_handlers libra_roller_object_handlers;

#define Z_LIBRA_ROLLER_P(zv) ((libra::Roller *)Z_LIBRA_INNER_P(zv))

LIBRA_STARTUP_FUNCTION(roller);

#endif //EXT_LIBRA_LIBRA_ROLLER_H
