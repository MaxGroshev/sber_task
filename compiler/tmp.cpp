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
ID      [a-zA-Z][a-zA-Z_0-9]*
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

{TABUL}           {loc->columns(4); loc->step();};
{WS}              {loc->columns(1); loc->step();};
{LINE}            {loc->lines(yyleng); loc->step();};
{I_LOVE_WINDOWS}  {};

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
"if"              {return make_if();};
"else"            {return make_else();};
"while"           {return make_while();};
"print"           {return make_output();};
"!"               {return make_negative();};
"?"               {return make_input();};
"("               {return make_op_pr();};
")"               {return make_cl_pr();};
"{"               {return make_op_br();};
"}"               {return make_cl_br();};
"||"              {return make_or();};
"&&"              {return make_and();};

{ONE_LINE_COMMENT} {}
{ID}              {return make_id();};
{DIGIT1}{DIGIT}*  {return make_num();};
{DIGIT}           {return make_num();};
.			      {return make_err();};

%{/*-----------------------------------------------------------------------*/%}

%%


