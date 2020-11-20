//
// Created by 王振浩 on 2020/11/20.
//

#include "Animate.h"

namespace libra {
    Animate::Animate(int width, int height, int loop) : timestamp(0) {
        WebPConfigInit(&config);
        WebPAnimEncoderOptionsInit(&animEncoderOpt);

        animEncoderOpt.anim_params.loop_count = loop;

        animEncoder = WebPAnimEncoderNew(width, height, &animEncoderOpt);
    }

    Animate::~Animate() {
        WebPAnimEncoderDelete(animEncoder);
    }

    void Animate::add(WebPPicture *pic, int dtime) {
        WebPAnimEncoderAdd(animEncoder, pic, timestamp, &config);
        timestamp += dtime;
    }

    void Animate::save(const std::string &file) {
        WebPAnimEncoderAdd(animEncoder, NULL, timestamp, NULL);

        WebPData data;
        WebPDataInit(&data);

        WebPAnimEncoderAssemble(animEncoder, &data);
        FILE *f = fopen(file.data(), "wb");
        fwrite(data.bytes, data.size, 1, f);
        fclose(f);

        WebPDataClear(&data);
    }
}