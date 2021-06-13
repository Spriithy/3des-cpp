#include "SequenceD.h"

Sequence read_seq_from_chars(std::istream &in, int n) {
    std::list<Sequence> seqs{};
    Sequence new_seq(8);
    uint8_t c;
    for (auto i = 0; i < n; ++i) {
        in >> c;
        new_seq = c;
        seqs.push_front(new_seq);
    }
    return Sequence(seqs);
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

void read(std::istream &in, SequenceD<64> &t_seq) {
    t_seq.left() = read_seq_from_bits(in, 32);
    t_seq.right() = read_seq_from_bits(in, 32);
}
