//
// Created by 王振浩 on 2020/11/14.
//

#ifndef EXT_LIBRA_SEQUENCE_H
#define EXT_LIBRA_SEQUENCE_H

#include <vector>
#include <string>
#include "opencv2/imgcodecs.hpp"
#include "ILogger.h"
#include "LibraErrno.h"
#include "Animate.h"

namespace libra {
    class Sequence: public Animate {
    public:
        Sequence(uint32_t w, uint32_t h): Animate(w, h) {}

        ~Sequence(){}

        bool generate(const std::string &result);
    };
}

#endif //EXT_LIBRA_SEQUENCE_H
