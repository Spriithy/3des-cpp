#ifndef INC_3DES_CPP_CRYPT_H
#define INC_3DES_CPP_CRYPT_H

#include "SequenceD.h"


class Crypt {
private:
    SequenceD<64> m_k1;
    SequenceD<64> m_k2;

public:
    Crypt(SequenceD<64> &k1, SequenceD<64> &k2) : m_k1(k1), m_k2(k2){};
    void operator()(const std::string &inputPath, const std::string &outputPath);
    void operator()(const std::string &inputPath, std::ostream &os);

private:
    SequenceD<64> &crypt(SequenceD<64> &seq);
};


class Decrypt {
private:
    SequenceD<64> m_k1;
    SequenceD<64> m_k2;


public:
    Decrypt(SequenceD<64> &k1, SequenceD<64> &k2) : m_k1(k1), m_k2(k2){};
    void operator()(const std::string &inputPath, const std::string &outputPath);
    void operator()(const std::string &inputPath, std::ostream &os);

private:
    SequenceD<64> &decrypt(SequenceD<64> &seq);
};


#endif//INC_3DES_CPP_CRYPT_H
