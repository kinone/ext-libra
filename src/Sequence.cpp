//
// Created by 王振浩 on 2020/11/14.
//

#include "Container.h"
#include "Animate.h"
#include "Sequence.h"
#include "Image.h"
#include "Utils.h"

namespace libra {
    Sequence::Sequence(int32_t w, int32_t h) : width(w),
                                               height(h),
                                               frameCount(10),
                                               quality(100),
                                               loop(0) {
        files = new std::vector<std::string>();
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
        Container::instance()->logger()->info("add file " + file);
        files->push_back(file);

        return true;
    }

    bool Sequence::generate(const std::string &result) {
        Container::instance()->logger()->info("Sequence: generate started.");

        Animate *animate = new Animate(width, height, loop);
        int eachFrameStay = 1000 / frameCount;

        for (int i = 0; i < files->size(); i++) {
            Container::instance()->logger()->info("processing " + files->at(i));
            // 读取图片
            cv::Mat src, dst;
            cv::Mat *ptr;

            src = cv::imread(files->at(i), cv::IMREAD_UNCHANGED);
            if (src.empty()) {
                Container::instance()->logger()->error("image read error: " + files->at(i));
                return false;
            }

            ptr = &src;
            // 调整尺寸
            if (!checkWH(src)) {
                Image *img = new Image(src);
                img->resize(width, height);
                img->exportTo(dst);
                ptr = &dst;
            }

            if (ptr->empty()) {
                Container::instance()->logger()->error("resize error: " + files->at(i));
                return false;
            }

            // 转webp并调整质量
            WebPPicture pic;
            Utils::mat2WebPPicture(*ptr, &pic, quality);
            animate->add(&pic, eachFrameStay);
            WebPPictureFree(&pic);
        }

        // 写文件
        animate->save(result);

        delete animate;

        Container::instance()->logger()->info("Sequence: generate finished. result is " + result);

        return true;
    }

    bool Sequence::checkWH(const cv::Mat &m) const {
        if (m.cols != width || m.rows != height) {
            return false;
        }

        return true;
    }
}
