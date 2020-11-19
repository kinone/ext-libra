//
// Created by 王振浩 on 2020/11/14.
//

#ifndef EXT_LIBRA_SEQUENCE_H
#define EXT_LIBRA_SEQUENCE_H

#include <vector>
#include <string>
#include "src/Base.h"

namespace libra {
    class Sequence : public Base {
    public:
        Sequence();

        void add(const std::string &file);

        void generate(const std::string &result);

        ~Sequence();

    private:
        std::vector<std::string> *files;
    };
}

#endif //EXT_LIBRA_SEQUENCE_H
