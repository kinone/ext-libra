//
// Created by 王振浩 on 2020/11/20.
//

#include "Mux.h"
#include "Container.h"

namespace libra {
    Mux::Mux(int width, int height, int loop) : timestamp(0) {
        WebPConfigInit(&config);
        WebPAnimEncoderOptionsInit(&animEncoderOpt);
        animEncoderOpt.anim_params.loop_count = loop;
        animEncoder = WebPAnimEncoderNew(width, height, &animEncoderOpt);

        logger = Container::instance()->logger();
    }

    Mux::~Mux() {
        WebPAnimEncoderDelete(animEncoder);
    }

    bool Mux::add(WebPPicture *pic, int dtime) {
        int r = WebPAnimEncoderAdd(animEncoder, pic, timestamp, &config);

        if (r == 0) {
            const char *err = WebPAnimEncoderGetError(animEncoder);
            logger->error(err);
            return false;
        }

        timestamp += dtime;

        return true;
    }

    bool Mux::save(const std::string &file) {
        WebPAnimEncoderAdd(animEncoder, NULL, timestamp, NULL);

        WebPData data;
        WebPDataInit(&data);

        int r = WebPAnimEncoderAssemble(animEncoder, &data);
        if (r == 0) {
            const char *err = WebPAnimEncoderGetError(animEncoder);
            logger->error(err);
            WebPDataClear(&data);
            return false;
        }

        FILE *f = fopen(file.data(), "wb");
        fwrite(data.bytes, data.size, 1, f);
        fclose(f);

        WebPDataClear(&data);

        return true;
    }
}