//
// Created by theophile on 06/05/2021.
//

#ifndef INC_3DES_CPP_S_FUNCTION_H
#define INC_3DES_CPP_S_FUNCTION_H

#include "Sbox.h"

class S_function {
private:
    Sbox **m_sboxes;

public:
    explicit S_function(const int sboxes[8][4][16]);
    ~S_function();
    S_function(const S_function &sFunction) = default;
    Sequence operator()(Sequence &seq);
};


#endif//INC_3DES_CPP_S_FUNCTION_H
