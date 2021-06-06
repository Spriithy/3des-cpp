//
// Created by theophile on 06/06/2021.
//

#include "DES.h"

SequenceD<64> DES::operator()(SequenceD<64> seq) {
    auto left = seq.left();
    auto right = seq.right();

    for (auto i = 0; i < 16; ++i) {
        auto tmp = right;
        right = m_f(right) * left;
        left = tmp;
    }

    return SequenceD<64>(left, right);
}

SequenceD<64> DESinv::operator()(SequenceD<64> seq) {
    auto left = seq.left();
    auto right = seq.right();

    for (auto i = 0; i < 16; ++i) {
        auto tmp = right;
        right = m_finv(right) * left;
        left = tmp;
    }

    return SequenceD<64>(left, right);
}
