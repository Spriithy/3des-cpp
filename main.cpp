#include "3des/DES.h"
#include "3des/KeyGen.h"
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

    SequenceD<64> key{};
    std::cout << "  Original key: " << key.as_bit_string() << std::endl;

    DES des(key);
    auto desKey = des(key);
    std::cout << "  Cyphered key: " << desKey.as_bit_string() << std::endl;

    DESinv desInv(key);
    auto desInvKey = desInv(desKey);
    std::cout << "Decyphered key: " << desInvKey.as_bit_string() << std::endl;

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
