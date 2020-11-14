//
// Created by 王振浩 on 2020/11/14.
//

#ifndef EXT_LIBRA_LIBRA_SEQUENCE_H
#define EXT_LIBRA_LIBRA_SEQUENCE_H

#include "src/Sequence.h"
#include "php_libra.h"
#include <vector>
#include <string>

typedef struct {
    std::vector<std::string> *files;
    zend_object std;
} libra_sequence_t;

#define Z_LIBRA_SEQUENCE_T(zv)     (libra_sequence_fetch_object(Z_OBJ(zv)))
#define Z_LIBRA_SEQUENCE_P(zv)     Z_LIBRA_SEQUENCE_T(*zv)

static zend_always_inline libra_sequence_t *libra_sequence_fetch_object(zend_object *obj) {
    return (libra_sequence_t *)((char*)(obj) - XtOffsetOf(libra_sequence_t, std));
}

LIBRA_STARTUP_FUNCTION(sequence);

#endif //EXT_LIBRA_LIBRA_SEQUENCE_H
