#include "3des/Sequence.h"
#include "3des/SequenceD.h"
#include "cli/Parser.h"
#include <iostream>

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

    Sequence seq(10);
    seq.print();
    std::cout << seq[1] << std::endl;
    seq.subsequence(1, 5).print();
    seq = 0b10;
    seq.print();
    Sequence seq2(10);
    seq2 = 0b11;
    (seq * seq2).print();

    SequenceD<64> sqd{};

    std::cout << sqd.to_string() << std::endl;

    std::cin >> sqd;
    std::cout << sqd << std::endl;

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
