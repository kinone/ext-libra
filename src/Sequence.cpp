//
// Created by 王振浩 on 2020/11/14.
//

#include "Sequence.h"

namespace libra {
    Sequence::Sequence() {
        this->files = new std::vector<std::string>();
    }

    Sequence::~Sequence() {
        this->files->clear();
        delete this->files;
    }

    void Sequence::add(const std::string &file) {
        this->files->push_back(file);
    }

    void Sequence::generate(const std::string &result) {
        this->logger->info(result);
    }
}
