//
// Created by 王振浩 on 2020/11/14.
//

#ifndef EXT_LIBRA_SEQUENCE_H
#define EXT_LIBRA_SEQUENCE_H

#include <vector>
#include <string>

namespace libra {
    class Sequence {
    public:
        Sequence();

        void add(const std::string &file);

        ~Sequence();

    private:
        std::vector<std::string> *files;
    };
}

#endif //EXT_LIBRA_SEQUENCE_H
