//
// Created by 王振浩 on 2020/11/3.
//

#ifndef LIBRA_IMAGE_H
#define LIBRA_IMAGE_H

#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include "src/Base.h"

namespace libra {
    class Image : public Base {
    public:
        Image(const std::string &file);

        Image(const cv::Mat &src);

        const cv::Mat& destination();

        void resize(int fx, int fy);

        void compressJpeg(const std::string &file, int q);

        void compressWebp(const std::string &file, int q);

        void compressPng(const std::string &file, int level);

        void download(const std::string &file);

        int getWidth() const;

        int getHeight() const;

    private:
        cv::Mat src;
        cv::Mat dst;
        int width;
        int height;
    };
}

#endif //LIBRA_IMAGE_H
