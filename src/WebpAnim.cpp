//
// Created by 王振浩 on 2021/03/20.
//

#include <cstdio>
#include <iostream>
#include "WebpAnim.h"

namespace libra {
    WebpAnim::WebpAnim(const std::string& fname) : dec(NULL) {
        WebPDataInit(&data);

        FILE* fp = fopen(fname.c_str(), "rb");
        fseek(fp, 0, SEEK_END);
        size_t fileSize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        uint8_t* buff = (uint8_t*)malloc(fileSize + 1);

        fread(buff, fileSize, 1, fp);
        fclose(fp);

        data.bytes = buff;
        data.size = fileSize;

        dec = WebPAnimDecoderNew(&data, NULL);
        WebPAnimDecoderGetInfo(dec, &info);
    }

    WebpAnim::~WebpAnim() {
        WebPDataClear(&data);
        if (NULL != dec) {
            WebPAnimDecoderDelete(dec);
        }
    }

    size_t WebpAnim::frameCount() {
        return info.frame_count;
    }

    size_t WebpAnim::width() {
        return info.canvas_width;
    }

    size_t WebpAnim::height() {
        return info.canvas_height;
    }

    size_t WebpAnim::loopCount() {
        return info.loop_count;
    }
}