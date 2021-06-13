#include "3des/Crypt.h"
#include "3des/KeyGen.h"
#include "cli/Parser.h"
#include <iostream>

//
// CLI args
// --------
//
// --key-gen
//      Permet de generer une nouvelle clef de chiffrement et l'affiche sur la sortie standard.
//
// -i <fichier>
//      Permet de specifier une clef utilisee pour le chiffrement ou le dechiffrement.
//
// -c <fichier>
//      Permet de chiffrer un fichier a l'aide d'une clef (specifiee par le flag -i).
//      Si le fichier est omis, lecture depuis l'entree standard. Par defaut, ecrit
//      le resultat dans la sortie standard.
//
// -d <fichier>
//      Permet de dechiffrer un fichier a l'aide d'une clef (specifiee par le flag -i).
//      Si le fichier est omis, lecture depuis l'entree standard. Par defaut, ecrit
//      le resultat dans la sortie standard.
//
//  -O <fichier>
//      Permet d'ecrire le resultat d'une sous commande vers un nouveau fichier plutot que
//      dans la sortie standard.
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

    switch (options.command) {
        case HELP:
            std::cout << "Usage: 3des [--key-gen] [-i <fichier>] [-c <fichier>] [-d <fichier>] [-O <fichier>]" << std::endl;
            std::cout << std::endl;
            std::cout << "Arguments:" << std::endl;
            std::cout << "  --key-gen" << std::endl;
            std::cout << "       Permet de generer une nouvelle clef de chiffrement et l'affiche sur la sortie standard." << std::endl;
            std::cout << std::endl;
            std::cout << "  -i <fichier>" << std::endl;
            std::cout << "       Permet de specifier une clef utilisee pour le chiffrement ou le dechiffrement." << std::endl;
            std::cout << std::endl;
            std::cout << "  -c <fichier>" << std::endl;
            std::cout << "       Permet de chiffrer un fichier a l'aide d'une clef (specifiee par le flag -i)." << std::endl;
            std::cout << "       Par defaut, ecrit le resultat dans la sortie standard." << std::endl;
            std::cout << std::endl;
            std::cout << "  -d <fichier>" << std::endl;
            std::cout << "       Permet de dechiffrer un fichier a l'aide d'une clef (specifiee par le flag -i)." << std::endl;
            std::cout << "       Par defaut, ecrit le resultat dans la sortie standard." << std::endl;
            std::cout << std::endl;
            std::cout << "  -O <fichier>" << std::endl;
            std::cout << "      Permet d'ecrire le resultat d'une sous commande vers un nouveau fichier plutot que" << std::endl;
            std::cout << "      dans la sortie standard." << std::endl;
            std::cout << std::endl;
            std::cout << "Exemple:" << std::endl;
            std::cout << std::endl;
            std::cout << "      ./3des -i ~/3des.key -c README.txt > README.3des" << std::endl;
            std::cout << std::endl;
            break;
        case KEY_GEN: {
            SequenceD<64> k1{}, k2{};
            if (options.outputFile.empty()) {
                write3DESKeys(std::cout, k1, k2);
            } else {
                write3DESKeys(options.outputFile, k1, k2);
            }
        } break;
        case CYPHER: {
            auto [k1, k2] = read3DESKeys(options.keyFile);
            Crypt crypt(k1, k2);
            if (options.outputFile.empty()) {
                crypt(options.inputFile, std::cout);
            } else {
                crypt(options.inputFile, options.outputFile);
            }
        } break;
        case DECYPHER: {
            auto [k1, k2] = read3DESKeys(options.keyFile);
            Decrypt decrypt(k1, k2);
            if (options.outputFile.empty()) {
                std::cout << std::ios::binary;
                decrypt(options.inputFile, std::cout);
            } else {
                decrypt(options.inputFile, options.outputFile);
            }
        } break;
        case NONE:
        default:
            break;
    }

    return EXIT_SUCCESS;
}
