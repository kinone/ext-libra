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
    public:
        static float calcT(float x) {
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

        static float calcY(float t) {
            float y = 3 * t * t - 2 * t * t * t;

            return 1.0f - y;
        }

        static float evaluate(float x) {
            return calcY(calcT(x));
        }

        static float currentTopRate(float x) {
            float y;

            if (x <= 0.5) {
                y = 2 * (1 - evaluate(x)) * maxTop;
            } else {
                y = 2 * (1 - evaluate(1.0f - x)) * maxTop;
            }

            return y;
        }

        static float currentLeftRate(float x) {
            float y;

            if (x <= 0.5) {
                y = 2 * (1 - evaluate(x)) * maxLeft;
            } else {
                y = 2 * (1 - evaluate(1.0f - x)) * maxLeft;
            }

            return y;
        }

        static Mat genFrameH(const Mat &a, const Mat &b, int step, int total) {
            float d = 1.0f / float(total + 1) * float(step + 1);
            float colRate, topRate, top, ltop, rtop;

            Point2f srcTri[4];
            Point2f dstTri[4];

            Mat warp_left(3, 3, a.type());
            Mat warp_right(3, 3, a.type());
            Mat dst_left, dst_right;

            colRate = evaluate(d);

            int x = a.cols - 1, y = a.rows - 1;
            int delimiter = int(round(float(a.cols) * colRate));

            bool l = false, r = false;
            topRate = currentTopRate(d);
            top = topRate * float(a.rows);

            srcTri[0] = Point2f(0, 0);
            srcTri[1] = Point2f(x, 0);
            srcTri[2] = Point2f(x, y);
            srcTri[3] = Point2f(0, y);

            ltop = (1 - colRate) * float(a.cols) * maxTop;
            if (delimiter > 25) {
                dst_left = Mat::zeros(a.rows, a.cols, a.type());

                dstTri[0] = Point2f(0, ltop);
                dstTri[1] = Point2f(delimiter - 1, -top);
                dstTri[2] = Point2f(delimiter - 1, float(y) + top);
                dstTri[3] = Point2f(0, float(y) - ltop);

                warp_left = getPerspectiveTransform(srcTri, dstTri);
                warpPerspective(a, dst_left, warp_left, dst_left.size());

                l = true;
            }

            rtop = colRate * float(a.cols) * maxTop;
            if (a.cols - delimiter > 25) {
                dst_right = Mat::zeros(b.rows, b.cols, a.type());

                dstTri[0] = Point2f(delimiter, -top);
                dstTri[1] = Point2f(x, rtop);
                dstTri[2] = Point2f(x, float(y) - rtop);
                dstTri[3] = Point2f(delimiter, float(y) + top);

                warp_right = getPerspectiveTransform(srcTri, dstTri);
                warpPerspective(b, dst_right, warp_right, dst_right.size());

                r = true;
            }

            if (!r) {
                return dst_left;
            }

            if (!l) {
                return dst_right;
            }

            Mat dst;
            Rect rect_left(0, 0, delimiter, b.rows);
            Rect rect_right(delimiter, 0, b.cols - delimiter, b.rows);
            hconcat(dst_left(rect_left), dst_right(rect_right), dst);

            return dst;
        }

        static Mat genFrameV(const Mat &a, const Mat &b, int step, int total) {
            float d = 1.0f / float(total + 1) * float(step + 1);
            float rowRate, leftRate, left, topLeft, bottomLeft;

            Point2f srcTri[4];
            Point2f dstTri[4];

            Mat warp_top(3, 3, a.type());
            Mat warp_bottom(3, 3, a.type());
            Mat dst_top, dst_bottom;

            rowRate = 1 - evaluate(d);

            int x = a.cols - 1, y = a.rows - 1;
            int delimiter = int(round(float(a.rows) * rowRate));

            bool bt = false, bb = false;
            leftRate = currentLeftRate(d);
            left = leftRate * float(a.cols);

            srcTri[0] = Point2f(0, 0);
            srcTri[1] = Point2f(x, 0);
            srcTri[2] = Point2f(x, y);
            srcTri[3] = Point2f(0, y);

            topLeft = (1 - rowRate) * float(b.rows) * maxLeft;
            if (delimiter > 25) {
                dst_top = Mat::zeros(b.rows, b.cols, b.type());

                dstTri[0] = Point2f(topLeft, 0);
                dstTri[1] = Point2f(float(x) - topLeft, 0);
                dstTri[2] = Point2f(float(x) + left, delimiter - 1);
                dstTri[3] = Point2f(-left, delimiter - 1);

                warp_top = getPerspectiveTransform(srcTri, dstTri);
                warpPerspective(b, dst_top, warp_top, dst_top.size());

                bt = true;
            }

            bottomLeft = rowRate * float(a.rows) * maxLeft;
            if (a.rows - delimiter > 25) {
                dst_bottom = Mat::zeros(a.rows, a.cols, a.type());

                dstTri[0] = Point2f(-left, delimiter);
                dstTri[1] = Point2f(float(x) + left, delimiter);
                dstTri[2] = Point2f(float(x) - bottomLeft, y);
                dstTri[3] = Point2f(bottomLeft, y);

                warp_bottom = getPerspectiveTransform(srcTri, dstTri);
                warpPerspective(a, dst_bottom, warp_bottom, dst_bottom.size());

                bb = true;
            }

            if (!bb) {
                return dst_top;
            }

            if (!bt) {
                return dst_bottom;
            }

            Mat dst;
            Rect rect_top(0, 0, b.cols, delimiter);
            Rect rect_bottom(0, delimiter, a.cols, a.rows - delimiter);

            vconcat(dst_top(rect_top), dst_bottom(rect_bottom), dst);

            return dst;
        }

        static void mat2WebPPicture(const Mat &mat, WebPPicture *pic) {
            std::vector <uchar> buff;
            imencode(".webp", mat, buff);

            WebPPictureInit(pic);
            pic->width = mat.cols;
            pic->height = mat.rows;
            pic->use_argb = 1;

            WebPPictureAlloc(pic);

            int width, height;
            uint8_t *p = WebPDecodeBGRA(&buff[0], buff.size(), &width, &height);
            WebPPictureImportBGRA(pic, p, width * 4);

            WebPFree(p);
        }
    };
}

#endif //LIBRA_UTILS_H
