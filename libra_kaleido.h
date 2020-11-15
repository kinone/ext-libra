//
// Created by 王振浩 on 2020/11/9.
//

#ifndef LIBRA_LIBRA_KALEIDO_H
#define LIBRA_LIBRA_KALEIDO_H

#include <string>
#include <vector>
#include "php_libra.h"
#include "src/Kaleido.h"

extern zend_object_handlers kaleido_object_handlers;

#define Z_KALEIDO_P(zv) ((libra::Kaleido *)Z_LIBRA_INNER_P(zv))

LIBRA_STARTUP_FUNCTION(kaleido);

#endif //LIBRA_LIBRA_KALEIDO_H
