#include "KeyGen.h"
#include "Permutation.h"
#include <fstream>


KeyGen::KeyGen(SequenceD<64> &key) : m_round(0) {
    m_rolling = Permutation<64, 56>{}(key, PC1);
}


SequenceD<48> KeyGen::next() {
    auto n = SCHEDULED_LEFT_SHIFTS[m_round++];
    m_rolling.shift(n);
    return Permutation<56, 48>{}(m_rolling, PC2);
}


std::pair<SequenceD<64>, SequenceD<64>> read3DESKeys(const std::string &keyFile) {
    SequenceD<64> k1, k2;
    std::ifstream in(keyFile, std::ios::in | std::ios::binary);
    in >> std::noskipws;
    in >> k1;
    in >> k2;
    in.close();
    return {k1, k2};
}


void write3DESKeys(const std::string &keyFile, SequenceD<64> &k1, SequenceD<64> &k2) {
    std::ofstream out(keyFile, std::ios::out | std::ios::binary | std::ios::trunc);
    write3DESKeys(out, k1, k2);
    out.close();
}


void write3DESKeys(std::ostream &os, SequenceD<64> &k1, SequenceD<64> &k2) {
    os << k1;
    os << k2;
    os << std::endl;
}
