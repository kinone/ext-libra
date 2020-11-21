//
// Created by 王振浩 on 2020/10/30.
//

#include "Container.h"
#include "Kaleido.h"
#include "Utils.h"
#include "Image.h"
#include "Animate.h"

namespace libra {
    Kaleido::Kaleido(uint32_t w, uint32_t h, uint8_t d)
            : width(w),
              height(h),
              direction(d),
              animateFrameCount(10),
              animateTime(1000),
              eachImageStay(1000),
              quality(100) {
        files = new std::vector<std::string>();
    }

    Kaleido::~Kaleido() {
        clear();
        delete files;
    }

    bool Kaleido::add(const std::string &file) {
        files->push_back(file);

        Container::instance()->logger()->info("add image: " + file);

        return true;
    }

    void Kaleido::clear() {
        files->clear();
    }

    bool Kaleido::setAnimateTime(int time) {
        if (time < 100 || time > 5000) {
            return false;
        }

        animateTime = time;

        return true;
    }

    bool Kaleido::setFrameCount(int count) {
        if (count < 1 || count > 20) {
            return false;
        }
        animateFrameCount = count;

        return true;
    }

    bool Kaleido::setImageStay(int time) {
        if (time < 100 || time > 5000) {
            return false;
        }

        eachImageStay = time;

        return true;
    }

    bool Kaleido::setQuality(int q) {
        if (q < 10 || q > 100) {
            return false;
        }

        quality = q;

        return true;
    }

    bool Kaleido::setLoop(int l) {
        if (l < 0 || l > 100) {
            return false;
        }

        loop = l;

        return true;
    }

    bool Kaleido::generate(const std::string &result) {
        Container::instance()->logger()->info("Kaleido: generate started.");
        int count = files->size();
        cv::Mat images[count];

        for (int i = 0; i < count; i++) {
            Container::instance()->logger()->info("read file: " + files->at(i));
            images[i] = cv::imread(files->at(i), cv::IMREAD_UNCHANGED);
            if (images[i].empty()) {
                Container::instance()->logger()->error("error read file: " + files->at(i));
                return false;
            }

            if (i > 0 && images[i].type() != images[0].type()) {
                Container::instance()->logger()->error("type of image not the same: " + files->at(i));
                return false;
            }

            if (!checkWH(images[i])) {
                Container::instance()->logger()->info("resize image: " + files->at(i));
                Image *obj = new Image(images[i]);
                obj->resize(width, height);
                images[i].release();
                obj->exportTo(images[i]);
                delete obj;
            }
        }

        Animate *animate = new Animate(width, height, loop);

        int eachFrameStay = animateTime / animateFrameCount;
        WebPPicture pic;
        bool r;
        for (int i = 0; i < count; i++) {
            // 添加第一张图片
            Utils::mat2WebPPicture(images[i], &pic, quality);
            r = animate->add(&pic, eachImageStay);
            WebPPictureFree(&pic);
            if (!r) {
                Container::instance()->logger()->error("add file error: " + files->at(i));
                return false;
            }

            int next = (i + 1) % count; // 下一张位置
            for (int j = 0; j < animateFrameCount; j++) {
                cv::Mat dst;
                if (direction == Kaleido::Vertical) {
                    Utils::genFrameV(images[i], images[next], dst, j, animateFrameCount);
                } else {
                    Utils::genFrameH(images[i], images[next], dst, j, animateFrameCount);
                }
                Utils::mat2WebPPicture(dst, &pic, quality);
                animate->add(&pic, eachFrameStay);
                WebPPictureFree(&pic);
            }
        }

        // 写文件
        r = animate->save(result);
        delete animate;

        if (!r) {
            Container::instance()->logger()->error("Kaleido: generate failed.");
            return false;
        }

        Container::instance()->logger()->info("Kaleido: generate finished. result is " + result);

        return true;
    }

    bool Kaleido::checkWH(const cv::Mat &m) const {
        if (m.cols != width || m.rows != height) {
            return false;
        }

        return true;
    }
}
