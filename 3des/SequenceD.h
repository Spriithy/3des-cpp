//
// Created by theophile on 03/29/2021.
//

#ifndef INC_3DES_CPP_SEQUENCED_H
#define INC_3DES_CPP_SEQUENCED_H

#include "Sequence.h"
#include <iostream>

template<int N>
class SequenceD : protected Sequence {
private:
    Sequence m_other;

public:
    SequenceD() : Sequence(N), m_other(N) {}
    SequenceD(Sequence &t_left, Sequence &t_right) : Sequence(t_left), m_other(t_right) {}
    ~SequenceD() = default;

    Sequence &left() { return *this; }
    Sequence &right() { return m_other; }

    int &operator[](int i) override { return left()[i]; }
    int operator()(int i) { return left()(i); }

    void shift(int n) override {
        left().shift(n);
        right().shift(n);
    }

    SequenceD operator*(SequenceD &t_seq) {
        auto new_left = left() * t_seq.left();
        auto new_right = right() * t_seq.right();
        return SequenceD(new_left, new_right);
    }

    int size() override { return N; }
};

std::string to_string(SequenceD<64> t_seq) {
    std::string str;
    for (int i = 0; i < 8; ++i) {
        Sequence ss = t_seq.left().subsequence(i * 8, (i + 1) * 8);
        str += (unsigned char) ss.to_bits();
    }
    return str;
}

std::ostream &operator<<(std::ostream &os, SequenceD<64> &t_seq) {
    os << to_string(t_seq);
    return os;
}

#endif//INC_3DES_CPP_SEQUENCED_H
