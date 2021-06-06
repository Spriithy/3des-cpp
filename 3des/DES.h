//
// Created by theophile on 06/06/2021.
//

#ifndef INC_3DES_CPP_DES_H
#define INC_3DES_CPP_DES_H

#include "F.h"
#include "SequenceD.h"

class DES {
private:
    F m_f;

public:
    explicit DES(SequenceD<64> &key) : m_f(key){};
    SequenceD<64> operator()(SequenceD<64> seq);
};


class DESinv {
private:
    Finv m_finv;

public:
    explicit DESinv(SequenceD<64> &key) : m_finv(key){};
    SequenceD<64> operator()(SequenceD<64> seq);
};

#endif//INC_3DES_CPP_DES_H
