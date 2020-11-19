//
// Created by 王振浩 on 2020/11/18.
//

#include "Logger.h"

namespace libra {
    Logger::Logger(zval *v) {
        ZVAL_COPY(&zv, v);
    }

    Logger::~Logger() {
        zval_ptr_dtor(&zv);
    }

    void Logger::debug(const std::string &message, void *context) {
        zval ret, arg;
        zend_string *str = zend_string_init(message.data(), message.length(), 1);
        ZVAL_STR(&arg, str);
        zend_call_method_with_1_params(&zv, Z_OBJCE_P(&zv), NULL, "debug", &ret, &arg);
        zend_string_free(str);
    }

    void Logger::info(const std::string &message, void *context) {
        zval ret, arg;
        zend_string *str = zend_string_init(message.data(), message.length(), 1);
        ZVAL_STR(&arg, str);
        zend_call_method_with_1_params(&zv, Z_OBJCE_P(&zv), NULL, "info", &ret, &arg);
        zend_string_free(str);
    }

    void Logger::error(const std::string &message, void *context) {
        zval ret, arg;
        zend_string *str = zend_string_init(message.data(), message.length(), 1);
        ZVAL_STR(&arg, str);
        zend_call_method_with_1_params(&zv, Z_OBJCE_P(&zv), NULL, "error", &ret, &arg);
        zend_string_free(str);
    }
}
