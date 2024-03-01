#pragma once

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

#include <iostream>
#include <memory>
#include <fstream>
#include "grammar.tab.hpp"

//-------------------------------THIS_YYLEX_WILL_BE_CALLED---------------------------------

#define YY_DECL int my_lexer_t::yylex(yy::parser::location_type* loc)

//-----------------------------------------------------------------------------------------

class my_lexer_t : public yyFlexLexer {
    std::string cur_lex_type;
    std::string cur_lex_val;
    yy::parser::location_type yylloc;


    int make_plus() {
        cur_lex_type = "operator";
        std::cout << YYText();
        return yy::parser::token_type::PLUS;
    }

    int make_minus() {
        cur_lex_type = "operator";
        return yy::parser::token_type::MINUS;
    }

    int make_mul() {
        cur_lex_type = "operator";
        return yy::parser::token_type::MUL;
    }

    int make_div() {
        cur_lex_type = "operator";
        return yy::parser::token_type::DIV;
    }

    int make_modulo() {
        cur_lex_type = "operator";
        return yy::parser::token_type::MODULO;
    }

    int make_scolon() {
        cur_lex_type = "eoe";
        return yy::parser::token_type::SCOLON;
    }

    int make_equal() {
        cur_lex_type = "operator";
        return yy::parser::token_type::EQUAL;
    }

    int make_not_equal() {
        cur_lex_type = "operator";
        return yy::parser::token_type::NOT_EQUAL;
    }

    int make_ls_equal() {
        cur_lex_type = "operator";
        return yy::parser::token_type::LS_EQUAL;
    }

    int make_gr_equal() {
        cur_lex_type = "operator";
        return yy::parser::token_type::GR_EQUAL;
    }

    int make_less() {
        cur_lex_type = "operator";
        return yy::parser::token_type::LESS;
    }

    int make_greater() {
        cur_lex_type = "operator";
        return yy::parser::token_type::GREATER;
    }

    int make_assign() {
        cur_lex_type = "operator";

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

    int make_err() {
        cur_lex_type = "ERROR";
        return yy::parser::token_type::ERR;
    }

    int make_num() {
        cur_lex_type = "number";
        return yy::parser::token_type::NUMBER;;
    }

    int make_id() {
        cur_lex_type = "name";
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

    int make_true() {
        cur_lex_type = "logic_val";
        return yy::parser::token_type::TRUE;
    }

    int make_false() {
        cur_lex_type = "logic_val";
        return yy::parser::token_type::FALSE;
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

    public:
        virtual int yylex(yy::parser::location_type* loc);
        yy::parser::location_type get_location() const {return yylloc;};
        std::string get_cur_lex_type() const {return cur_lex_type;};
        void set_location(yy::parser::location_type* loc) {
            if (loc)
                yylloc = *loc;
        }

};
