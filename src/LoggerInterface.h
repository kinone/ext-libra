//
// Created by 王振浩 on 2020/11/19.
//

#ifndef EXT_LIBRA_LOGGERINTERFACE_H
#define EXT_LIBRA_LOGGERINTERFACE_H

#include <string>

namespace libra {
    class LoggerInterface {
    public:
        virtual ~LoggerInterface();

        virtual void debug(const std::string &message, void *context = NULL) = 0;

        virtual void info(const std::string &message, void *context = NULL) = 0;

        virtual void error(const std::string &message, void *context = NULL) = 0;
    };
}


#endif //EXT_LIBRA_LOGGERINTERFACE_H
