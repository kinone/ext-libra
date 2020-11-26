//
// Created by 王振浩 on 2020/11/18.
//
#include "libra_interface.h"
#include "src/LibraErrno.h"

zend_class_entry *libra_logger_interface_ce;
zend_class_entry *libra_animate_interface_ce;

static const zend_function_entry libra_logger_interface_functions[] = {
    ZEND_ABSTRACT_ME(logger_interface, debug, logger_level_log)
    ZEND_ABSTRACT_ME(logger_interface, info, logger_level_log)
    ZEND_ABSTRACT_ME(logger_interface, error, logger_level_log)
    {NULL, NULL, NULL}
};

LIBRA_STARTUP_FUNCTION(logger_interface) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra", "LoggerInterface", libra_logger_interface_functions);
    libra_logger_interface_ce = zend_register_internal_interface(&ce);

    return SUCCESS;
}

static const zend_function_entry libra_animate_interface_functions[] = {
    ZEND_ABSTRACT_ME(animate_interface, loop, animate_loop)
    ZEND_ABSTRACT_ME(animate_interface, quality, animate_quality)
    ZEND_ABSTRACT_ME(animate_interface, frameCount, animate_frame_count)
    ZEND_ABSTRACT_ME(animate_interface, add, animate_add)
    ZEND_ABSTRACT_ME(animate_interface, generate, animate_generate)
    ZEND_ABSTRACT_ME(animate_interface, clear, animate_noargs)
    ZEND_ABSTRACT_ME(animate_interface, errorCode, animate_noargs)
    ZEND_ABSTRACT_ME(animate_interface, errorInfo, animate_noargs)
    {NULL, NULL, NULL}
};

LIBRA_STARTUP_FUNCTION(animate_interface) {
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "Libra", "AnimateInterface", libra_animate_interface_functions);
    libra_animate_interface_ce = zend_register_internal_interface(&ce);

    zend_declare_class_constant_long(libra_animate_interface_ce, "E_READ_FAILED", sizeof("E_READ_FAILED") - 1, libra::ERR_READ_FAILED TSRMLS_CC);
    zend_declare_class_constant_long(libra_animate_interface_ce, "E_TYPE_DIFFERENT", sizeof("E_TYPE_DIFFERENT") - 1, libra::ERR_TYPE_DIFFERENT TSRMLS_CC);
    zend_declare_class_constant_long(libra_animate_interface_ce, "E_RESIZE_FAILED", sizeof("E_RESIZE_FAILED") - 1, libra::ERR_RESIZE_FAILED TSRMLS_CC);
    zend_declare_class_constant_long(libra_animate_interface_ce, "E_ADD_FAILED", sizeof("E_ADD_FAILED") - 1, libra::ERR_ADD_FAILED TSRMLS_CC);
    zend_declare_class_constant_long(libra_animate_interface_ce, "E_SAVE_FAILED", sizeof("E_SAVE_FAILED") - 1, libra::ERR_SAVE_FAILED TSRMLS_CC);

    return SUCCESS;
}