//
// Created by 王振浩 on 2020/10/31.
//

#ifndef LIBRA_UTILS_H
#define LIBRA_UTILS_H

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <webp/encode.h>
#include <webp/decode.h>

using namespace cv;

namespace libra {
    class Utils {
    private:
        static float maxTop;
        static float maxLeft;

        static float calcT(float x);

        static float calcY(float t);

        static float evaluate(float x);

        static float currentTopRate(float x);

        static float currentLeftRate(float x);

    public:
        static void mat2WebPPicture(const Mat &mat, WebPPicture *pic);

        static Mat genFrameH(const Mat &a, const Mat &b, int step, int total);

        static Mat genFrameV(const Mat &a, const Mat &b, int step, int total);
    };
}

#endif //LIBRA_UTILS_H
