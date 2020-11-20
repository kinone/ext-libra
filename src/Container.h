//
// Created by 王振浩 on 2020/11/20.
//

#ifndef EXT_LIBRA_CONTAINER_H
#define EXT_LIBRA_CONTAINER_H

#include "Logger.h"
#include "AbstractLogger.h"
#include "NullLogger.h"

namespace libra {
    class Container {
    public:
        void setLogger(zval *l);

        AbstractLogger *logger();

        ~Container();

        static Container *instance();

    private:
        Container();

        AbstractLogger *driver;

        static Container *self;

        class Garbo {
        public:
            ~Garbo() {
                if (NULL != Container::self) {
                    delete Container::self;
                    Container::self = NULL;
                }
            }

        };

        static Garbo garbo;
    };
}

#endif //EXT_LIBRA_CONTAINER_H
