//
// Created by 王振浩 on 2020/11/19.
//

#ifndef EXT_LIBRA_ABSTRACTLOGGER_H
#define EXT_LIBRA_ABSTRACTLOGGER_H

#include <string>

namespace libra {
    class AbstractLogger {
    public:
        virtual ~AbstractLogger();

        virtual void debug(const std::string &message, void *context = NULL) = 0;

        virtual void info(const std::string &message, void *context = NULL) = 0;

        virtual void error(const std::string &message, void *context = NULL) = 0;
    };
}


#endif //EXT_LIBRA_ABSTRACTLOGGER_H
