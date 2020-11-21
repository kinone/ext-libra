//
// Created by 王振浩 on 2020/10/30.
//

#ifndef LIBRA_KALEIDO_H
#define LIBRA_KALEIDO_H

#include <string>
#include <vector>
#include <opencv2/imgproc.hpp>

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

        bool setFrameCount(int count);

        bool setAnimateTime(int time);

        bool setImageStay(int time);

        bool setQuality(int q);

        bool setLoop(int l);

    private:
        bool checkWH(const cv::Mat &m) const;

        std::vector<std::string> *files;
        uint8_t direction;
        int animateFrameCount;
        int animateTime;
        int eachImageStay;
        int width;
        int height;
        int quality;
        int loop;
    };
}

#endif //LIBRA_KALEIDO_H
