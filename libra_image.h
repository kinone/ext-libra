//
// Created by 王振浩 on 2020/11/10.
//

#ifndef LIBRA_LIBRA_IMAGE_H
#define LIBRA_LIBRA_IMAGE_H

#include "php_libra.h"
#include "src/Image.h"

extern zend_object_handlers libra_image_object_handlers;

typedef struct {
    libra::Image *proto;
    zend_object std;
} libra_image_t;

#define Z_LIBRA_IMAGE_T(zv)     (libra_image_fetch_object(Z_OBJ(zv)))
#define Z_LIBRA_IMAGE_P(zv)     Z_LIBRA_IMAGE_T(*zv)

static zend_always_inline libra_image_t *libra_image_fetch_object(zend_object *obj) {
    return (libra_image_t *)((char*)(obj) - XtOffsetOf(libra_image_t, std));
}

LIBRA_STARTUP_FUNCTION(image);

#endif //LIBRA_LIBRA_IMAGE_H
