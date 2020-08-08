%{
#include "simple.tab.h"
extern int line_number;
%}
%option noyywrap

%%
"float"	{ printf("from flex float %s\n", yytext); return FLOAT; }
"int"	{ printf("from flex int %s\n", yytext); return INT; }
[;]	{return *yytext;}
[_a-zA-Z][_a-zA-Z0-9]*	{ printf("from flex Indentifier %s\n", yytext); return IDENTIFIER; }
[ \t\r]+	/* eat up whitespace */
[\n]	{ line_number++; }
%%

