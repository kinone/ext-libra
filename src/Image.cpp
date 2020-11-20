//
// Created by 王振浩 on 2020/11/3.
//

#include "Image.h"

namespace libra {
    Image::Image(const std::string &file) {
        this->src = cv::imread(file, cv::IMREAD_UNCHANGED);
        this->width = this->src.cols;
        this->height = this->src.rows;
    }

    Image::Image(const cv::Mat &src) {
        this->src = src;
        this->width = this->src.cols;
        this->height = this->src.rows;
    }

    void Image::resize(int fx, int fy) {
        float xr = float(fx) / float(this->width);
        float yr = float(fy) / float(this->height);

        cv::Mat result;
        cv::Rect r;
        if (xr >= yr) { // 按宽进行等比例压缩
            int h = int(float(this->height) * xr);
            cv::resize(this->src, result, cv::Size(fx, h));

            int top = (h - fy) / 2;
            r = cv::Rect(0, top, fx, fy);
        } else { // 按高进行等比例压缩
            int w = int(float(this->width) * yr);
            cv::resize(this->src, result, cv::Size(w, fy));

            int left = (w - fx) / 2;
            r = cv::Rect(left, 0, fx, fy);
        }
        // 截取
        this->dst = result(r);

        this->width = fx;
        this->height = fy;
    }

    void Image::compressJpeg(const std::string &file, int q) {
        std::vector<int> params;
        params.push_back(cv::IMWRITE_JPEG_QUALITY);
        params.push_back(q);

        cv::imwrite(file, this->src, params);
    }

    void Image::compressWebp(const std::string &file, int q) {
        std::vector<int> params;
        params.push_back(cv::IMWRITE_WEBP_QUALITY);
        params.push_back(q);

        cv::imwrite(file, this->src, params);
    }

    void Image::compressPng(const std::string &file, int level) {
        std::vector<int> params;
        params.push_back(cv::IMWRITE_PNG_COMPRESSION);
        params.push_back(level);

        cv::imwrite(file, this->src, params);
    }

    const cv::Mat& Image::destination() {
        return this->dst;
    }

    void Image::save(const std::string &file) {
        if (this->dst.cols == 0) {
            cv::imwrite(file, this->src);
        } else {
            cv::imwrite(file, this->dst);
        }
    }

    int Image::getWidth() const {
        return this->width;
    }

    int Image::getHeight() const {
        return this->height;
    }
}