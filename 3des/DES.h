//
// Created by theophile on 06/06/2021.
//

#ifndef INC_3DES_CPP_DES_H
#define INC_3DES_CPP_DES_H

#include "F.h"
#include "SequenceD.h"

class DES {
private:
    SequenceD<64> m_key;

public:
    explicit DES(SequenceD<64> &key) : m_key(key){};
    SequenceD<64> operator()(SequenceD<64> seq);
};


class DESinv {
private:
    SequenceD<64> m_key;

public:
    explicit DESinv(SequenceD<64> &key) : m_key(key){};
    SequenceD<64> operator()(SequenceD<64> seq);
};

#endif//INC_3DES_CPP_DES_H
