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

    int &operator[](int i) { return (i < (N / 2)) ? m_other[i] : Sequence::operator[](i - (N / 2)); }
    int operator()(int i) const { return (i < (N / 2)) ? m_other(i) : Sequence::operator()(i - (N / 2)); }

    void shift(int n) override {
        Sequence::shift(n);
        right().shift(n);
    }

    SequenceD<N> operator*(SequenceD<N> t_seq) {
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

Sequence read_seq_from_chars(std::istream &in, int n);
Sequence read_seq_from_bits(std::istream &in, int n);

std::ostream &operator<<(std::ostream &os, SequenceD<64> &t_seq);
std::istream &operator>>(std::istream &in, SequenceD<64> &t_seq);

void write(std::ostream &os, SequenceD<64> &t_seq);
void read(std::istream &in, SequenceD<64> &t_seq);

template<class seqType>
void print(seqType &t_seq) {
    auto n = t_seq.size();
    for (auto i = 0; i < n; ++i) {
        std::cout << t_seq(i);
    }
    std::cout << std::endl;
}

#endif//INC_3DES_CPP_SEQUENCED_H
