//
// Created by 王振浩 on 2020/11/14.
//

#include "Container.h"
#include "Mux.h"
#include "Sequence.h"
#include "Image.h"
#include "Utils.h"

namespace libra {
    bool Sequence::generate(const std::string& result) {
        logger->info("Sequence: generate started.");

        Mux* mux = new Mux(width, height, loop);
        int eachFrameStay = duration / frameCount;

        for (int i = 0; i < files->size(); i++) {
            logger->info("processing " + files->at(i));
            // 读取图片
            cv::Mat src, dst;
            cv::Mat* ptr;

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
                Image* img = new Image(src);
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
            bool r = mux->add(&pic, eachFrameStay);
            WebPPictureFree(&pic);
            if (!r) {
                delete mux;
                code = ERR_ADD_FAILED;
                message = "add webp frame failed: " + files->at(i);
                logger->error(message);

                return false;
            }
        }

        // 写文件
        bool r = mux->save(result);
        delete mux;
        if (!r) {
            code = ERR_SAVE_FAILED;
            message = "Sequence: generate failed.";
            logger->error(message);

            return false;
        }

        logger->info("Sequence: generate finished. result is " + result);

        return true;
    }
}
