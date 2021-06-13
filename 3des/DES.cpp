#include "DES.h"
#include "Permutation.h"

SequenceD<64> DES::operator()(SequenceD<64> seq) {
    F f(m_key);
    auto tmp = Permutation<64, 64>{}(seq, INITIAL_PERMUTATION);

    for (auto i = 0; i < 16; ++i) {
        auto tmpSeq = f(tmp.right());
        auto xorSeq = tmp.left() * tmpSeq;
        tmp = SequenceD<64>{tmp.right(), xorSeq};
    }

    auto swapSeq = SequenceD<64>{tmp.right(), tmp.left()};
    return Permutation<64, 64>{}(swapSeq, INITIAL_PERMUTATION_REVERSE);
}

SequenceD<64> DESinv::operator()(SequenceD<64> seq) {
    Finv f_inv(m_key);
    auto tmp = Permutation<64, 64>{}(seq, INITIAL_PERMUTATION);

    for (int i = 0; i < 16; ++i) {
        auto tempSeq = f_inv(tmp.right());
        auto xorSeq = tmp.left() * tempSeq;
        tmp = SequenceD<64>{tmp.right(), xorSeq};
    }

    auto swapSeq = SequenceD<64>{tmp.right(), tmp.left()};
    return Permutation<64, 64>()(swapSeq, INITIAL_PERMUTATION_REVERSE);
}
