%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

#define TRUE 1
#define FALSE 0

int prag_source;
int prag_token;
int prag_parse;
int prag_tag;
int system_flag;

//char array for lead line
char** tokens;
int lineLen = 0;

int lineNo = 1; //index for print line

void PrintToken(char* _type, char* _text)
{
	if ( prag_token == TRUE )
		printf("Line %d : #token %s:%s\n", lineNo, _type, _text);
}
void PushToken(char* _type, char* _text)
{
	lineLen++;

	tokens = realloc(tokens, sizeof(char*) * lineLen);
	tokens[lineLen - 1] = (char*)malloc(sizeof(char) * 100);
	strcpy(tokens[lineLen - 1], _text);

	PrintToken(_type, _text);
}
void PrintLine(int _idx)
{
	if ( prag_source == TRUE )
	{
		printf("Line %d : ", _idx);
		for (int i = 0; i < lineLen; i++)
			printf("%s ", tokens[i]);
		printf("\n");
	}
	for (int i = 0; i < lineLen; i++)
		free(tokens[i]);
	//tokens = realloc(tokens, sizeof(char*) * 1);
	lineLen = 0;
}
%}

%x COMMENT
/* Exclusive */
%x LineCOMMENT

%%

"/*"	{ BEGIN(COMMENT); }
<COMMENT>.*"*/"	{ BEGIN(0); }
<COMMENT>.*	{  }
<COMMENT>\n	{  }

"//"	{ BEGIN(LineCOMMENT); }
<LineCOMMENT>.*	{  }
<LineCOMMENT>\n	{ BEGIN(0); }

"#pragma token on"	{ prag_token = 1; }
"#pragma token off"	{ prag_token = 0; }
"#pragma source on"	{ prag_source = 1; }
"#pragma source off"	{ prag_source = 0; }
"#pragma parsing on"	{ prag_parse = 1; }
"#pragma parsing off"	{ prag_parse = 0; }
"#pragma tag on"	{ prag_tag = 1; }
"#pragma tag off"	{ prag_tag = 0; }
"#system on"		{ system_flag = 1; }
"#system off"		{ system_flag = 0; }

(for)	{ PushToken("KEY", yytext); return FOR; }
(do)	{ PushToken("KEY", yytext); return DO; }
(while)	{ return WHILE; }
(break)	{ return BREAK; }
(continue) { return CONTINUE; }
(if)	{ return IF; }
(else)	{ return ELSE; }
(return) { return RETURN; }
(struct) { return STRUCT; }
(switch) { return SWITCH; }
(case)	{ return CASE; }
(default) { return DEFAULT; }
(void)	{ return VOID; }
(int)	{ PushToken("KEY", yytext); return INT; }
(double) { PushToken("KEY", yytext); return DOUBLE; }
(float) { PushToken("KEY", yytext); return FLOAT; }
(char)	{ PushToken("KEY", yytext); return CHAR; }
(const)	{ PushToken("KEY", yytext); return CONST; }
(NULL)|(fclose)|(clearerr)|(feof)|(ferror)|(fflush)|(fgetpos)|(fopen)|(fread)|(freopen)|(fseek)|(fsetpos)|(ftell)|(fwrite)|(remove)|(rename)|(rewind)|(setbuf)|(setvbuf)|(tmpfile)|(tmpnam)|(fprintf)|(printf)|(sprintf)|(vfprintf)|(vprintf)|(vsprintf)|(fscanf)|(scanf)|(sscanf)|(fgetc)|(fgets)|(fputc)|(fputs)|(getc)|(getchar)|(gets)|(putc)|(putchar)|(puts)|(ungetc)|(perror) { return KEY; }

\".*\"	{ PushToken("STRING", yytext);
	yylval.stringVal = strdup(yytext);
	return sVal; }
\'.\'	{ yylval.charVal = yytext[1]; return cVal; }

0|[1-9][0-9]*	{ PushToken("INT", yytext);
		yylval.intVal = atoi(yytext);
		return iVal; }
00|0[1-9][0-9]*	{ /*octal*/ }
0x0|0x[abcdefABCDEF123456789][abcdefABCDEF01233456789]* { /*hexa*/ }
[0-9]+\.[0-9]*	{ yylval.doubleVal = atof(yytext); return fVal; }
[0-9]*\.[0-9]+  { yylval.doubleVal = atof(yytext); return fVal; }
[_a-zA-Z][_a-zA-Z0-9]* { PushToken("ID", yytext); 
			yylval.stringVal = strdup(yytext); return ID; }

(\+\+)	{ PushToken("OP", yytext); return INC; }
(\-\-)	{ return DEC; }
!	{ return '!'; }
(==)	{ return EQ; }
(!=)	{ return NQ; }
(<=)	{ return GQ; }
(>=)	{ return LQ; }
(&&)	{ return AND; }
(\|\|)	{ return OR; }
\+	{ PushToken("OP", yytext); return '+'; }
\-	{ PushToken("OP", yytext); return '-'; }
\*	{ PushToken("OP", yytext); return '*'; }
\/	{ PushToken("OP", yytext); return '/'; }
%	{ return '%'; }
\<	{ return GT ; }
\>	{ return LT ; }
=	{ PushToken("OP", yytext); return '='; }
(\+=)	{ return PEQ; }
(\-=)	{ return MEQ; }
&	{ return BAND; }
\|	{ return BOR; }

:	{ PushToken("PUNC", yytext); return ':'; }
;	{ PushToken("PUNC", yytext); return ';'; }
,	{ PushToken("PUNC", yytext); return ','; }
\.	{ return '.'; }
"["	{ PushToken("PUNC", yytext); return '['; }
"]"	{ return ']'; }
"("	{ return '('; }
")"	{ return ')'; }
"{"	{ return '{'; }
"}"	{ return '}'; }

\t {;}
\n { PrintLine(lineNo); lineNo++; }

%%
