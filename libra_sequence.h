//
// Created by 王振浩 on 2020/11/14.
//

#ifndef EXT_LIBRA_LIBRA_SEQUENCE_H
#define EXT_LIBRA_LIBRA_SEQUENCE_H

#include "src/Sequence.h"
#include "php_libra.h"

#define LIBRA_SEQUENCE_P(zv)  ((libra::Sequence *)(Z_LIBRA_P(zv)->ptr))

LIBRA_STARTUP_FUNCTION(sequence);

#endif //EXT_LIBRA_LIBRA_SEQUENCE_H
