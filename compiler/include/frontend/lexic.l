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
TRUE  [t][r|R][u|u][e|E]
FALSE [f][a|A][l|L][s|S][e|E]

ONE_LINE_COMMENT "//".*

/*---------------------------------------------------------------------------*/

%x COMMENT
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
    {LINE}        {loc->lines(yyleng); loc->step();};
}

%{/*-----------------------------------------------------------------------*/%}

{TABUL}           {loc->columns(4);    loc->step();};
{WS}              {loc->columns(1);    loc->step();};
{LINE}            {loc->lines(yyleng); loc->step();};
{ONE_LINE_COMMENT} {}
{I_LOVE_WINDOWS}   {};

%{/*-----------------------------------------------------------------------*/%}

"+"               {return make_plus();};
"-"               {return make_minus();};
"*"               {return make_mul();};
"/"               {return make_div();};
"%"               {return make_modulo();};
";"               {return make_scolon();};
"=="              {return make_equal();};
"<="              {return make_ls_equal();};
">="              {return make_gr_equal();};
"!="              {return make_not_equal();};
">"               {return make_greater();};
"<"               {return make_less();};
"="               {return make_assign();};
{IF}              {return make_if();};
{WHILE}           {return make_while();};
{ELSE}            {return make_else();}
{LOOP}            {return make_loop();}
{NOT}             {return make_negative();}
{PRINT}           {return make_print();}
{PRINTLN}         {return make_println();}
{THEN}            {return make_then();}
{TRUE}            {return make_true();}
{FALSE}           {return make_false();}
{STRING_TYPE}     {return make_type(yy::parser::token_type::STRING_TYPE);}
{CHAR_TYPE}       {return make_type(yy::parser::token_type::CHAR_TYPE);}
{INT_TYPE}        {return make_type(yy::parser::token_type::INT_TYPE);}
"!"               {return make_negative();};
"?"               {return make_input();};
"("               {return make_op_pr();};
")"               {return make_cl_pr();};
"{"               {return make_op_br();};
"}"               {return make_cl_br();};

"||"              {return make_or();};

"&&"              {return make_and();};

{ID}              {return make_id();};
{DIGIT1}{DIGIT}*  {return make_num();};
{DIGIT}           {return make_num();};
.			      {return make_err();};

%{/*-----------------------------------------------------------------------*/%}

%%

