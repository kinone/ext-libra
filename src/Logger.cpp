//
// Created by 王振浩 on 2021/3/16.
//

#include "Logger.h"

namespace libra {
    const char* LG_DEBUG = "debug";
    const char* LG_INFO = "info";
    const char* LG_ERROR = "error";

    Logger::Logger(zval* v) {
        ZVAL_COPY(&zv, v);
    }

    Logger::~Logger() {
        zval_ptr_dtor(&zv);
    }

    void Logger::log(const std::string& level, const std::string& message) {
        zval ret, arg;

        zend_string* str = zend_string_init(message.data(), message.length(), 1);
        ZVAL_STR(&arg, str);

        char method[level.length() + 1];
        strcpy(method, level.data());

        zend_call_method_with_1_params(&zv, Z_OBJCE_P(&zv), NULL, method, &ret, &arg);
        zend_string_free(str);
    }

    void Logger::debug(const std::string& message) {
        this->log(LG_DEBUG, message);
    }

    void Logger::info(const std::string& message) {
        this->log(LG_INFO, message);
    }

    void Logger::error(const std::string& message) {
        this->log(LG_ERROR, message);
    }
}