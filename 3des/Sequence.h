//
// Created by theophile on 03/27/2021.
//

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
    explicit Sequence(const std::list<Sequence> &t_seq);
    int operator()(int i) const;
    int &operator[](int i);
    Sequence &operator=(uint64_t seq);
    Sequence operator*(Sequence &t_seq);
    uint64_t to_bits();
    int size();
    void shift(int n);
    Sequence permutation(std::vector<int> &t_permutor);
    Sequence subsequence(int begin, int end);
    void print();
};


#endif//INC_3DES_CPP_SEQUENCE_H
