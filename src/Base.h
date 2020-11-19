//
// Created by 王振浩 on 2020/11/19.
//

#ifndef EXT_LIBRA_BASE_H
#define EXT_LIBRA_BASE_H

#include "src/LoggerInterface.h"
#include "src/NullLogger.h"

namespace libra {
    class Base {
    public:
        Base();

        ~Base();

        void setLogger(LoggerInterface *l);

    protected:
        LoggerInterface *logger;
    };
}

#endif //EXT_LIBRA_BASE_H
