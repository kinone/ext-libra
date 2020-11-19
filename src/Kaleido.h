//
// Created by 王振浩 on 2020/10/30.
//

#ifndef LIBRA_KALEIDO_H
#define LIBRA_KALEIDO_H

#include <string>
#include <vector>
#include <opencv2/imgproc.hpp>
#include "src/Base.h"

extern "C" {
#include <webp/mux.h>
};

namespace libra {
    class Kaleido : public Base {
    public:
        static const uint8_t Horizontal = 0;
        static const uint8_t Vertical = 1;

        Kaleido(uint32_t width, uint32_t height, uint8_t direction);

        ~Kaleido();

        bool add(const std::string &file);

        void clear();

        void generate(const std::string &result);

        bool setFrameCount(int count);

        bool setAnimateTime(int time);

        bool setImageStay(int time);

        bool setQuality(int q);

        bool setLoop(int loop);

    private:
        std::vector<cv::Mat> *images;
        uint8_t direction;
        int animateFrameCount;
        int animateTime;
        int eachImageStay;
        int width;
        int height;
        int quality;
        int type;
        int loop;
    };
}

#endif //LIBRA_KALEIDO_H
