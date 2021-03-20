//
// Created by 王振浩 on 2021/03/20.
//

#ifndef EXT_LIBRA_LIBRA_WEBP_H
#define EXT_LIBRA_LIBRA_WEBP_H

#include "php_libra.h"
#include "src/WebpAnim.h"

extern zend_object_handlers libra_webpanim_object_handlers;

#define Z_LIBRA_WEBPANIM_P(zv)  ((libra::WebpAnim *)Z_LIBRA_INNER_P(zv))

LIBRA_STARTUP_FUNCTION(webp);

#endif //EXT_LIBRA_LIBRA_WEBP_H