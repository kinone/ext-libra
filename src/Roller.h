//
// Created by 王振浩 on 2021/3/16.
//

#ifndef EXT_LIBRA_ROLLER_H
#define EXT_LIBRA_ROLLER_H

#include <string>
#include <vector>
#include "Animate.h"

namespace libra {
    class Roller : public Animate {
    public:
        Roller(uint32_t w, uint32_t h) : Animate(w, h) {}

        ~Roller() {}

        bool add(const std::string& image);

        bool generate(const std::string& dstUp, const std::string& dstDown);
    };
}

#endif //EXT_LIBRA_ROLLER_H
