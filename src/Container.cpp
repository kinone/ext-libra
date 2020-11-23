//
// Created by 王振浩 on 2020/11/20.
//

#include "Container.h"

namespace libra {
    Container *Container::self = NULL;

    Container::Container() {
        driver = new NullLogger();
    }

    Container::~Container() {
        delete driver;
    }

    Container *Container::instance() {
        if (NULL == Container::self) {
            Container::self = new Container();
        }

        return Container::self;
    }

    void Container::setLogger(zval *l) {
        delete driver;
        driver = new Logger(l);
    }

    LoggerInterface *Container::logger() {
        return driver;
    }
}