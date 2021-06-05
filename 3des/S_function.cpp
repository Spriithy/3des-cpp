//
// Created by theophile on 06/05/2021.
//

#include "S_function.h"
#include <list>
#include <vector>

S_function::S_function(const int sboxes[8][4][16]) {
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
    for (auto i = 0; i < 8; ++i) {
        Sequence subseq = seq.subsequence(i * 8, (i + 1) * 8);
        seqs[i] = (*m_sboxes[i]) (subseq);
    }

    std::list<Sequence> seqList(seqs.begin(), seqs.end());
    return Sequence(seqList);
}
