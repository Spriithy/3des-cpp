//
// Created by theophile on 06/05/2021.
//

#ifndef INC_3DES_CPP_F_H
#define INC_3DES_CPP_F_H


#include "KeyGen.h"
#include "S_function.h"
class F {
private:
    KeyGen m_keyGen;
    S_function m_sFunction;

public:
    explicit F(SequenceD<64> &key) : m_keyGen(key), m_sFunction(SBOX_MATRICES){};
    Sequence operator()(Sequence &seq);
};


#endif//INC_3DES_CPP_F_H
