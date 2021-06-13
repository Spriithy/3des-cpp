//
// Created by theophile on 06/05/2021.
//

#include "S_function.h"
#include <list>
#include <vector>

S_function::S_function(const int sboxes[8][4][16]) {
    // Allocate arrays of Sequences used to map inputs to outputs
    m_sboxes = new Sbox *[8];
    for (auto i = 0; i < 8; ++i) {
        m_sboxes[i] = new Sbox(sboxes[i]);
    }
}

S_function::~S_function() {
    for (auto i = 0; i < 8; ++i) {
        delete m_sboxes[i];
    }
    delete[] m_sboxes;
}

Sequence S_function::operator()(Sequence &seq) {
    std::vector<Sequence> seqs(8);

    // For each subsequence of size 6, map input to output using Sboxes
    for (auto i = 0; i < 8; ++i) {
        Sequence subseq = seq.subsequence(i * 6, (i + 1) * 6);
        seqs[8 - i - 1] = (*m_sboxes[8 - i - 1])(subseq);
    }

    return Sequence({seqs.begin(), seqs.end()});
}
