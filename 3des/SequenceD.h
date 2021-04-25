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

    int &operator[](int i) override { return i < N / 2 ? left()[i] : right()[i - N / 2]; }
    int operator()(int i) { return i < N / 2 ? left()(i) : right()(i - N / 2); }

    void shift(int n) override {
        left().shift(n);
        right().shift(n);
    }

    SequenceD<N> operator*(SequenceD<N> &t_seq) {
        auto new_left = left() * t_seq.left();
        auto new_right = right() * t_seq.right();
        return SequenceD<N>(new_left, new_right);
    }

    int size() { return N; }

    std::string as_char_string() {
        return left().as_char_string() + right().as_char_string();
    }

    std::string as_bit_string() {
        return left().as_bit_string() + right().as_bit_string();
    }
};

Sequence read_seq_from_chars(std::istream &in, int n) {
    std::list<Sequence> seqs{};
    Sequence new_seq(8);
    uint8_t c;
    for (auto i = 0; i < n; ++i) {
        in >> c;
        new_seq = c;
        seqs.push_back(new_seq);
    }
    return Sequence(seqs);
}

std::ostream &operator<<(std::ostream &os, SequenceD<64> &t_seq) {
    os << t_seq.as_char_string();
    return os;
}

std::istream &operator>>(std::istream &in, SequenceD<64> &t_seq) {
    t_seq.left() = read_seq_from_chars(in, 4);
    t_seq.right() = read_seq_from_chars(in, 4);
    return in;
}

void write(std::ostream &os, SequenceD<64> &t_seq) {
    os << t_seq.as_char_string();
}

Sequence read_seq_from_bits(std::istream &in, int n) {
    Sequence seq(n);
    uint8_t c;
    for (auto i = 0; i < n; ++i) {
        in >> c;
        seq[n - i - 1] = c == '1' ? 1 : 0;
    }
    return seq;
}

void read(std::istream &in, SequenceD<64> &t_seq) {
    // We need to read the right sequence first because of endianness
    t_seq.right() = read_seq_from_bits(in, 32);
    t_seq.left() = read_seq_from_bits(in, 32);
}

template<class seqType>
void print(seqType &t_seq) {
    for (auto i = 0; i < t_seq.size(); ++i) {
        std::cout << t_seq(t_seq.size() - i - 1);
    }
}

template<class seqType>
std::string to_bits_string(seqType &t_seq) {
    std::string str;
    auto n = t_seq.size();
    for (auto i = 0; i < n; ++i) {
        str += t_seq(n - i - 1) ? '1' : '0';
    }
    return str;
}

#endif//INC_3DES_CPP_SEQUENCED_H
