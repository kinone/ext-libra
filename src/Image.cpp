//
// Created by 王振浩 on 2020/11/3.
//

#include "Image.h"

namespace libra {
    Image::Image(std::string file) {
        this->src = cv::imread(file, cv::IMREAD_UNCHANGED);
        this->width = this->src.cols;
        this->height = this->src.rows;
    }

    Image::Image(cv::Mat src) {
        this->src = src;
        this->width = this->src.cols;
        this->height = this->src.rows;
    }

    void Image::resize(int width, int height) {
        float fx = double(width) / this->width;
        float fy = double(height) / this->height;

        cv::Mat dst;
        cv::Rect r;
        if (fx >= fy) { // 按宽进行等比例压缩
            int h = int(this->height * fx);
            cv::resize(this->src, dst, cv::Size(width, h));

            int top = (h - height) / 2;
            r = cv::Rect(0, top, width, height);
        } else { // 按高进行等比例压缩
            int w = int(this->width * fy);
            cv::resize(this->src, dst, cv::Size(w, height));

            int left = (w - width) / 2;
            r = cv::Rect(left, 0, width, height);
        }
        // 截取
        this->dst = dst(r);

        this->width = width;
        this->height = height;
    }

    void Image::compressJpeg(std::string file, int q) {
        std::vector<int> params;
        params.push_back(cv::IMWRITE_JPEG_QUALITY);
        params.push_back(q);

        cv::imwrite(file, this->src, params);
    }

    void Image::compressPng(std::string file, int level) {
        std::vector<int> params;
        params.push_back(cv::IMWRITE_PNG_COMPRESSION);
        params.push_back(level);

        cv::imwrite(file, this->src, params);
    }

    cv::Mat Image::destination() {
        return this->dst;
    }

    void Image::download(std::string file) {
        if (this->dst.cols == 0) {
            cv::imwrite(file, this->src);
        } else {
            cv::imwrite(file, this->dst);
        }
    }

    int Image::getWidth() {
        return this->width;
    }

    int Image::getHeight() {
        return this->height;
    }
}