//
// Created by 王振浩 on 2020/11/14.
//

#ifndef EXT_LIBRA_SEQUENCE_H
#define EXT_LIBRA_SEQUENCE_H

#include <vector>
#include <string>
#include "opencv2/imgcodecs.hpp"

namespace libra {
    class Sequence {
    public:
        Sequence(int width, int height);

        ~Sequence();

        bool add(const std::string &file);

        bool setFrameCount(int c);

        bool setQuality(int q);

        bool setLoop(int l);

        bool generate(const std::string &result);

    private:
        bool checkWH(const cv::Mat &m) const;

        std::vector<std::string> *files;
        int32_t width;
        int32_t height;
        int32_t loop;
        int32_t frameCount;
        int32_t quality;
    };
}

#endif //EXT_LIBRA_SEQUENCE_H
