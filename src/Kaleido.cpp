//
// Created by 王振浩 on 2020/10/30.
//

#include "Container.h"
#include "Kaleido.h"
#include "Utils.h"
#include "Image.h"
#include "Mux.h"

namespace libra {
    Kaleido::Kaleido(uint32_t w, uint32_t h, uint8_t d) : Animate(w, h), direction(d), eachImageStay(1000) {
    }

    Kaleido::~Kaleido() {
    }

    bool Kaleido::setImageStay(uint32_t d) {
        if (d < 100 || d > 5000) {
            return false;
        }

        eachImageStay = d;

        return true;
    }

    bool Kaleido::generate(const std::string& result) {
        logger->info("Kaleido: generate started.");
        int count = files->size();

        if (count == 0) {
            logger->error("empty files");
            return false;
        }

        cv::Mat images[count];

        for (int i = 0; i < count; i++) {
            logger->info("read file: " + files->at(i));
            images[i] = cv::imread(files->at(i), cv::IMREAD_UNCHANGED);
            if (images[i].empty()) {
                code = ERR_READ_FAILED;
                message = "error read file: " + files->at(i);
                logger->error(message);
                return false;
            }

            // 3 通道转 4 通道
            if (images[i].channels() == 3) {
                cv::Mat tmp;
                Utils::addAlpha(images[i], tmp);
                images[i] = tmp;
            }

            // 类型检查
            if (i > 0 && images[i].type() != images[0].type()) {
                code = ERR_TYPE_DIFFERENT;
                message = "type of image not the same: " + files->at(i);
                logger->error(message);
                return false;
            }

            // 尺寸调整
            if (!checkWH(images[i])) {
                logger->info("resize image: " + files->at(i));
                Image* obj = new Image(images[i]);
                obj->resize(width, height);
                obj->exportTo(images[i]);
                delete obj;

                if (images[i].empty()) {
                    code = ERR_RESIZE_FAILED;
                    message = "resize image failed: " + files->at(i);
                    logger->error(message);
                    return false;
                }
            }
        }

        Mux* mux = new Mux(width, height, loop);

        uint32_t eachFrameStay = duration / frameCount;
        WebPPicture pic;
        bool r;
        for (int i = 0; i < count; i++) {
            // 添加第一张图片
            Utils::mat2WebPPicture(images[i], &pic, quality);
            r = mux->add(&pic, eachImageStay);
            WebPPictureFree(&pic);
            if (!r) {
                code = ERR_ADD_FAILED;
                message = "add webp frame failed" + files->at(i);
                logger->error(message);
                delete mux;
                return false;
            }

            int next = (i + 1) % count; // 下一张位置
            for (int j = 0; j < frameCount; j++) {
                cv::Mat dst;
                if (direction == Kaleido::Vertical) {
                    Utils::genFrameV(images[i], images[next], dst, j, frameCount);
                }
                else {
                    Utils::genFrameH(images[i], images[next], dst, j, frameCount);
                }
                Utils::mat2WebPPicture(dst, &pic, quality);
                mux->add(&pic, eachFrameStay);
                WebPPictureFree(&pic);
            }
        }

        if (loop > 0) {
            Utils::mat2WebPPicture(images[0], &pic, quality);
            mux->add(&pic, 1);
            WebPPictureInit(&pic);
        }

        // 写文件
        r = mux->save(result);
        delete mux;

        if (!r) {
            code = ERR_SAVE_FAILED;
            message = "Kaleido: generate failed.";
            logger->error(message);
            return false;
        }

        logger->info("Kaleido: generate finished. result is " + result);

        return true;
    }
}
