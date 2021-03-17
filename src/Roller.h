//
// Created by 王振浩 on 2021/3/16.
//

#ifndef EXT_LIBRA_ROLLER_H
#define EXT_LIBRA_ROLLER_H

#include <string>
#include <vector>
#include "Base.h"

namespace libra {
    class Roller: public Base {
    public:
        Roller(uint32_t w, uint32_t h) : Base(w, h) {}

        ~Roller() {}

        bool add(const std::string &image);

        bool generate(const std::string &sUp, const std::string &sDown);
    };
}

#endif //EXT_LIBRA_ROLLER_H
