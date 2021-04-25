//
// Created by theophile on 04/25/2021.
//

#include "KeyGen.h"
#include "Permutation.h"


KeyGen::KeyGen(SequenceD<64> &key) {
    m_rolling = Permutation<64, 56>{}(key, PC1);
}

SequenceD<48> KeyGen::next() {
    static int round = 0;
    if (round > 15) {
        return {};
    }
    m_rolling.shift(SCHEDULED_LEFT_SHIFTS[round]);
    return Permutation<56, 48>{}(m_rolling, PC2);
}