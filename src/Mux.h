//
// Created by 王振浩 on 2020/11/20.
//

#ifndef EXT_LIBRA_Mux_H
#define EXT_LIBRA_Mux_H

extern "C" {
#include "webp/mux.h"
#include "webp/encode.h"
};

#include <string>
#include <cstdio>
#include "ILogger.h"

namespace libra {
    class Mux {
    public:
        Mux(int width, int height, int loop);

        ~Mux();

        bool add(WebPPicture *pic, int dtime);

        bool save(const std::string &file);

    private:
        WebPConfig config;
        WebPAnimEncoderOptions animEncoderOpt;
        WebPAnimEncoder *animEncoder;
        int timestamp;

        LoggerInterface *logger;
    };
}

#endif //EXT_LIBRA_Mux_H
