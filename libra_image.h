//
// Created by 王振浩 on 2020/11/10.
//

#ifndef LIBRA_LIBRA_IMAGE_H
#define LIBRA_LIBRA_IMAGE_H

#include "php_libra.h"
#include "src/Image.h"

extern zend_object_handlers libra_image_object_handlers;

#define Z_LIBRA_IMAGE_P(obj)     ((libra::Image *)(Z_LIBRA_P(obj)->ptr))

LIBRA_STARTUP_FUNCTION(image);

#endif //LIBRA_LIBRA_IMAGE_H
