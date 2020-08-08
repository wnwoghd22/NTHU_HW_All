%{
	//Definition
#include <stdio.h>

	int lineCount = 0;
%}

%%


\n{ lineCount++; 
	printf("line:%d\n", lineCount)}

%%

int main(void)
	{
		yylex();

		return 0;
	}


