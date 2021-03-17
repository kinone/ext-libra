//
// Created by 王振浩 on 2020/11/18.
//

#ifndef EXT_LIBRA_ILOGGER_H
#define EXT_LIBRA_ILOGGER_H

#include <string>

namespace libra {
    class LoggerInterface {
    public:
        virtual ~LoggerInterface() {};

        virtual void debug(const std::string &message) = 0;

        virtual void info(const std::string &message) = 0;

        virtual void error(const std::string &message) = 0;
    };

    class NullLogger : public LoggerInterface {
    public:
        virtual ~NullLogger() {}

        virtual void debug(const std::string &message) {}

        virtual void info(const std::string &message) {}

        virtual void error(const std::string &message) {}
    };
}

#endif //EXT_LIBRA_ILOGGER_H
