//
// Created by 王振浩 on 2020/11/20.
//

#ifndef EXT_LIBRA_LIBRA_CONTAINER_H
#define EXT_LIBRA_LIBRA_CONTAINER_H

#include "php_libra.h"
#include "src/Container.h"

extern zend_object_handlers libra_container_object_handlers;

#define Z_LIBRA_CONTAINER_P(zv)  ((libra::Container *)Z_LIBRA_INNER_P(zv))

LIBRA_STARTUP_FUNCTION(container);

static zval *libra_container_instance();

#endif //EXT_LIBRA_LIBRA_CONTAINER_H
