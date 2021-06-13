#include "3des/DES.h"
#include "3des/KeyGen.h"
#include "3des/Permutation.h"
#include "3des/S_function.h"
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
    auto options = parser.parse();

    if (options.error) {
        return EXIT_FAILURE;
    }

    Sequence l(32), r(32);
    l = 0b10001111000011110000111100001111;
    r = 0b11110000111100001111000011111000;

    SequenceD<64> key{l, r};

    SequenceD<64> text;
    std::cin >> text;

    std::cout << "   Original key: " << key << std::endl;
    std::cout << "  Original text: " << text << std::endl;

    DES des(key);
    auto desText = des(text);
    std::cout << "  Cyphered text: " << desText << std::endl;

    DESinv desInv(key);
    auto desInvText = desInv(desText);
    std::cout << "Decyphered text: " << desInvText << std::endl;

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
