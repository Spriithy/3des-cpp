#include "3des/KeyGen.h"
#include "3des/Sbox.h"
#include "3des/Sequence.h"
#include "3des/SequenceD.h"
#include "cli/Parser.h"
#include <iostream>
#include <sstream>

//
// CLI args
// --------
//
// --key-gen
//      Permet de générer une nouvelle clef de chiffrement et l'affiche sur la sortie standard.
//
// -i <file>
//      Permet de spécifier une clef utilisée pour le chiffrement ou le déchiffrement.
//
// -c <file>
//      Permet de chiffrer un fichier à l'aide d'une clef (spécifiée par le flag -i).
//      Si le fichier est omis, lecture depuis l'entrée standard. Par défaut, écrit
//      le résultat dans la sortie standard.
//
// -d <file>
//      Permet de déchiffrer un fichier à l'aide d'une clef (spécifiée par le flag -i).
//      Si le fichier est omis, lecture depuis l'entrée standard. Par défaut, écrit
//      le résultat dans la sortie standard.
//
//  -o <file>
//      Permet d'écrire le résultat d'une sous commande vers un nouveau fichier.
//
// Exemple:
//
//      ./3des -i ~/3des.key -c README.txt > README.3des
//

int main(int argc, char *argv[]) {
    Parser parser(argc, argv);
    ParsedOptions options = parser.parse();

    if (options.error) {
        return EXIT_FAILURE;
    }

    Sequence seq(8);
    seq = 0b01111000;
    std::cout << seq.as_bit_string() << std::endl;
    std::cout << seq.as_char_string() << std::endl;
    std::istringstream in(seq.as_bit_string());
    seq = read_seq_from_bits(in, 8);
    std::cout << seq.as_bit_string() << std::endl;
    std::cout << seq.as_char_string() << std::endl;

    Sequence seq2(32);
    seq2 = 0b01100001011000100110001101100100;
    std::cout << seq2.as_bit_string() << std::endl;
    std::cout << seq2.as_char_string() << std::endl;
    in = std::istringstream(seq2.as_bit_string());
    seq2 = read_seq_from_bits(in, 32);
    std::cout << seq2.as_bit_string() << std::endl;
    std::cout << seq2.as_char_string() << std::endl;

    SequenceD<64> seqd{};
    seqd.left() = 0b01100001011000100110001101100100;
    seqd.right() = 0b01100001011000100110001101100100;
    seqd.right().shift(16);
    std::cout << seqd.as_bit_string() << std::endl;
    std::cout << seqd.as_char_string() << std::endl;

    // Test read from bits
    in = std::istringstream(seqd.as_bit_string());
    read(in, seqd);
    std::cout << seqd.as_bit_string() << std::endl;
    std::cout << seqd.as_char_string() << std::endl;

    // Test read from chars
    std::istringstream("abcdcdab") >> seqd;
    std::cout << seqd.as_bit_string() << std::endl;
    print(seqd);
    print(seqd.left());
    print(seqd.right());
    std::cout << seqd.as_char_string() << std::endl;

    SequenceD<64> kseq{};
    KeyGen kg(kseq);
    for (auto i : SCHEDULED_LEFT_SHIFTS) {
        std::cout << kg.next().as_bit_string() << std::endl;
    }

    Sbox sbox(SBOX_MATRIX_1);
    seq = 0b100011;
    std::cout << sbox(seq).to_bits() << std::endl;

    switch (options.command) {
        case HELP:
            // show help message
            break;
        case KEY_GEN:
            // generate key
            break;
        case CYPHER:
            // cypher input
            break;
        case DECYPHER:
            // decypher input
            break;
        case NONE:
        default:
            break;
    }

    return EXIT_SUCCESS;
}
