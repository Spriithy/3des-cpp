#include "F.h"
#include "Permutation.h"

template<int N>
inline SequenceD<N> toSequenceD(Sequence &seq) {
    auto l = seq.subsequence(N / 2, N);
    auto r = seq.subsequence(0, N / 2);
    return SequenceD<N>{l, r};
}

template<int N>
inline Sequence toSequence(SequenceD<N> &seq) {
    return Sequence({seq.right(), seq.left()});
}

Sequence F::operator()(Sequence &seq) {
    auto expansion = seq.permutation(EXPANSION_PERMUTATION);
    auto key = m_keyGen.next();
    auto tmp = expansion * toSequence(key);
    auto sbox = m_sFunction(tmp);
    auto permutation = sbox.permutation(PERMUTATION_FUNCTION);
    return permutation;
}

// Finv

Finv::Finv(SequenceD<64> &key) : m_round(0), m_keyGen(key), m_sFunction(SBOX_MATRICES), m_keys(16) {
    // We need to lookup all keys before we start the Finv procedure because we
    // need to start with the last generated key
    for (auto i = 0; i < 16; ++i) {
        m_keys[16 - i - 1] = m_keyGen.next();
    }
}


Sequence Finv::operator()(Sequence &seq) {
    auto expansion = seq.permutation(EXPANSION_PERMUTATION);
    auto key = m_keys[m_round++];
    auto tmp = expansion * toSequence(key);
    auto sbox = m_sFunction(tmp);
    auto permutation = sbox.permutation(PERMUTATION_FUNCTION);
    return permutation;
}
