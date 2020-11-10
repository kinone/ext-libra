/* libra extension for PHP */

#ifndef PHP_LIBRA_H
# define PHP_LIBRA_H

#include "php.h"

# define phpext_libra_ptr &libra_module_entry

# define PHP_LIBRA_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_LIBRA)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#define LIBRA_STARTUP_FUNCTION(module)    ZEND_MINIT_FUNCTION(libra_##module)
#define LIBRA_STARTUP(module)             ZEND_MINIT(libra_##module)(INIT_FUNC_ARGS_PASSTHRU)

PHP_RINIT_FUNCTION(libra);

PHP_RSHUTDOWN_FUNCTION(libra);

PHP_MINFO_FUNCTION(libra);

PHP_MINIT_FUNCTION(libra);

PHP_MSHUTDOWN_FUNCTION(libra);

#endif    /* PHP_LIBRA_H */

