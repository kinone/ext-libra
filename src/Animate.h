//
// Created by 王振浩 on 2021/03/17.
//

#ifndef LIBRA_ANIMATE_H
#define LIBRA_ANIMATE_H

#include <string>
#include <vector>
#include <opencv2/imgproc.hpp>
#include "ILogger.h"

namespace libra {
    class Animate {
    public:
        Animate(uint32_t width, uint32_t height);
        virtual ~Animate();

        virtual bool add(const std::string& file);

        virtual void clear();

        const std::string& lastError() const;

        int lastErrorCode() const;

        bool setFrameCount(uint32_t c);

        bool setQuality(uint32_t q);

        bool setLoop(uint32_t l);

        bool setDuration(uint32_t time);

    protected:
        bool checkWH(const cv::Mat& m) const;

        std::vector<std::string>* files;
        uint32_t width;
        uint32_t height;
        uint32_t loop;
        uint32_t frameCount;
        uint32_t quality;
        uint32_t duration;

        int code;
        std::string message;

        LoggerInterface* logger;
    };
}

#endif