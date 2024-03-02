%option c++
%option yylineno
%option debug
%option yyclass="my_lexer_t"

/*---------------------------------------------------------------------------*/

%{
#include "lexer.hpp"
%}

WS      [ \v]
TABUL   [\t]
LINE    [\n]+
I_LOVE_WINDOWS [\r]+
DIGIT   [0-9]
DIGIT1  [1-9]

/*---------------------------------------------------------------------------*/

STRING_TYPE "String"
CHAR_TYPE   "Char"
INT_TYPE    "Int"

/*---------------------------------------------------------------------------*/

IF    [i|I][f|F]
WHILE [w|W][h|H][i|I][l|L][e|E]
ELSE  [e|E][l|L][s|S][e|E]
LOOP  [l|L][o|O][o|O][p|P]
NOT   [n|N][o|O][t|T]
PRINT [p|P][r|R][i|I][n|N][t|T]
PRINTLN [p|P][r|R][i|I][n|N][t|T][l|L][n|N]
THEN  [t|T][h|H][e|E][n|N]
ID    [a-zA-Z][a-zA-Z_0-9]*
TRUE  [t][r|R][u|U][e|E]
FALSE [f][a|A][l|L][s|S][e|E]

ONE_LINE_COMMENT "--".*

/*---------------------------------------------------------------------------*/

%x COMMENT
%x STRING_MATCH

%%
    int com_level = 0;

%{
    loc->columns(yyleng);
    loc->step();
    set_location(loc);
%}

"/*"              {BEGIN(COMMENT);}
<COMMENT>{
    "/*"          {com_level++;}
    "*/"          {if (com_level)
                      com_level--;
                  else BEGIN(INITIAL);}
    "*"+          {};
    [/]           {};
    [^/*\n]+      {};
    \0            {make_err("ASCII 0 in comment"); BEGIN(INITIAL); return 1;}
    <<EOF>>       {make_err("EOF in comment");     BEGIN(INITIAL); return 1;}
    {LINE}        {loc->lines(yyleng); loc->step();};
}


["]              {BEGIN(STRING_MATCH);}
<STRING_MATCH>{
    ["]           {BEGIN(INITIAL);}

    [^"\n]+       {return make_string();};
    \0            {make_err("ASCII 0 in string"); BEGIN(INITIAL); return 1;}
    <<EOF>>       {make_err("EOF in string");     BEGIN(INITIAL); return 1;}
    {LINE}        {loc->lines(yyleng); loc->step();};
}

%{/*-----------------------------------------------------------------------*/%}

{TABUL}            {loc->columns(4);    loc->step();};
{WS}               {loc->columns(1);    loc->step();};
{LINE}             {loc->lines(yyleng); loc->step();};
{I_LOVE_WINDOWS}   {};
{ONE_LINE_COMMENT} {}

%{/*-----------------------------------------------------------------------*/%}

"+"               {return make_arith(yy::parser::token_type::PLUS);};
"-"               {return make_arith(yy::parser::token_type::MINUS);};
"*"               {return make_arith(yy::parser::token_type::MUL);};
"/"               {return make_arith(yy::parser::token_type::DIV);};
"%"               {return make_arith(yy::parser::token_type::MODULO);};
"=="              {return make_compare(yy::parser::token_type::EQUAL);};
"<="              {return make_compare(yy::parser::token_type::LS_EQUAL);};
">="              {return make_compare(yy::parser::token_type::GR_EQUAL);};
"!="              {return make_compare(yy::parser::token_type::NOT_EQUAL);};
">"               {return make_compare(yy::parser::token_type::GREATER);};
"<"               {return make_compare(yy::parser::token_type::LESS);};
"="               {return make_assign();};
";"               {return make_scolon();};
"!"               {return make_negative();};
"?"               {return make_input();};
"("               {return make_op_pr();};
")"               {return make_cl_pr();};
"{"               {return make_op_br();};
"}"               {return make_cl_br();};
"||"              {return make_or();};
"&&"              {return make_and();};


{IF}              {return make_if();};
{WHILE}           {return make_while();};
{ELSE}            {return make_else();}
{LOOP}            {return make_loop();}
{NOT}             {return make_negative();}
{PRINT}           {return make_print();}
{PRINTLN}         {return make_println();}
{THEN}            {return make_then();}
{TRUE}            {return make_logic_val(yy::parser::token_type::TRUE);}
{FALSE}           {return make_logic_val(yy::parser::token_type::FALSE);}
{STRING_TYPE}     {return make_type(yy::parser::token_type::STRING_TYPE);}
{CHAR_TYPE}       {return make_type(yy::parser::token_type::CHAR_TYPE);}
{INT_TYPE}        {return make_type(yy::parser::token_type::INT_TYPE);}

{ID}              {return make_id();};
{DIGIT1}{DIGIT}*  {return make_num();};
{DIGIT}           {return make_num();};
.			      {return make_err("Unknown symbol");};

%{/*-----------------------------------------------------------------------*/%}

%%

