//
// Created by 王振浩 on 2020/11/19.
//

#ifndef EXT_LIBRA_NULLLOGGER_H
#define EXT_LIBRA_NULLLOGGER_H

#include "AbstractLogger.h"

namespace libra {
    class NullLogger: public AbstractLogger {
    public:
        virtual ~NullLogger();

        virtual void debug(const std::string &message, void *context = NULL);

        virtual void info(const std::string &message, void *context = NULL);

        virtual void error(const std::string &message, void *context = NULL);
    };
}

#endif //EXT_LIBRA_NULLLOGGER_H
