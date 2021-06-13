#include "Parser.h"
#include <iostream>

std::map<std::string, Flag> Parser::m_flag_map = {
        {"--key-gen", KEY_GEN},
        {"-c", CYPHER},
        {"-d", DECYPHER},
        {"-O", OUTPUT_FILE},
        {"-i", INPUT_KEY},
        {"-h", HELP},
        {"--help", HELP},
};

Parser::Parser(int t_argc, char **t_args) {
    m_args = std::vector<std::string>(t_args, t_args + t_argc);
    m_parsed_options = {};
}

ParsedOptions Parser::parse() {
    for (auto it = 1; it < m_args.size(); ++it) {
        std::string arg = m_args[it];
        if (!m_flag_map.contains(arg)) {
            m_parsed_options.error = true;
            if (arg[0] == '-') {
                std::cerr << "unrecognized option: " << arg << std::endl;
            } else {
                std::cerr << "unexpected argument: " << arg << std::endl;
            }
            continue;
        }

        bool has_next = it + 1 < m_args.size();
        switch (Flag flag = m_flag_map.at(arg); flag) {
            case HELP:
            case KEY_GEN:
                m_parsed_options.command = flag;
                break;
            case CYPHER:
            case DECYPHER:
                if (m_parsed_options.command != NONE) {
                    m_parsed_options.error = true;
                    std::cerr << "error: too many options" << std::endl;
                    return m_parsed_options;
                }
                m_parsed_options.command = flag;
                if (!has_next or m_flag_map.contains(m_args[it + 1])) {
                    m_parsed_options.inputFile = "-";
                } else {
                    m_parsed_options.inputFile = m_args[++it];
                }
                break;
            case INPUT_KEY:
                if (!has_next) {
                    m_parsed_options.error = true;
                    std::cerr << "error: missing input key parameter" << std::endl;
                    return m_parsed_options;
                }
                m_parsed_options.keyFile = m_args[++it];
                break;
            case OUTPUT_FILE:
                if (!has_next) {
                    m_parsed_options.error = true;
                    std::cerr << "error: missing output file parameter" << std::endl;
                    return m_parsed_options;
                }
                m_parsed_options.outputFile = m_args[++it];
                break;
            default:
                std::cout << arg << std::endl;
                break;
        }
    }
    return m_parsed_options;
}


Parser::~Parser() = default;
