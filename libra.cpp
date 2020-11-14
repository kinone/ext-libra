/* libra extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php_libra.h"
#include "libra_image.h"
#include "libra_kaleido.h"
#include "libra_sequence.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
    ZEND_PARSE_PARAMETERS_START(0, 0) \
    ZEND_PARSE_PARAMETERS_END()
#endif

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
    php_info_print_table_end();
}
/* }}} */

PHP_MINIT_FUNCTION(libra)
{
    LIBRA_STARTUP(kaleido);
    LIBRA_STARTUP(image);
    LIBRA_STARTUP(sequence);

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(libra)
{
    return SUCCESS;
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
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_LIBRA
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(libra)
#endif

