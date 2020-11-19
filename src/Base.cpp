//
// Created by 王振浩 on 2020/11/19.
//

#include "Base.h"

namespace libra {
    Base::Base() {
        logger = new NullLogger;
    }

    Base::~Base() {
        delete logger;
    }

    void Base::setLogger(LoggerInterface *l) {
        delete logger;
        logger = l;
    }
}
