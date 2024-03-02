#pragma once

#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <memory>
#include <FlexLexer.h>
#include "lexer.hpp"

#include "tokens/cond_operators.hpp"
#include "inode/inode.hpp"
#include "error_hadl.hpp"
#include "grammar.tab.hpp"

//-----------------------------------------------------------------------------------------

namespace yy {

class driver_config_t {
    private:
        std::ifstream f_input = std::ifstream();
    public:
        std::istream& input   = std::cin;

        driver_config_t() {};
        driver_config_t(const int argc, char** argv) :
            f_input(get_f_input(argc, argv)), input(f_input) {

            if (!input.good()) {
                throw ("ParaCl: No such file or directory: " + std::string(argv[1]));
            }
        }

        std::ifstream get_f_input (const int argc, char** argv) {
            for (int i = 1; i < argc; i++) {
                std::string arg = argv[i];
                std::ifstream file_input(argv[i]);
                return file_input;

            };
            return std::ifstream();
        }
        ~driver_config_t() {
            f_input.close();
        }
};

//-----------------------------------------------------------------------------------------

class driver_t {
    private:
        std::unique_ptr<driver_config_t> dr_config_;
        std::unique_ptr<my_lexer_t> plex_;
        std::vector<std::string> prog_data_;
    public:
        std::vector<frontend::error_t> compil_err;
        bool compil_err_flag = false;


        driver_t(std::unique_ptr<my_lexer_t> plex, std::unique_ptr<driver_config_t> dr_config) :
            plex_(std::move(plex)), dr_config_(std::move(dr_config)) {

            plex_->my_lexer_t::switch_streams(dr_config_->input, std::cout);

            std::string prog_str;
            while (getline(dr_config_->input, prog_str)) {
                prog_data_.push_back(prog_str);
            }

            dr_config_->input.clear();
            dr_config_->input.seekg(0, std::ios::beg);
        }

        parser::token_type yylex(parser::semantic_type* yylval, parser::location_type* loc) {

            parser::token_type tt = {};
            while (tt = static_cast<parser::token_type>(plex_->yylex(loc))) {
                if (tt == yy::parser::token_type::ERR) {
                    error(*loc, plex_->get_token_extra_dat());
                    continue;
                }
                std::cout << "| CUR_LEX_TYPE: " << plex_->get_cur_lex_type() << "\n";
                std::cout << "| LEX_VAL: " << "<\033[32m" << plex_->YYText() << "\033[0m>" << "\n\n";
            }
            print_errors();

            return tt;
        }

        bool parse() {
            parser parser(this);
            bool res = parser.parse();
            return !res;
        }

        void error(const location& loc, const std::string& msg) {
            compil_err_flag = true;

            // yy::parser::location_type my_loc = plex_->get_location();
            const frontend::error_t my_error {msg, prog_data_[loc.begin.line - 1],
                                                  plex_->get_cur_lex_type(), loc};
            compil_err.push_back(std::move(my_error));

        }

        int print_errors() const {
            for (const auto& err : compil_err) {
                err.pretty_error_msg();
            }
            return 1;
        }
};

}
