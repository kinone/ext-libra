//
// Created by 王振浩 on 2020/11/14.
//

#include "Sequence.h"
#include <iostream>

namespace libra {

    Sequence::Sequence() {
        std::cout << "libra::Sequence::Sequence" << std::endl;
        this->files = new std::vector<std::string>();
    }

    Sequence::~Sequence() {
        std::cout << "libra::Sequence::~Sequence" << std::endl;
        this->files->clear();
        delete this->files;
    }

    void Sequence::add(const std::string &file) {
        this->files->push_back(file);
    }
}
