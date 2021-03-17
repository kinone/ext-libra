//
// Created by 王振浩 on 2021/3/16.
//

#ifndef EXT_LIBRA_LOGGER_H
#define EXT_LIBRA_LOGGER_H

extern "C" {
#include "php.h"
#include "Zend/zend_interfaces.h"
};

#include "ILogger.h"

namespace libra {
    extern const char *LG_DEBUG;
    extern const char *LG_INFO;
    extern const char *LG_ERROR;


    class Logger : public LoggerInterface {
    private:
        void log(const std::string &level, const std::string &message);

    public:
        Logger(zval *v);

        virtual ~Logger();

        virtual void debug(const std::string &message);

        virtual void info(const std::string &message);

        virtual void error(const std::string &message);

    private:
        zval zv;
    };
}


#endif //EXT_LIBRA_LOGGER_H
