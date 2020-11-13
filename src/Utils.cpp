//
// Created by 王振浩 on 2020/10/31.
//

#include "Utils.h"

namespace libra {
    float Utils::maxTop = 0.1f;
    float Utils::maxLeft = 0.1f;

    void Utils::genFrameH(const cv::Mat &a, const cv::Mat &b, cv::Mat &dst, int step, int total) {
        float d = 1.0f / float(total + 1) * float(step + 1);
        float colRate, topRate, top, ltop, rtop;

        cv::Point2f srcTri[4];
        cv::Point2f dstTri[4];

        cv::Mat warp_left(3, 3, a.type());
        cv::Mat warp_right(3, 3, a.type());
        cv::Mat dst_left, dst_right;

        colRate = evaluate(d);

        int x = a.cols - 1, y = a.rows - 1;
        int delimiter = int(round(float(a.cols) * colRate));

        bool l = false, r = false;
        topRate = currentTopRate(d);
        top = topRate * float(a.rows);

        srcTri[0] = cv::Point2f(0, 0);
        srcTri[1] = cv::Point2f(x, 0);
        srcTri[2] = cv::Point2f(x, y);
        srcTri[3] = cv::Point2f(0, y);

        ltop = (1 - colRate) * float(a.cols) * maxTop;
        if (delimiter > 25) {
            dst_left = cv::Mat::zeros(a.rows, a.cols, a.type());

            dstTri[0] = cv::Point2f(0, ltop);
            dstTri[1] = cv::Point2f(delimiter - 1, -top);
            dstTri[2] = cv::Point2f(delimiter - 1, float(y) + top);
            dstTri[3] = cv::Point2f(0, float(y) - ltop);

            warp_left = getPerspectiveTransform(srcTri, dstTri);
            warpPerspective(a, dst_left, warp_left, dst_left.size());

            l = true;
        }

        rtop = colRate * float(a.cols) * maxTop;
        if (a.cols - delimiter > 25) {
            dst_right = cv::Mat::zeros(b.rows, b.cols, a.type());

            dstTri[0] = cv::Point2f(delimiter, -top);
            dstTri[1] = cv::Point2f(x, rtop);
            dstTri[2] = cv::Point2f(x, float(y) - rtop);
            dstTri[3] = cv::Point2f(delimiter, float(y) + top);

            warp_right = getPerspectiveTransform(srcTri, dstTri);
            warpPerspective(b, dst_right, warp_right, dst_right.size());

            r = true;
        }

        if (!r) {
            dst = dst_left;
            return;
        }

        if (!l) {
            dst = dst_right;
            return;
        }

        cv::Rect rect_left(0, 0, delimiter, b.rows);
        cv::Rect rect_right(delimiter, 0, b.cols - delimiter, b.rows);
        hconcat(dst_left(rect_left), dst_right(rect_right), dst);
   }

    void Utils::genFrameV(const cv::Mat &a, const cv::Mat &b, cv::Mat &dst, int step, int total) {
        float d = 1.0f / float(total + 1) * float(step + 1);
        float rowRate, leftRate, left, topLeft, bottomLeft;

        cv::Point2f srcTri[4];
        cv::Point2f dstTri[4];

        cv::Mat warp_top(3, 3, a.type());
        cv::Mat warp_bottom(3, 3, a.type());
        cv::Mat dst_top, dst_bottom;

        rowRate = 1 - evaluate(d);

        int x = a.cols - 1, y = a.rows - 1;
        int delimiter = int(round(float(a.rows) * rowRate));

        bool bt = false, bb = false;
        leftRate = currentLeftRate(d);
        left = leftRate * float(a.cols);

        srcTri[0] = cv::Point2f(0, 0);
        srcTri[1] = cv::Point2f(x, 0);
        srcTri[2] = cv::Point2f(x, y);
        srcTri[3] = cv::Point2f(0, y);

        topLeft = (1 - rowRate) * float(b.rows) * maxLeft;
        if (delimiter > 25) {
            dst_top = cv::Mat::zeros(b.rows, b.cols, b.type());

            dstTri[0] = cv::Point2f(topLeft, 0);
            dstTri[1] = cv::Point2f(float(x) - topLeft, 0);
            dstTri[2] = cv::Point2f(float(x) + left, delimiter - 1);
            dstTri[3] = cv::Point2f(-left, delimiter - 1);

            warp_top = getPerspectiveTransform(srcTri, dstTri);
            warpPerspective(b, dst_top, warp_top, dst_top.size());

            bt = true;
        }

        bottomLeft = rowRate * float(a.rows) * maxLeft;
        if (a.rows - delimiter > 25) {
            dst_bottom = cv::Mat::zeros(a.rows, a.cols, a.type());

            dstTri[0] = cv::Point2f(-left, delimiter);
            dstTri[1] = cv::Point2f(float(x) + left, delimiter);
            dstTri[2] = cv::Point2f(float(x) - bottomLeft, y);
            dstTri[3] = cv::Point2f(bottomLeft, y);

            warp_bottom = getPerspectiveTransform(srcTri, dstTri);
            warpPerspective(a, dst_bottom, warp_bottom, dst_bottom.size());

            bb = true;
        }

        if (!bb) {
            dst = dst_top;
            return;
        }

        if (!bt) {
            dst = dst_bottom;
            return;
        }

        cv::Rect rect_top(0, 0, b.cols, delimiter);
        cv::Rect rect_bottom(0, delimiter, a.cols, a.rows - delimiter);

        vconcat(dst_top(rect_top), dst_bottom(rect_bottom), dst);
    }

    void Utils::mat2WebPPicture(const cv::Mat &src, WebPPicture *pic, int quality) {
        std::vector <uchar> buff;

        // 设置图片质量
        std::vector<int> params = std::vector<int>();
        params.push_back(cv::IMWRITE_WEBP_QUALITY);
        params.push_back(quality);

        imencode(".webp", src, buff, params);

        WebPPictureInit(pic);
        pic->width = src.cols;
        pic->height = src.rows;
        pic->use_argb = 1;

        WebPPictureAlloc(pic);

        int width, height;
        uint8_t *p = WebPDecodeBGRA(&buff[0], buff.size(), &width, &height);
        WebPPictureImportBGRA(pic, p, width * 4);

        WebPFree(p);
    }

    float Utils::calcT(float x) {
        float a = 1.96f;
        float b = -2.94f;
        float c = 1.98f;
        float d = -x;


        float A = b * b - 3 * a * c;
        float B = b * c - 9 * a * d;
        float C = c * c - 3 * b * d;

        float delta = B * B - 4 * A * C;

        if (delta <= 0) {
            // TODO 暂时不处理该情况
            return 0;
        }

        float Y1 = A * b + 3 * a * (-B + sqrt(delta)) / 2;
        float Y2 = A * b + 3 * a * (-B - sqrt(delta)) / 2;
        float Y11, Y22;

        if (Y1 > 0) {
            Y11 = float(pow(Y1, float(1) / 3));
        } else {
            Y11 = -float(pow(-Y1, float(1) / 3));
        }

        if (Y2 > 0) {
            Y22 = float(pow(Y2, float(1) / 3));
        } else {
            Y22 = -float(pow(-Y2, float(1) / 3));
        }

        float t = (-b - (Y11 + Y22)) / (3 * a);

        return t;
    }

    float Utils::calcY(float t) {
        float y = 3 * t * t - 2 * t * t * t;

        return 1.0f - y;
    }

    float Utils::evaluate(float x) {
        return calcY(calcT(x));
    }

    float Utils::currentTopRate(float x) {
        float y;

        if (x <= 0.5) {
            y = 2 * (1 - evaluate(x)) * maxTop;
        } else {
            y = 2 * (1 - evaluate(1.0f - x)) * maxTop;
        }

        return y;
    }

    float Utils::currentLeftRate(float x) {
        float y;

        if (x <= 0.5) {
            y = 2 * (1 - evaluate(x)) * maxLeft;
        } else {
            y = 2 * (1 - evaluate(1.0f - x)) * maxLeft;
        }

        return y;
    }
}