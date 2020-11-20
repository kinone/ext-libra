//
// Created by 王振浩 on 2020/11/14.
//

#include "Container.h"
#include "Sequence.h"
#include "Image.h"
#include "Utils.h"

namespace libra {
    Sequence::Sequence(int32_t w, int32_t h) : width(w), height(h), frameCount(10), quality(100), loop(0) {
        files = new std::vector<std::string>();
        logger = Container::instance()->logger();
    }

    Sequence::~Sequence() {
        files->clear();
        delete this->files;
    }

    bool Sequence::setFrameCount(int c) {
        if (c < 1 || c > 50) {
            return false;
        }

        frameCount = c;

        return true;
    }

    bool Sequence::setQuality(int q) {
        if (q < 10 || q > 100) {
            return false;
        }

        quality = q;

        return true;
    }

    bool Sequence::setLoop(int l) {
        if (l < 0 || l > 100) {
            return false;
        }

        loop = l;

        return true;
    }

    bool Sequence::add(const std::string &file) {
        logger->info("add file " + file);
        files->push_back(file);

        return true;
    }

    bool Sequence::generate(const std::string &result) {
        logger->info("start to generate " + result);

        WebPAnimEncoderOptions option;
        WebPAnimEncoderOptionsInit(&option);
        option.anim_params.loop_count = loop;
        WebPAnimEncoder *enc = WebPAnimEncoderNew(this->width, this->height, &option);

        WebPConfig config;
        WebPConfigInit(&config);

        int timestamp = 0;
        int eachFrameStay = 1000 / frameCount;

        for (int i = 0; i < files->size(); i++) {
            logger->info("processing " + files->at(i));
            // 读取图片
            cv::Mat src = cv::imread(files->at(i), cv::IMREAD_UNCHANGED);
            if (src.empty()) {
                logger->error("image read error: " + files->at(i));
                return false;
            }

            // 调整尺寸
            if (!checkWH(src)) {
                Image *img = new Image(src);
                img->resize(width, height);
                src = img->destination();
            }

            // 转webp并调整质量
            WebPPicture pic;
            Utils::mat2WebPPicture(src, &pic, quality);
            WebPAnimEncoderAdd(enc, &pic, timestamp, &config);
            WebPPictureFree(&pic);

            timestamp += eachFrameStay;
        }

        // 空帧
        WebPAnimEncoderAdd(enc, NULL, timestamp, NULL);

        // 写文件
        WebPData data;
        WebPDataInit(&data);
        WebPAnimEncoderAssemble(enc, &data);
        FILE *f = fopen(result.data(), "wb");
        fwrite(data.bytes, data.size, 1, f);
        fclose(f);
        WebPDataClear(&data);
        WebPAnimEncoderDelete(enc);

        logger->info("end to generate " + result);

        return true;
    }

    bool Sequence::checkWH(const cv::Mat &m) const {
        if (m.cols != width || m.rows != height) {
            return false;
        }

        return true;
    }
}
