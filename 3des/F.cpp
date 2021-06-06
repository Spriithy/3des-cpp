//
// Created by theophile on 06/05/2021.
//

#include "F.h"
#include "Permutation.h"


Sequence F::operator()(Sequence &right) {
    static int round = 0;
    if (round > 15) {
        return Sequence();
    }
    ++round;

    // Adapt Sequence to SequenceD<32>
    auto subLeft = right.subsequence(0, 16);
    auto subRight = right.subsequence(16, 32);
    SequenceD<32> rightD(subLeft, subRight);

    // Expand SequenceD<32> to SequenceD<48>
    auto expanded = Permutation<32, 48>{}(rightD, EXPANSION_PERMUTATION);

    // Perform XOR on expanded SequenceD<48>
    auto seq = expanded * m_keyGen.next();

    // Pass expanded sequence to S-Box
    auto sboxInput = Sequence(std::list{seq.left(), seq.right()});
    auto sboxResult = m_sFunction(sboxInput);

    // Pass S-Box resulting sequence to permutation P
    auto sboxLeft = sboxResult.subsequence(0, 16);
    auto sboxRight = sboxResult.subsequence(16, 0);
    SequenceD<32> sboxResultD(sboxLeft, sboxRight);

    // Apply permutation P
    auto newRight = Permutation<32, 32>{}(sboxResultD, PERMUTATION_FUNCTION);

    return Sequence(std::list{newRight.left(), newRight.right()});
}

// Finv

Finv::Finv(SequenceD<64> &key) : m_keyGen(key), m_sFunction(SBOX_MATRICES), m_keys(16) {
    // We need to lookup all keys before we start the Finv procedure because we
    // need to start with the last generated key
    for (auto i = 0; i < 16; ++i) {
        m_keys[16 - i - 1] = m_keyGen.next();
    }
}


Sequence Finv::operator()(Sequence &right) {
    static int round = 0;
    if (round > 15) {
        return Sequence();
    }
    ++round;

    // Adapt Sequence to SequenceD<32>
    auto subLeft = right.subsequence(0, 16);
    auto subRight = right.subsequence(16, 32);
    SequenceD<32> rightD(subLeft, subRight);

    // Expand SequenceD<32> to SequenceD<48>
    auto expanded = Permutation<32, 48>{}(rightD, EXPANSION_PERMUTATION);

    // Perform XOR on expanded SequenceD<48>
    auto seq = expanded * m_keys[round];

    // Pass expanded sequence to S-Box
    auto sboxInput = Sequence(std::list{seq.left(), seq.right()});
    auto sboxResult = m_sFunction(sboxInput);

    // Pass S-Box resulting sequence to permutation P
    auto sboxLeft = sboxResult.subsequence(0, 16);
    auto sboxRight = sboxResult.subsequence(16, 0);
    SequenceD<32> sboxResultD(sboxLeft, sboxRight);

    // Apply permutation P
    auto newRight = Permutation<32, 32>{}(sboxResultD, PERMUTATION_FUNCTION);

    return Sequence(std::list{newRight.left(), newRight.right()});
}
