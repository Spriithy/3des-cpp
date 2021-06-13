#ifndef INC_3DES_CPP_SEQUENCE_H
#define INC_3DES_CPP_SEQUENCE_H

#include <deque>
#include <iterator>
#include <list>
#include <string>
#include <vector>

class Sequence {
private:
    std::deque<int> m_bits;

public:
    explicit Sequence(int t_size = 4);
    explicit Sequence(const std::list<Sequence> &seqs);
    int operator()(int i) const;
    int &operator[](int i);
    Sequence &operator=(uint64_t seq);
    Sequence operator*(Sequence t_seq);
    uint64_t to_bits();
    int size();
    virtual void shift(int n);
    Sequence permutation(const std::vector<int> &permutation);
    Sequence subsequence(int begin, int end);

    std::string as_char_string();
    std::string as_bit_string();
};


#endif//INC_3DES_CPP_SEQUENCE_H
