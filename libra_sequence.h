//
// Created by 王振浩 on 2020/11/14.
//

#ifndef EXT_LIBRA_LIBRA_SEQUENCE_H
#define EXT_LIBRA_LIBRA_SEQUENCE_H

#include "php_libra.h"
#include "src/Sequence.h"

extern zend_object_handlers libra_sequence_object_handlers;

#define Z_LIBRA_SEQUENCE_P(zv)  ((libra::Sequence *)Z_LIBRA_INNER_P(zv))

LIBRA_STARTUP_FUNCTION(sequence);

#endif //EXT_LIBRA_LIBRA_SEQUENCE_H
