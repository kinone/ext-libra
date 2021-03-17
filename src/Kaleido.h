//
// Created by 王振浩 on 2020/10/30.
//

#ifndef LIBRA_KALEIDO_H
#define LIBRA_KALEIDO_H

#include <string>
#include <vector>
#include <opencv2/imgproc.hpp>
#include "ILogger.h"
#include "LibraErrno.h"
#include "Base.h"

namespace libra {
    class Kaleido: public Base {
    public:
        static const uint8_t Horizontal = 0;
        static const uint8_t Vertical = 1;

        Kaleido(uint32_t w, uint32_t h, uint8_t d);

        ~Kaleido();

        bool generate(const std::string &result);

        bool setImageStay(uint32_t time);

    private:
        uint8_t direction;
        uint32_t eachImageStay;
    };
}

#endif //LIBRA_KALEIDO_H
