//
// Created by 王振浩 on 2020/11/18.
//

#ifndef EXT_LIBRA_LOGGER_H
#define EXT_LIBRA_LOGGER_H

extern "C" {
#include "php.h"
#include "Zend/zend_interfaces.h"
};

#include <string>
#include "AbstractLogger.h"

namespace libra {
    extern const char *LG_DEBUG;
    extern const char *LG_INFO;
    extern const char *LG_ERROR;

    class Logger : public AbstractLogger {
    private:
        void log(const std::string &level, const std::string &message);

    public:
        Logger(zval *v);

        ~Logger();

        virtual void debug(const std::string &message);

        virtual void info(const std::string &message);

        virtual void error(const std::string &message);

    private:
        zval zv;
    };
}

#endif //EXT_LIBRA_LOGGER_H
