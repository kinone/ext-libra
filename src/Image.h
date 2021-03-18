//
// Created by 王振浩 on 2020/11/3.
//

#ifndef LIBRA_IMAGE_H
#define LIBRA_IMAGE_H

#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace libra {
    class Image {
    public:
        Image(const std::string& file);

        Image(const cv::Mat& src);

        ~Image();

        void exportTo(cv::Mat& ret);

        void resize(int fx, int fy);

        void compressJpeg(const std::string& file, int q);

        void compressWebp(const std::string& file, int q);

        void compressPng(const std::string& file, int level);

        void save(const std::string& file);

        int getWidth() const;

        int getHeight() const;

        int type() const;

    private:
        cv::Mat src;
        cv::Mat dst;
        int width;
        int height;
    };
}

#endif //LIBRA_IMAGE_H
