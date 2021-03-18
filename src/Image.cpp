//
// Created by 王振浩 on 2020/11/3.
//

#include "Image.h"

namespace libra {
    Image::Image(const std::string& file) {
        src = cv::imread(file, cv::IMREAD_UNCHANGED);
        width = src.cols;
        height = src.rows;
    }

    Image::Image(const cv::Mat& src) : src(src) {
        width = src.cols;
        height = src.rows;
    }

    Image::~Image() {

    }

    void Image::resize(int fx, int fy) {
        float xr = float(fx) / float(width);
        float yr = float(fy) / float(height);

        cv::Mat result;
        cv::Rect r;
        if (xr >= yr) { // 按宽进行等比例压缩
            int h = int(float(height) * xr);
            cv::resize(src, result, cv::Size(fx, h));

            int top = (h - fy) / 2;
            r = cv::Rect(0, top, fx, fy);
        }
        else { // 按高进行等比例压缩
            int w = int(float(width) * yr);
            cv::resize(src, result, cv::Size(w, fy));

            int left = (w - fx) / 2;
            r = cv::Rect(left, 0, fx, fy);
        }
        // 截取
        dst = result(r);

        width = fx;
        height = fy;
    }

    void Image::compressJpeg(const std::string& file, int q) {
        std::vector<int> params;
        params.push_back(cv::IMWRITE_JPEG_QUALITY);
        params.push_back(q);

        cv::imwrite(file, src, params);
    }

    void Image::compressWebp(const std::string& file, int q) {
        std::vector<int> params;
        params.push_back(cv::IMWRITE_WEBP_QUALITY);
        params.push_back(q);

        cv::imwrite(file, src, params);
    }

    void Image::compressPng(const std::string& file, int level) {
        std::vector<int> params;
        params.push_back(cv::IMWRITE_PNG_COMPRESSION);
        params.push_back(level);

        cv::imwrite(file, src, params);
    }

    void Image::exportTo(cv::Mat& ret) {
        dst.copyTo(ret);
    }

    void Image::save(const std::string& file) {
        if (dst.empty()) {
            cv::imwrite(file, src);
        }
        else {
            cv::imwrite(file, dst);
        }
    }

    int Image::type() const {
        return src.type();
    }

    int Image::getWidth() const {
        return width;
    }

    int Image::getHeight() const {
        return height;
    }
}