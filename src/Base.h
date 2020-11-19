//
// Created by 王振浩 on 2020/11/19.
//

#ifndef EXT_LIBRA_BASE_H
#define EXT_LIBRA_BASE_H

#include "src/LoggerInterface.h"
#include "src/NullLogger.h"
#include "src/Logger.h"
#include "php_libra.h"

namespace libra {
    class Base {
    public:
        Base();

        ~Base();

        void registerLogger(zval *logger);

    protected:
        LoggerInterface *logger;
    };
}

#endif //EXT_LIBRA_BASE_H
