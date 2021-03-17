//
// Created by 王振浩 on 2021/03/17.
//

#include "Base.h"
#include "Container.h"

namespace libra {
    Base::Base(uint32_t w, uint32_t h): width(w), 
                                        height(h),
                                        loop(0),
                                        frameCount(10),
                                        quality(60),
                                        animateTime(1000),
                                        code(0),
                                        message("") {
        files = new std::vector<std::string>;
        logger = Container::instance()->logger();
    }

    Base::~Base() {
        clear();
        delete files;
    }

    bool Base::add(const std::string &image) {
        files->push_back(image);

        logger->info("add file: " + image);

        return true;
    }

    void Base::clear() {
        files->clear();
    }

    bool Base::setFrameCount(uint32_t f) {
        frameCount = f;

        return true;
    }

    bool Base::setLoop(uint32_t l) {
        loop = l;

        return true;
    }

    bool Base::setQuality(uint32_t q) {
        quality = q;

        return true;
    }

    bool Base::setAnimateTime(uint32_t t) {
        if (t < 100 || t > 5000) {
            return false;
        }

        animateTime = t;

        return true;
    }

    const std::string & Base::lastError() const {
        return message;
    }

    int Base::lastErrorCode() const {
        return code;
    }

    bool Base::checkWH(const cv::Mat &m) const {
        if (m.cols != width || m.rows != height) {
            return false;
        }

        return true;
    }
}