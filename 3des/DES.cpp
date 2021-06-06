//
// Created by theophile on 06/06/2021.
//

#include "DES.h"

SequenceD<64> DES::operator()(SequenceD<64> seq) {
    auto left = seq.right();
    auto right = m_f(seq.right()) * seq.left();
    return SequenceD<64>(left, right);
}

SequenceD<64> DESinv::operator()(SequenceD<64> seq) {
    auto left = seq.right();
    auto right = m_finv(seq.right()) * seq.left();
    return SequenceD<64>(left, right);
}
