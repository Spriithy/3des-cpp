//
// Created by theophile on 06/05/2021.
//

#include "Sbox.h"
#include <iostream>

Sbox::Sbox(const int sbox_matrix[4][16]) {
    m_tab = new Sequence *[4];
    for (auto i = 0; i < 4; ++i) {
        m_tab[i] = new Sequence[16];
        for (auto j = 0; j < 16; ++j) {
            m_tab[i][j] = sbox_matrix[i][j];
        }
    }
}


Sbox::~Sbox() {
    for (auto i = 0; i < 16; ++i) {
        delete[] m_tab[i];
    }
    delete[] m_tab;
}

Sequence Sbox::operator()(const Sequence &seq) {
    auto x = seq(0) | (seq(5) << 1);
    auto y = seq(1) | (seq(2) << 1) | (seq(3) << 2) | (seq(4) << 3);
    return m_tab[x][y];
}
