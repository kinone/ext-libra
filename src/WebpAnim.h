//
// Created by 王振浩 on 2020/10/31.
//

#ifndef EXT_LIBRA_WEBP_H
#define EXT_LIBRA_WEBP_H

#include <cstddef>
#include <stdint.h>
#include <string>

extern "C" {
    #include <webp/demux.h>
}

namespace libra {
    class WebpAnim
    {
    private:
        WebPData data;
        WebPAnimInfo info;
        WebPAnimDecoder* dec;
    public:
        WebpAnim(const std::string& fname);
        ~WebpAnim();
        size_t frameCount();
        size_t width();
        size_t height();
        size_t loopCount();
    };
}

#endif