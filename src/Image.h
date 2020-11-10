//
// Created by 王振浩 on 2020/11/3.
//

#ifndef LIBRA_IMAGE_H
#define LIBRA_IMAGE_H

#include <strings.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace libra {

    class Image {
    public:
        Image(std::string file);

        Image(cv::Mat src);

        cv::Mat destination();

        void resize(int width, int height);

        void compressJpeg(std::string file, int q);

        void compressPng(std::string file, int level);

        void download(std::string file);

        int getWidth();

        int getHeight();

    private:
        cv::Mat src;
        cv::Mat dst;
        int width;
        int height;
    };
}

#endif //LIBRA_IMAGE_H
