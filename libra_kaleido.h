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

typedef struct {
    std::vector<std::string> *files;
    zend_long width;
    zend_long height;
    zend_long direction;
    zend_long animateFrameCount;
    zend_long animateTime;
    zend_long imageDelay;
    zend_long quality;
    zend_object std;
} kaleido_t;

static libra::Kaleido* newLibraKaileido(kaleido_t *obj) {
    libra::Kaleido *k = new libra::Kaleido(obj->width, obj->height, obj->direction);
    k->setQuality(obj->quality);
    k->setAnimateTime(obj->animateTime);
    k->setFrameCount(obj->animateFrameCount);
    k->setImageStay(obj->imageDelay);

    return k;
}

#define Z_KALEIDO_T(zv)     (kaleido_fetch_object(Z_OBJ(zv)))
#define Z_KALEIDO_P(zv)     Z_KALEIDO_T(*zv)

static zend_always_inline kaleido_t *kaleido_fetch_object(zend_object *obj) {
    return (kaleido_t *)((char*)(obj) - XtOffsetOf(kaleido_t, std));
}

LIBRA_STARTUP_FUNCTION(kaleido);

#endif //LIBRA_LIBRA_KALEIDO_H
