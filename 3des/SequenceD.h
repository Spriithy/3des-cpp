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
    SequenceD() : Sequence(N / 2), m_other(N / 2) {}
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

    int size() { return N; }

    std::string to_string() {
        return left().to_string() + right().to_string();
    }
};

Sequence read_seq_from_chars(std::istream &in, int n) {
    std::list<Sequence> seqs{};
    Sequence new_seq(8);
    uint8_t c;
    for (int i = 0; i < n; ++i) {
        in >> c;
        new_seq = c;
        seqs.push_back(new_seq);
    }
    return Sequence(seqs);
}

std::ostream &operator<<(std::ostream &os, SequenceD<64> &t_seq) {
    os << t_seq.to_string();
    return os;
}

std::istream &operator>>(std::istream &in, SequenceD<64> &t_seq) {
    t_seq.left() = read_seq_from_chars(in, 4);
    t_seq.right() = read_seq_from_chars(in, 4);
    return in;
}

void write_seq_bits(std::ostream &os, Sequence &t_seq) {
    for (auto i = 0; i < t_seq.size(); ++i) {
        os << (t_seq[i] ? '1' : '0');
    }
}

void write(std::ostream &os, SequenceD<64> &t_seq) {
    write_seq_bits(os, t_seq.left());
    write_seq_bits(os, t_seq.right());
}

Sequence read_seq_from_bits(std::istream &in, int n) {
    Sequence seq(n);
    uint8_t c;
    for (auto i = 0; i < n; ++i) {
        in >> c;
        seq[i] = c == '1' ? 1 : 0;
    }
    return seq;
}

void read(std::istream &in, SequenceD<64> &t_seq) {
    t_seq.left() = read_seq_from_bits(in, 32);
    t_seq.right() = read_seq_from_bits(in, 32);
}

#endif//INC_3DES_CPP_SEQUENCED_H
