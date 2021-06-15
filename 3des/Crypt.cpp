#include "Crypt.h"
#include "DES.h"
#include <fstream>
#include <sstream>


void Crypt::operator()(const std::string &inputPath, const std::string &outputPath) {
    // open output file
    std::ofstream os(outputPath, std::ios::out | std::ios::binary | std::ios::trunc);
    operator()(inputPath, os);
    os.close();
}


void Crypt::operator()(const std::string &inputPath, std::ostream &os) {
    // Read input file and tell it to not ignore whitespaces while reading
    std::ifstream is(inputPath, std::ios::in | std::ios::binary | std::ios::ate);
    is >> std::noskipws;

    // Count the number of "dead" chars
    // That is, the number of characters that are used as "padding" at the end
    // of the cyphered file to match an round number of 64 bit sequences
    auto size = is.tellg();
    char deadChars = 8 - (size % 8 == 0 ? 8 : size % 8);

    // Write this number at the very start of the file so that decypher routine
    // knows about it upfront.
    os << deadChars;
    is.seekg(0, std::ios::beg);

    // Process each sequence in a "streaming" fashion
    SequenceD<64> seq;
    for (auto i = 0; i < size; i += 8) {
        is >> seq;
        os << crypt(seq);
    }

    is.close();
}


SequenceD<64> &Crypt::crypt(SequenceD<64> &seq) {
    DES c1(m_k1);
    seq = c1(seq);
    DESinv d(m_k2);
    seq = d(seq);
    DES c2(m_k1);
    seq = c2(seq);
    return seq;
}


void Decrypt::operator()(const std::string &inputPath, const std::string &outputPath) {
    std::ofstream os(outputPath, std::ios::out | std::ios::binary | std::ios::trunc);
    operator()(inputPath, os);
    os.close();
}


void Decrypt::operator()(const std::string &inputPath, std::ostream &os) {
    // Read input file and tell it to not ignore whitespaces while reading
    std::ifstream is(inputPath, std::ios::in | std::ios::binary | std::ios::ate);
    is >> std::noskipws;

    auto size = is.tellg();
    is.seekg(0, std::ios::beg);

    // Read the number of dead characters upfront so that we know how to truncate
    // input at the end.
    char deadChars;
    is >> deadChars;

    // Decypher each sequence in a streaming fashion
    SequenceD<64> seq;
    auto total = (size / 8) - (deadChars > 0 ? 1 : 0);
    for (auto i = 0; i < total; ++i) {
        is >> seq;
        os << decrypt(seq);
    }

    // If there is at least one dead character...
    if (deadChars > 0) {
        // Read last  sequence in a string stream
        std::ostringstream oss{};
        is >> seq;
        oss << decrypt(seq);
        // and truncate resul
        os << oss.str().substr(0, 8 - deadChars);
    }

    is.close();
}


SequenceD<64> &Decrypt::decrypt(SequenceD<64> &seq) {
    DESinv d1(m_k1);
    seq = d1(seq);
    DES c(m_k2);
    seq = c(seq);
    DESinv d2(m_k1);
    seq = d2(seq);
    return seq;
}
