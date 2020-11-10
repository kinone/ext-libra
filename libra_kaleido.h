//
// Created by 王振浩 on 2020/11/9.
//

#ifndef LIBRA_LIBRA_KALEIDO_H
#define LIBRA_LIBRA_KALEIDO_H

#include "php_libra.h"
#include "src/Kaleido.h"

extern zend_object_handlers kaleido_object_handlers;

typedef struct {
    libra::Kaleido *proto;
    zend_object std;
} kaleido_t;

#define Z_KALEIDO_T(zv)     (kaleido_fetch_object(Z_OBJ(zv)))
#define Z_KALEIDO_P(zv)     Z_KALEIDO_T(*zv)

static zend_always_inline kaleido_t *kaleido_fetch_object(zend_object *obj) {
    return (kaleido_t *)((char*)(obj) - XtOffsetOf(kaleido_t, std));
}

LIBRA_STARTUP_FUNCTION(kaleido);

#endif //LIBRA_LIBRA_KALEIDO_H
