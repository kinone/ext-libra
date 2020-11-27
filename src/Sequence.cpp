//
// Created by 王振浩 on 2020/11/14.
//

#include "Container.h"
#include "Animate.h"
#include "Sequence.h"
#include "Image.h"
#include "Utils.h"

namespace libra {
    Sequence::Sequence(uint32_t w, uint32_t h) : width(w),
                                               height(h),
                                               frameCount(10),
                                               quality(100),
                                               loop(0),
                                               code(0),
                                               message(""){
        files = new std::vector<std::string>();
        logger = Container::instance()->logger();
    }

    Sequence::~Sequence() {
        clear();
        delete this->files;
    }

    bool Sequence::setFrameCount(uint32_t c) {
        if (c < 1 || c > 50) {
            return false;
        }

        frameCount = c;

        return true;
    }

    bool Sequence::setQuality(uint32_t q) {
        if (q < 10 || q > 100) {
            return false;
        }

        quality = q;

        return true;
    }

    bool Sequence::setLoop(uint32_t l) {
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
        logger->info("Sequence: generate started.");

        Animate *animate = new Animate(width, height, loop);
        int eachFrameStay = 1000 / frameCount;

        for (int i = 0; i < files->size(); i++) {
            logger->info("processing " + files->at(i));
            // 读取图片
            cv::Mat src, dst;
            cv::Mat *ptr;

            src = cv::imread(files->at(i), cv::IMREAD_UNCHANGED);
            if (src.empty()) {
                code = ERR_READ_FAILED;
                message = "image read error: " + files->at(i);

                logger->error(message);

                return false;
            }

            ptr = &src;
            // 调整尺寸
            if (!checkWH(src)) {
                logger->info("resize image: " + files->at(i));
                Image *img = new Image(src);
                img->resize(width, height);
                img->exportTo(dst);
                ptr = &dst;

                if (ptr->empty()) {
                    code = ERR_RESIZE_FAILED;
                    message = "resize image failed: " + files->at(i);
                    logger->error(message);

                    return false;
                }
            }

            // 转webp并调整质量
            WebPPicture pic;
            Utils::mat2WebPPicture(*ptr, &pic, quality);
            bool r = animate->add(&pic, eachFrameStay);
            WebPPictureFree(&pic);
            if (!r) {
                delete animate;
                code = ERR_ADD_FAILED;
                message = "add webp frame failed: " + files->at(i);
                logger->error(message);

                return false;
            }
        }

        // 写文件
        bool r = animate->save(result);
        delete animate;
        if (!r) {
            code = ERR_SAVE_FAILED;
            message = "Sequence: generate failed.";
            logger->error(message);

            return false;
        }

        logger->info("Sequence: generate finished. result is " + result);

        return true;
    }

    void Sequence::clear() {
        files->clear();
    }

    bool Sequence::checkWH(const cv::Mat &m) const {
        if (m.cols != width || m.rows != height) {
            return false;
        }

        return true;
    }

    const std::string & Sequence::lastError() const {
        return message;
    }

    int Sequence::lastErrorCode() const {
        return code;
    }
}
