//
// Created by theophile on 04/25/2021.
//

#ifndef INC_3DES_CPP_PERMUTATION_H
#define INC_3DES_CPP_PERMUTATION_H

#include "SequenceD.h"

template<int I, int O>
class Permutation {
public:
    SequenceD<O> operator()(SequenceD<I> &seq, const std::vector<int> &indices) {
        SequenceD<O> new_seq{};
        for (auto i = 0; i < O; ++i) {
            new_seq[i] = seq[indices[i] - 1];
        }
        return new_seq;
    }
};

#endif//INC_3DES_CPP_PERMUTATION_H
