//
// Created by 王振浩 on 2020/11/20.
//

#ifndef EXT_LIBRA_ANIMATE_H
#define EXT_LIBRA_ANIMATE_H

extern "C" {
#include "webp/mux.h"
#include "webp/encode.h"
};

#include <string>
#include <cstdio>

namespace libra {
    class Animate {
    public:
        Animate(int width, int height, int loop);

        ~Animate();

        void add(WebPPicture *pic, int dtime);

        void save(const std::string &file);

    private:
        WebPConfig config;
        WebPAnimEncoderOptions animEncoderOpt;
        WebPAnimEncoder *animEncoder;
        int timestamp;
    };
}

#endif //EXT_LIBRA_ANIMATE_H
