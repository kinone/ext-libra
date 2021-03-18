//
// Created by 王振浩 on 2021/03/17.
//

#include "Animate.h"
#include "Container.h"

namespace libra {
    Animate::Animate(uint32_t w, uint32_t h) :
        width(w),
        height(h),
        loop(0),
        frameCount(10),
        quality(60),
        duration(1000),
        code(0),
        message("") {
        files = new std::vector<std::string>;
        logger = Container::instance()->logger();
    }

    Animate::~Animate() {
        clear();
        delete files;
    }

    bool Animate::add(const std::string& image) {
        files->push_back(image);

        logger->info("add file: " + image);

        return true;
    }

    void Animate::clear() {
        files->clear();
    }

    bool Animate::setFrameCount(uint32_t f) {
        frameCount = f;

        return true;
    }

    bool Animate::setLoop(uint32_t l) {
        loop = l;

        return true;
    }

    bool Animate::setQuality(uint32_t q) {
        quality = q;

        return true;
    }

    bool Animate::setDuration(uint32_t t) {
        if (t < 100 || t > 5000) {
            return false;
        }

        duration = t;

        return true;
    }

    const std::string& Animate::lastError() const {
        return message;
    }

    int Animate::lastErrorCode() const {
        return code;
    }

    bool Animate::checkWH(const cv::Mat& m) const {
        if (m.cols != width || m.rows != height) {
            return false;
        }

        return true;
    }
}