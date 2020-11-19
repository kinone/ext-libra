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

    void Base::registerLogger(zval *l) {
        delete logger;
        logger = new Logger(l);
    }
}
