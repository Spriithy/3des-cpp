//
// Created by theophile on 06/06/2021.
//

#include "DES.h"
#include "Permutation.h"

SequenceD<64> DES::operator()(SequenceD<64> seq) {
    auto pSeq = Permutation<64, 64>{}(seq, INITIAL_PERMUTATION);
    auto left = pSeq.left();
    auto right = pSeq.right();

    for (auto i = 0; i < 16; ++i) {
        auto tmp = right;
        right = m_f(right) * left;
        left = tmp;
    }

    pSeq.left() = right;
    pSeq.right() = left;
    return Permutation<64, 64>{}(pSeq, INITIAL_PERMUTATION_REVERSE);
}

SequenceD<64> DESinv::operator()(SequenceD<64> seq) {
    auto pSeq = Permutation<64, 64>{}(seq, INITIAL_PERMUTATION);
    auto left = pSeq.left();
    auto right = pSeq.right();

    for (auto i = 0; i < 16; ++i) {
        auto tmp = right;
        right = m_finv(right) * left;
        left = tmp;
    }

    pSeq.left() = right;
    pSeq.right() = left;
    return Permutation<64, 64>{}(pSeq, INITIAL_PERMUTATION_REVERSE);
}
