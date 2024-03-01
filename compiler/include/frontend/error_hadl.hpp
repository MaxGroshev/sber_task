#pragma once
#include <iostream>
#include <string>
#include <cstring>

#define RED_C    "\033[91m"
#define GREEN_C  "\033[32m"
#define BLUE_C   "\033[36m"
#define YELLOW_C "\033[33m"
#define RESET_C  "\033[0m"

//-----------------------------------------------------------------------------------------

namespace frontend {

struct error_t {
    std::string msg_;
    const std::string prog_str_ = "";
    std::string cur_lex_type_ = "";
    yy::parser::location_type loc_;

    error_t(std::string msg, const std::string prog_str, std::string cur_lex_type, yy::parser::location_type loc) :
                        msg_(msg), prog_str_(prog_str), loc_(loc), cur_lex_type_(cur_lex_type) {}

    error_t(std::string msg, std::string cur_lex_type, yy::parser::location_type loc) :
                        msg_(msg), loc_(loc), cur_lex_type_(cur_lex_type) {}

    void pretty_error_msg() const {

        std::cerr << "---------------------------------------------------------------\n";
        std::cerr << "| " << RED_C << msg_ << RESET_C <<'|' << '\n';
        std::cerr << "| in line: " << loc_.end.line << '\n';
        std::cerr << "| lexem_type : "<< cur_lex_type_ << '\n';

        std::cerr << "| " << prog_str_  << '\n';
        for (int i = 0; i < std::strlen("| ") + loc_.begin.column; i++) {
            std::cerr << " ";
        }
        std::cerr << RED_C << "^" << RESET_C << '\n';
        std::cerr << "---------------------------------------------------------------\n";

    }
};

}
