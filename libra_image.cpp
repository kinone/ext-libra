//
// Created by 王振浩 on 2020/11/10.
//
#include "libra_image.h"
#include "libra_logger.h"
#include "src/Logger.h"

zend_class_entry *libra_image_ce;

zend_object_handlers libra_image_object_handlers;

ZEND_BEGIN_ARG_INFO_EX(image_construct, 0, 0, 1)
    ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(image_no_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(image_resize, 0, 0, 3)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, dst)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(image_download, 0, 0, 1)
    ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(image_compress_jpeg, 0, 0, 1)
    ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(image_comperss_png, 0, 0, 1)
    ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

PHP_METHOD(image, __construct) {
    char *file;
    size_t len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(file, len)
    ZEND_PARSE_PARAMETERS_END();

    libra_object *obj = Z_LIBRA_P(getThis());
    obj->ptr = new libra::Image(std::string(file));
}

PHP_METHOD(image, __destruct) {
    delete Z_LIBRA_IMAGE_P(getThis());
}

PHP_METHOD(image, resize) {
    int64_t width;
    int64_t height;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(width);
        Z_PARAM_LONG(height);
    ZEND_PARSE_PARAMETERS_END();

    libra::Image *img = Z_LIBRA_IMAGE_P(getThis());
    img->resize(width, height);

    RETURN_NULL();
}

PHP_METHOD(image, download) {
    char *file;
    size_t len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(file, len)
    ZEND_PARSE_PARAMETERS_END();

    libra::Image *img = Z_LIBRA_IMAGE_P(getThis());
    img->download(file);

    RETURN_NULL();
}

PHP_METHOD(image, compressJpeg) {
    char *file;
    size_t len;
    int64_t q;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(file, len)
        Z_PARAM_LONG(q);
    ZEND_PARSE_PARAMETERS_END();

    libra::Image *img = Z_LIBRA_IMAGE_P(getThis());
    img->compressJpeg(file, q);

    RETURN_NULL();
}

PHP_METHOD(image, compressWebp) {
    char *file;
    size_t len;
    int64_t q;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(file, len)
        Z_PARAM_LONG(q);
    ZEND_PARSE_PARAMETERS_END();

    libra::Image *img = Z_LIBRA_IMAGE_P(getThis());
    img->compressWebp(file, q);

    RETURN_NULL();
}

PHP_METHOD(image, compressPng) {
    char *file;
    size_t len;
    int64_t level;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(file, len)
        Z_PARAM_LONG(level);
    ZEND_PARSE_PARAMETERS_END();

    libra::Image *img = Z_LIBRA_IMAGE_P(getThis());
    img->compressPng(file, level);

    RETURN_NULL();
}

PHP_METHOD(image, getWidth) {
    ZEND_PARSE_PARAMETERS_NONE();

    libra::Image *img = Z_LIBRA_IMAGE_P(getThis());

    RETURN_LONG(img->getWidth());
}

PHP_METHOD(image, getHeight) {
    ZEND_PARSE_PARAMETERS_NONE();

    libra::Image *img = Z_LIBRA_IMAGE_P(getThis());

    RETURN_LONG(img->getHeight());
}

static const zend_function_entry libra_image_functions[] = {
    PHP_ME(image, __construct, image_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(image, __destruct, image_no_args, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    PHP_ME(image, download, image_download, ZEND_ACC_PUBLIC)
    PHP_ME(image, compressPng, image_comperss_png, ZEND_ACC_PUBLIC)
    PHP_ME(image, compressJpeg, image_compress_jpeg, ZEND_ACC_PUBLIC)
    PHP_ME(image, compressWebp, image_compress_jpeg, ZEND_ACC_PUBLIC)
    PHP_ME(image, getWidth, image_no_args, ZEND_ACC_PUBLIC)
    PHP_ME(image, getHeight, image_no_args, ZEND_ACC_PUBLIC)
    PHP_ME(image, resize, image_resize, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_object* libra_image_new(zend_class_entry *ce)  {
    return libra_object_new(ce, &libra_image_object_handlers);
}

LIBRA_STARTUP_FUNCTION(image) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra", "Image", libra_image_functions);
    libra_image_ce = zend_register_internal_class(&ce TSRMLS_CC);
    libra_image_ce->create_object = libra_image_new;

    libra_object_handlers_init(&libra_image_object_handlers);

    return SUCCESS;
}

