//
// Created by theophile on 03/27/2021.
//

#ifndef INC_3DES_CPP_PARSER_H
#define INC_3DES_CPP_PARSER_H

#include <map>
#include <string>
#include <vector>

enum Flag {
    // No flag specified
    NONE,

    // -h / --help
    HELP,
    // --key-gen
    KEY_GEN,

    // -c <file>
    CYPHER,

    // -d <file>
    DECYPHER,

    // -i <file>
    INPUT_KEY,

    // -o <file>
    OUTPUT_FILE,
};

struct ParsedOptions {
    bool error;
    Flag command;
    std::string keyFile;
    std::string inputFile;
    std::string outputFile;
};

class Parser {
private:
    std::vector<std::string> m_args;
    ParsedOptions m_parsed_options;
    static std::map<std::string, Flag> m_flag_map;

public:
    Parser(int t_argc, char *t_args[]);
    ParsedOptions parse();
    ~Parser();
};


#endif//INC_3DES_CPP_PARSER_H
