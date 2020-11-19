//
// Created by 王振浩 on 2020/11/18.
//

#ifndef EXT_LIBRA_LOGGER_H
#define EXT_LIBRA_LOGGER_H

#include <string>
#include "src/LoggerInterface.h"

namespace libra {
    class Logger: public LoggerInterface {
    public:
        Logger(zval *v);
        ~Logger();

        virtual void debug(const std::string &message, zend_array *context = NULL);

        virtual void info(const std::string &message, zend_array *context = NULL);

        virtual void error(const std::string &message, zend_array *context = NULL);
    private:
        zval zv;
    };
}

#endif //EXT_LIBRA_LOGGER_H
