//
// Created by 王振浩 on 2020/11/19.
//

#include "NullLogger.h"

namespace libra {
    NullLogger::~NullLogger() {}

    void NullLogger::debug(const std::string &message) {}

    void NullLogger::info(const std::string &message) {}

    void NullLogger::error(const std::string &message) {}
}
