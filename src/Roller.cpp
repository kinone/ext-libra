//
// Created by 王振浩 on 2021/3/16.
//

#include "Roller.h"
#include "Utils.h"
#include "Image.h"
#include "LibraErrno.h"
#include "Mux.h"

namespace libra {
    bool Roller::add(const std::string &image) {
        if (files->size() >= 2) {
            return false;
        }

        return Animate::add(image);
    }

    bool Roller::generate(const std::string &dstUp, const std::string &dstDown) {
        if (files->size() < 2) {
            return false;
        }

        cv::Mat images[2];
        
        for (int i = 0; i < 2; i++) {
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
                Image *obj = new Image(images[i]);
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

        uint32_t dtime = animateTime / frameCount;

        Mux *muxUp = new Mux(width, height, 1);
        Mux *muxDown = new Mux(width, height, 1);

        // 生成中间帧
        WebPPicture pic[frameCount];
        for (int i = 0; i < frameCount; i++) {
            cv::Mat dst;
            Utils::genFrameV(images[1], images[0], dst, i, frameCount);
            Utils::mat2WebPPicture(dst, &pic[i], quality);
        }
        // 上翻vs下翻
        for (int i = 0; i < frameCount; i++) {
            muxUp->add(&pic[frameCount - 1 - i], dtime);
            muxDown->add(&pic[i], dtime);
        }

        bool b1 = muxUp->save(dstUp);
        bool b2 = muxDown->save(dstDown);

        delete muxUp;
        delete muxDown;

        return b1 && b2;
    }
}