//
// Created by 王振浩 on 2020/10/30.
//

#include "Kaleido.h"
#include "Utils.h"
#include "Image.h"

namespace libra {
    Kaleido::Kaleido(uint32_t width, uint32_t height, uint8_t direction) : width(width), height(height),
                                                                           direction(direction) {
        this->images = new std::vector<cv::Mat>();
        this->animateFrameCount = 10;
        this->animateTime = 1000;
        this->eachImageStay = 1000;
        this->quality = 100;
    }

    Kaleido::~Kaleido() {
        this->clear();
        delete this->images;
    }

    bool Kaleido::add(const std::string &file) {
        cv::Mat image = imread(file, cv::IMREAD_UNCHANGED);

        if (image.cols == 0 || image.rows == 0) {
            return false;
        }

        if (this->images->size() == 0) { // 记录第一张的图片类型
            this->type = image.type();
        } else {
            if (image.type() != this->type) { // 与第一张的图片类型不一致
                return false;
            }
        }

        if (image.cols != this->width || image.rows != this->height) {
            // 调整图片尺寸
            Image *o = new Image(image);
            o->resize(this->width, this->height);
            this->images->push_back(o->destination());
            delete o;
        } else {
            this->images->push_back(image);
        }

        return true;
    }

    void Kaleido::clear() {
        this->images->clear();
    }

    bool Kaleido::setAnimateTime(int time) {
        if (time < 100 || time > 5000) {
            return false;
        }

        this->animateTime = time;

        return true;
    }

    bool Kaleido::setFrameCount(int count) {
        if (count < 1 || count > 20) {
            return false;
        }
        this->animateFrameCount = count;

        return true;
    }

    bool Kaleido::setImageStay(int time) {
        if (time < 100 || time > 5000) {
            return false;
        }

        this->eachImageStay = time;

        return true;
    }

    bool Kaleido::setQuality(int q) {
        if (q < 1 || q > 100) {
            return false;
        }

        this->quality = q;

        return true;
    }

    bool Kaleido::setLoop(int loop) {
        if (loop < 0 || loop > 100) {
            return false;
        }

        this->loop = loop;

        return true;
    }

    void Kaleido::generate(const std::string &result) {
        int count = this->images->size();

        WebPAnimEncoderOptions option;
        WebPAnimEncoderOptionsInit(&option);
        option.anim_params.loop_count = this->loop;
        WebPAnimEncoder *enc = WebPAnimEncoderNew(this->width, this->height, &option);

        WebPConfig config;
        WebPConfigInit(&config);

        int timestamp = 0;
        int eachFrameStay = this->animateTime / this->animateFrameCount;
        WebPPicture pic;
        for (int i = 0; i < count; i++) {
            // 添加第一张图片
            Utils::mat2WebPPicture(this->images->at(i), &pic, this->quality);
            WebPAnimEncoderAdd(enc, &pic, timestamp, &config);
            timestamp += this->eachImageStay;
            WebPPictureFree(&pic);

            int next = (i + 1) % count; // 下一张位置
            for (int j = 0; j < this->animateFrameCount; j++) {
                cv::Mat dst;
                if (this->direction == Kaleido::Vertical) {
                    Utils::genFrameV(this->images->at(i), this->images->at(next), dst, j, this->animateFrameCount);
                } else {
                    Utils::genFrameH(this->images->at(i), this->images->at(next), dst, j, this->animateFrameCount);
                }
                Utils::mat2WebPPicture(dst, &pic, this->quality);
                WebPAnimEncoderAdd(enc, &pic, timestamp, &config);
                timestamp += eachFrameStay;
                WebPPictureFree(&pic);
            }
        }

        WebPAnimEncoderAdd(enc, NULL, timestamp, NULL);

        WebPData data;
        WebPDataInit(&data);

        WebPAnimEncoderAssemble(enc, &data);

        FILE *f = fopen(result.data(), "wb");
        fwrite(data.bytes, data.size, 1, f);
        fclose(f);
        WebPDataClear(&data);
        WebPAnimEncoderDelete(enc);
    }
}
