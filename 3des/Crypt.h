//
// Created by theophile on 06/06/2021.
//

#ifndef INC_3DES_CPP_CRYPT_H
#define INC_3DES_CPP_CRYPT_H


#include "SequenceD.h"


class Crypt {
private:
    SequenceD<64> m_k1;
    SequenceD<64> m_k2;

public:
    Crypt(SequenceD<64> &k1, SequenceD<64> &k2) : m_k1(k1), m_k2(k2){};
    void operator()(std::string inputPath, std::string outputPath);
};


class Decrypt {
public:
    Decrypt(SequenceD<64> &k1, SequenceD<64> &k2);
    void operator()(std::string inputPath, std::string outputPath);
};


#endif//INC_3DES_CPP_CRYPT_H
