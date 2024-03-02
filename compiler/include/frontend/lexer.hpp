#pragma once

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

#include <iostream>
#include <memory>
#include <iomanip>
#include <fstream>
#include "grammar.tab.hpp"

//-------------------------------THIS_YYLEX_WILL_BE_CALLED---------------------------------

#define YY_DECL int my_lexer_t::yylex(yy::parser::location_type* loc)

//-----------------------------------------------------------------------------------------

class my_lexer_t : public yyFlexLexer {
    std::string cur_lex_type;
    std::string cur_lex_val;
    std::string token_extra_dat;
    yy::parser::location_type yylloc;


    int make_arith(int lex_val) {
        cur_lex_type = "arith_operator";
        return lex_val;
    }

    int make_scolon() {
        cur_lex_type = "eoe";
        return yy::parser::token_type::SCOLON;
    }

    int make_compare(int lex_val) {
        cur_lex_type = "compare operator";
        return lex_val;
    }

    int make_assign() {
        cur_lex_type = "assign operator";

        return yy::parser::token_type::ASSIGN;
    }

    int make_if() {
        cur_lex_type = "cond operator";
        return yy::parser::token_type::IF;
    }

    int make_while() {
        cur_lex_type = "cond operator";
        return yy::parser::token_type::WHILE;
    }

    int make_else() {
        cur_lex_type = "cond operator";
        return yy::parser::token_type::ELSE;
    }

    int make_print() {
        cur_lex_type = "iostream";
        return yy::parser::token_type::PRINT;
    }

    int make_input() {
        cur_lex_type = "iostream";
        return yy::parser::token_type::INPUT;
    }

    int make_op_pr() {
        cur_lex_type = "bracket";
        return yy::parser::token_type::OP_PR;
    }

    int make_cl_pr() {
        cur_lex_type = "bracket";
        return yy::parser::token_type::CL_PR;
    }

    int make_op_br() {
        cur_lex_type = "bracket";
        return yy::parser::token_type::OP_BR;
    }

    int make_cl_br() {
        cur_lex_type = "bracket";
        return yy::parser::token_type::CL_BR;
    }

    int make_err(const char* error) {
        cur_lex_type = "ERROR";
        token_extra_dat = error;
        return yy::parser::token_type::ERR;
    }

    int make_num() {
        cur_lex_type = "number";
        return yy::parser::token_type::NUMBER;;
    }

    int make_id() {
        cur_lex_type = "ID";
        return yy::parser::token_type::ID;
    }

    int make_and() {
        cur_lex_type = "cond_operator";
        return yy::parser::token_type::AND;
    }

    int make_or() {
        cur_lex_type = "cond_operator";
        return yy::parser::token_type::OR;
    }

    int make_negative() {
        cur_lex_type = "not";
        return yy::parser::token_type::NEGATIVE;
    }

    int make_logic_val(int lex_val) {
        cur_lex_type = "logic_val";
        return lex_val;
    }

    int make_then() {
        cur_lex_type = "operator";
        return yy::parser::token_type::THEN;
    }

    int make_loop() {
        cur_lex_type = "cond_operator";
        return yy::parser::token_type::LOOP;
    }

    int make_println() {
        cur_lex_type = "iostream";
        return yy::parser::token_type::PRINTLN;
    }

    int make_type(int lex_val) {
        cur_lex_type = "type_indificator";
        return lex_val;
    }
    int make_string() {
        cur_lex_type = "string";
        return yy::parser::token_type::STRING;
    }

    public:
        virtual int yylex(yy::parser::location_type* loc);
        yy::parser::location_type get_location() const {return yylloc;};
        std::string get_cur_lex_type() const {return cur_lex_type;};
        std::string get_token_extra_dat() const {return token_extra_dat;};
        void set_location(yy::parser::location_type* loc) {
            if (loc)
                yylloc = *loc;
        }

};
