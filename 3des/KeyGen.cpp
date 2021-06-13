//
// Created by theophile on 04/25/2021.
//

#include "KeyGen.h"
#include "Permutation.h"

KeyGen::KeyGen(SequenceD<64> &key) : m_round(0) {
    m_rolling = Permutation<64, 56>{}(key, PC1);
}

SequenceD<48> KeyGen::next() {
    auto n = SCHEDULED_LEFT_SHIFTS[m_round++];
    m_rolling.shift(n);

    return Permutation<56, 48>{}(m_rolling, PC2);
}
