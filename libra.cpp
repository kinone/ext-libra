/* libra extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php_libra.h"
#include "libra_container.h"
#include "libra_image.h"
#include "libra_kaleido.h"
#include "libra_sequence.h"
#include "libra_interface.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
    ZEND_PARSE_PARAMETERS_START(0, 0) \
    ZEND_PARSE_PARAMETERS_END()
#endif

ZEND_DECLARE_MODULE_GLOBALS(libra)

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(libra)
{
#if defined(ZTS) && defined(COMPILE_DL_LIBRA)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif

    return SUCCESS;
}
/* }}} */

PHP_RSHUTDOWN_FUNCTION(libra)
{
    return SUCCESS;
}

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(libra)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "libra support", "enabled");
    php_info_print_table_header(2, "libra version", PHP_LIBRA_VERSION);
    php_info_print_table_header(2, "libra author", "zhenhao <phpcandy@163.com>");
    php_info_print_table_end();
}
/* }}} */

PHP_MINIT_FUNCTION(libra)
{
    LIBRA_STARTUP(logger_interface);
    LIBRA_STARTUP(animate_interface);
    LIBRA_STARTUP(container);
    LIBRA_STARTUP(kaleido);
    LIBRA_STARTUP(image);
    LIBRA_STARTUP(sequence);

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(libra)
{
    return SUCCESS;
}

PHP_GINIT_FUNCTION(libra)
{
    memset(libra_globals, 0, sizeof(*libra_globals));
}

/* {{{ libra_module_entry
 */
zend_module_entry libra_module_entry = {
    STANDARD_MODULE_HEADER,
    "libra",                     /* Extension name */
    NULL,                        /* zend_function_entry */
    PHP_MINIT(libra),            /* PHP_MINIT - Module initialization */
    PHP_MSHUTDOWN(libra),        /* PHP_MSHUTDOWN - Module shutdown */
    PHP_RINIT(libra),            /* PHP_RINIT - Request initialization */
    PHP_RSHUTDOWN(libra),        /* PHP_RSHUTDOWN - Request shutdown */
    PHP_MINFO(libra),            /* PHP_MINFO - Module info */
    PHP_LIBRA_VERSION,           /* Version */
    PHP_MODULE_GLOBALS(libra),
    PHP_GINIT(libra),
    NULL,
    NULL,
    STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_LIBRA
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(libra)
#endif

