//
// Created by 王振浩 on 2020/10/30.
//

#ifndef LIBRA_KALEIDO_H
#define LIBRA_KALEIDO_H

#include <string>
#include <vector>
#include <opencv2/imgproc.hpp>
#include "Logger.h"

namespace libra {
    class Kaleido {
    public:
        static const uint8_t Horizontal = 0;
        static const uint8_t Vertical = 1;

        Kaleido(uint32_t w, uint32_t h, uint8_t d);

        ~Kaleido();

        bool add(const std::string &file);

        void clear();

        bool generate(const std::string &result);

        bool setFrameCount(uint32_t count);

        bool setAnimateTime(uint32_t time);

        bool setImageStay(uint32_t time);

        bool setQuality(uint32_t q);

        bool setLoop(uint32_t l);

    private:
        bool checkWH(const cv::Mat &m) const;

        std::vector<std::string> *files;
        uint8_t direction;
        uint32_t animateFrameCount;
        uint32_t animateTime;
        uint32_t eachImageStay;
        uint32_t width;
        uint32_t height;
        uint32_t quality;
        uint32_t loop;

        LoggerInterface *logger;
    };
}

#endif //LIBRA_KALEIDO_H
