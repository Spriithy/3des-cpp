//
// Created by theophile on 03/27/2021.
//

#include "Sequence.h"
#include <algorithm>
#include <iostream>
#include <random>

Sequence::Sequence(int t_size) {
    m_bits = std::deque<int>(t_size);

    // This lambda function is a courtesy of :
    // https://www.fluentcpp.com/2019/05/24/how-to-fill-a-cpp-collection-with-random-values/
    auto randBetween = [](int low, int high) {
        auto wrapped = [distribution_ = std::uniform_int_distribution<int>(low, high),
                        random_engine_ = std::mt19937{std::random_device{}()}]() mutable {
            return distribution_(random_engine_);
        };
        return wrapped;
    };

    std::ranges::generate(m_bits, randBetween(0, 1));
}

Sequence::Sequence(const std::list<Sequence> &t_seq) {
    m_bits = std::deque<int>(0);
    for (auto seq : t_seq) {
        m_bits.insert(std::end(m_bits), std::begin(seq.m_bits), std::end(seq.m_bits));
    }
}

int Sequence::operator()(int i) const {
    return m_bits.at(i);
}

int &Sequence::operator[](int i) {
    return m_bits.at(i);
}

int Sequence::size() {
    return m_bits.size();
}

void Sequence::shift(int n) {
    for (auto i = 0; i < n; i++) {
        auto front = m_bits.front();
        m_bits.pop_front();
        m_bits.push_back(front);
    }
}

void Sequence::print() {
    int n = size();
    for (auto i = 0; i < n; ++i) {
        std::cout << m_bits[n - i - 1];
    }
    std::cout << std::endl;
}

Sequence &Sequence::operator=(uint64_t seq) {
    for (auto i = 0; i < size(); ++i) {
        m_bits[i] = (seq >> i) & 1;
    }
    return *this;
}

uint64_t Sequence::to_bits() {
    uint64_t bits(0);
    for (int i = 0; i < size(); ++i) {
        bits |= m_bits[i] << i;
    }
    return bits;
}

Sequence Sequence::operator*(Sequence &t_seq) {
    Sequence res(size());
    if (size() != t_seq.size()) {
        return res;
    }

    res = to_bits() ^ t_seq.to_bits();
    return res;
}
