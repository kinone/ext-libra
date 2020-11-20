//
// Created by 王振浩 on 2020/10/30.
//

#include "Kaleido.h"
#include "Utils.h"
#include "Image.h"
#include "Animate.h"

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

        if (image.empty()) {
            return false;
        }

        if (images->empty()) { // 记录第一张的图片类型
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
        if (q < 10 || q > 100) {
            return false;
        }

        this->quality = q;

        return true;
    }

    bool Kaleido::setLoop(int l) {
        if (l < 0 || l > 100) {
            return false;
        }

        this->loop = l;

        return true;
    }

    void Kaleido::generate(const std::string &result) {
        int count = this->images->size();
        Animate *animate = new Animate(width, height, loop);

        int eachFrameStay = this->animateTime / this->animateFrameCount;
        WebPPicture pic;
        for (int i = 0; i < count; i++) {
            // 添加第一张图片
            Utils::mat2WebPPicture(this->images->at(i), &pic, this->quality);
            animate->add(&pic, eachImageStay);
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
                animate->add(&pic, eachFrameStay);
                WebPPictureFree(&pic);
            }
        }

        // 写文件
        animate->save(result);

        delete animate;
    }
}
