//
// Created by 王振浩 on 2020/11/14.
//

#ifndef EXT_LIBRA_SEQUENCE_H
#define EXT_LIBRA_SEQUENCE_H

#include <vector>
#include <string>
#include "opencv2/imgcodecs.hpp"
#include "Logger.h"
#include "LibraErrno.h"

namespace libra {
    class Sequence {
    public:
        Sequence(uint32_t width, uint32_t height);

        ~Sequence();

        bool add(const std::string &file);

        bool setFrameCount(uint32_t c);

        bool setQuality(uint32_t q);

        bool setLoop(uint32_t l);

        bool generate(const std::string &result);

        void clear();

        const std::string &lastError() const;

        int lastErrorCode() const;

    private:
        bool checkWH(const cv::Mat &m) const;

        std::vector<std::string> *files;
        uint32_t width;
        uint32_t height;
        uint32_t loop;
        uint32_t frameCount;
        uint32_t quality;

        int code;
        std::string message;

        LoggerInterface *logger;
    };
}

#endif //EXT_LIBRA_SEQUENCE_H
