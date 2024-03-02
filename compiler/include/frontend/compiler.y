%language "c++"
%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define parse.error    verbose
%locations
%param     {yy::driver_t* driver}

//-----------------------------------------------------------------------------------------

%code requires {

#include "tokens/scope.hpp"
#include "inode/inode.hpp"
#include "tokens/operators.hpp"
#include "tokens/comparator.hpp"
#include "tokens/conjunction.hpp"
#include "tokens/utils.hpp"
#include "tokens/io.hpp"

using namespace paracl;
using namespace backend;

namespace yy { class driver_t; }

}

%code {

#include "frontend/driver.hpp"
#include <iostream>


using namespace paracl;
using namespace backend;


scope_t* current_scope = new scope_t(nullptr);

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval, parser::location_type* loc, driver_t* driver);

}

}

//-----------------------------------------------------------------------------------------

%token
    IF       "if"
    ELSE     "else"
    WHILE    "while"
    PRINT   "print"
    INPUT    "?"
    ASSIGN   "="
    SCOLON   ";"
    PRINTLN
    LOOP
    TRUE
    FALSE
    THEN
    STRING_TYPE
    CHAR_TYPE
    INT_TYPE
    <std::string> ID
    <int> NUMBER
    MUL      "*"
    PLUS     "+"
    MINUS    "-"
    DIV      "/"
    MODULO   "%"
    OP_PR    "("
    CL_PR    ")"
    EQUAL    "=="
    NOT_EQUAL "!="
    GREATER  ">"
    NEGATIVE "!"
    LESS     "<"
    LS_EQUAL "<="
    GR_EQUAL ">="
    OP_BR    "{"
    CL_BR    "}"

    STRING

    AND      "&&"
    OR       "||"
    ERR
;

%right ASSIGN
%left  EQUAL NOT_EQUAL GREATER LESS GR_EQUAL LS_EQUAL NEGATIVE
%left  PLUS MINUS OR
%left  MUL DIV MODULO AND
%left  INPUT

%left UMINUS

//-----------------------------------------------------------------------------------------

%start program


%%

program:


%%

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval, parser::location_type* loc, driver_t* driver) {
    return driver->yylex(yylval, loc);
}

void parser::error(const parser::location_type& loc, const std::string& msg)
{
    driver->error(loc, msg);
}

}
