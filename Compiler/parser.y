%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolTable.h"
extern FILE* yyin;
FILE* f_asm;

//typedef char* string;

Node* IDENT;

int yylex();
void yyerror(char* msg);

extern int prag_source;
extern int prag_token;
extern int prag_parse;
extern int prag_tag;
extern int system_flag;
extern int lineNo;

int type = 0;
int para_num;
int offset_count = 0;

%}
%start Cmp_Stmt

%union{
	int intVal;
	double doubleVal;
	char charVal;
	char* stringVal;

	struct _TreeNode* _node;
	struct _parameter* _par;
	//struct symbol *sym;
}
%token VOID RETURN STRUCT CONST
%token <intVal> iVal INT DOUBLE FLOAT CHAR STRING
%token <doubleVal> fVal
%token <charVal> cVal
%token <stringVal> sVal ID
%token KEY OP PUNC

%token NOT EQ NQ GQ LQ GT LT AND OR BAND BOR PEQ MEQ

%token <intVal> IF 
%token ELSE
%token SWITCH CASE DEFAULT BREAK
%token <intVal> WHILE DO FOR CONTINUE

%left OR
%left AND
%left BOR
%left BAND
%left EQ NQ
%left GQ LQ GT LT
%left '-' '+' 
%left '*' '/' '%'
%nonassoc UMINUS INC DEC NOT
%right "then" ELSE

%type <intVal> Stmt Expr 
%type <_node> E arr_option para_call para_call_option
%type <_par> parameter para_option
%type <intVal> type assign_option return_option

%%
Cmp_Stmt : 
	 | Stmt Cmp_Stmt
	 ;
Stmt : { if( prag_tag == 1 )
     		printf("<stmt>"); }  
     Expr ';' { 
     		if( prag_parse == 1 )
     			printf("Line %d - result : %d \n", lineNo, $2);
		if( prag_tag == 1 )
			printf(";</stmt>");
		$$ = $2;
		}
     | Decl	{
		if( prag_parse == 1 )
			printf("\n"); 
		$$ = TRUE;
		}
     |
		IF '('
		{ if( prag_tag == 1 )
			printf("<stmt>if(");
			$1 = offset_count++;
			}
		Expr')'
		{ if( prag_tag == 1)
			printf(")");
			
			fprintf(f_asm,"        lw t0, -4(sp)\n");
			fprintf(f_asm,"        li t1, 0\n");
			fprintf(f_asm,"        beq t0, t1, ELSE%d\n", $1);
		}
		C_Stmt
		{	
			fprintf(f_asm,"        j EXIT%d\n", $1);	
			fprintf(f_asm,"ELSE%d:\n", $1);
		}
		if_option
		{ 	
		$$ = $4;
			fprintf(f_asm,"EXIT%d:\n", $1);
		}
     | SWITCH '(' ID ')'
	'{'
		{ if( prag_tag == 1)
			printf("<stmt>switch(%s){", $3); }
		switch_stmt
	'}' { $$ = 1; }
	|
	WHILE '('
	{ 
		if( prag_tag == 1 )
			printf("<stmt>while(");
			
		$1 = offset_count++;
		fprintf(f_asm,"WHILE%d:\n", $1);
	}
	Expr ')'
	{ 
		if( prag_tag == 1 ) printf(")"); 
		
		fprintf(f_asm,"        lw t0, -4(sp)\n");
		fprintf(f_asm,"        li t1, 0\n");
		fprintf(f_asm,"        beq t0, t1, EXIT%d\n", $1);
	}
	loop_stmt
	{
		$$ = 1;
		if( prag_tag == 1 ) printf("</stmt>");
		
		fprintf(f_asm,"        j WHILE%d\n", $1);
		fprintf(f_asm,"EXIT%d:\n", $1);
	}
	|
	DO
	{
		if( prag_tag == 1 )
			printf("<stmt>do");
		
		$1 = offset_count++;		
		fprintf(f_asm,"WHILE%d:\n", $1);
	} 
	loop_stmt
	WHILE '('
	{ if( prag_tag == 1 )
		printf("while("); }
	Expr
	')' ';'
	{
		if( prag_tag == 1 )
			printf(");</stmt>"); $$ = 1;
		
		fprintf(f_asm,"        lw t0, -4(sp)\n");
		fprintf(f_asm,"        li t1, 0\n");
		fprintf(f_asm,"        beq t0, t1, EXIT%d\n", $1);
		fprintf(f_asm,"        j WHILE%d\n", $1);
		fprintf(f_asm,"EXIT%d:\n", $1);
	}
     |	FOR '('
		{ if( prag_tag == 1 )
			printf("<stmt>for("); }
	Expr ';' { if( prag_tag == 1 ) printf(";"); }
	Expr ';' { if( prag_tag == 1 ) printf(";"); }
	Expr ')' { if( prag_tag == 1 ) printf(")"); }
	loop_stmt { $$ = 1; }
     |	RETURN		{ if( prag_tag == 1 ) printf("<stmt>return"); }
	return_option ';' { $$ = $3; if( prag_tag == 1 )
					printf("</stmt>"); }
     |  ';' { $$ = 0; }
     ;
C_Stmt : Stmt
       | '{' { printf("<stmt>{"); } Cmp_Stmt '}' { printf("}</stmt>"); }
       ;
if_option : %prec "then"	{ if( prag_tag == 1 )
	  				printf("</stmt>"); }
	  | ELSE C_Stmt		{ if( prag_tag == 1 )
					printf("</stmt>"); }
	  ;
switch_stmt : 
	    | CASE iVal ':' Sw_Stmt switch_stmt
	    | DEFAULT ':' Sw_Stmt switch_stmt
	    ;
Sw_Stmt :
	| BREAK ';' { if( prag_tag == 1 ) printf("<stmt>break;</stmt>"); }
	| Stmt Sw_Stmt
	;
loop_stmt : L_Stmt
	  | '{' loop_C '}'
	  ;
loop_C : L_Stmt loop_C
       |
       ;
L_Stmt : BREAK ';'
       | CONTINUE ';'
       | Stmt
       ;
return_option :		{ $$ = 0;	}
	      | Expr	{ $$ = $1;	}
		;

Expr :     	
     	E  { Expression = $1;
		$$ = $1->intVal;
		if( prag_tag == 1 )
			PrintTag(Expression); }
	|
	ID arr_option
	'='
	Expr
	{	
		TreeNode* idNode = (TreeNode*)malloc(sizeof(TreeNode));
		idNode->left = NULL; idNode->right = $2;
		strcpy(idNode->value, $1);
		idNode->Expr = 0; idNode->Print = 1;
		idNode->intVal = $4;		

		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = idNode; 
		temp->right = NULL; /*temp->right = $4;*/
		temp->value[0] = '=';
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = 1;
		
		Expression = temp;
		if( prag_tag == 1)
			PrintTag(Expression);

		$$ = 1;

		/*GetNode($1)->intVal = $4;*/
		
		fprintf(f_asm,"        sw t0, %d(s0)\n", GetNode($1)->offset*4*(-1)-8);//////////////////////////////
	}
	|
	ID PEQ
	{	
		fprintf(f_asm,"        lw t0, %d(s0)\n", GetNode($1)->offset*4*(-1)-8);
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}
	E
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        add t0, t0, t1\n");
		fprintf(f_asm,"        sw t0, %d(s0)\n", GetNode($1)->offset*4*(-1)-8);//////////////////////////////
		
		$$ = 1;
	}
	|
	ID MEQ
	{
		fprintf(f_asm,"        lw t0, %d(s0)\n", GetNode($1)->offset*4*(-1)-8);
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}
	E
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        sub t0, t1, t0\n");
		fprintf(f_asm,"        sw t0, %d(s0)\n", GetNode($1)->offset*4*(-1)-8);//////////////////////////////
		
		$$ = 1;
	}
	;
E :
	E OR 
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}	
	E
	{
	
		int _off = offset_count++;
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        beqz t1, ELSE%d\n", _off); //E1 = false
		fprintf(f_asm,"        li t0, 1\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"        j EXIT%d\n", _off);
		fprintf(f_asm,"        beqz t0, ELSE%d\n", _off); //E2 = false
		fprintf(f_asm,"        li t0, 1\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"        j EXIT%d\n", _off);
		fprintf(f_asm,"ELSE%d:\n", _off);
		fprintf(f_asm,"        li t0, 0\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"EXIT%d:\n", _off);
		
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '|';
		temp->value[1] = '|';
		temp->right = $4;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = (temp->left->intVal || temp->right->intVal);
		$$ = temp;
	}
  	|
	E AND
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}	
	E
	{
		int _off = offset_count++;
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        beqz t1, ELSE%d\n", _off); //E1 = false
		fprintf(f_asm,"        beqz t0, ELSE%d\n", _off); //E2 = false
		fprintf(f_asm,"        li t0, 1\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"        j EXIT%d\n", _off);
		fprintf(f_asm,"ELSE%d:\n", _off);
		fprintf(f_asm,"        li t0, 0\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"EXIT%d:\n", _off);
	
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '&';
		temp->value[1] = '&';
		temp->right = $4;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = (temp->left->intVal && temp->right->intVal);
		$$ = temp;
	}
  	|
	E BOR E
	{
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '|';
		temp->right = $3;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = (temp->left->intVal | temp->right->intVal);
		$$ = temp;
	}
  	|
	E BAND E
	{
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '&';
		temp->right = $3;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = (temp->left->intVal & temp->right->intVal);
		$$ = temp;
	}
  	|
  	E EQ 
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}
	E
	{
		int _off = offset_count++;
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        bne t0, t1, ELSE%d\n", _off);
		fprintf(f_asm,"        li t0, 1\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"        j EXIT%d\n", _off);
		fprintf(f_asm,"ELSE%d:\n", _off);
		fprintf(f_asm,"        li t0, 0\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"EXIT%d:\n", _off);
	
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '=';
		temp->value[1] = '=';
		temp->right = $4;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = (temp->left->intVal == temp->right->intVal);
		$$ = temp;
	}
  	|
	E NQ
	{	
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}
	E
	{
		int _off = offset_count++;
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        beq t0, t1, ELSE%d\n", _off);
		fprintf(f_asm,"        li t0, 1\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"        j EXIT%d\n", _off);
		fprintf(f_asm,"ELSE%d:\n", _off);
		fprintf(f_asm,"        li t0, 0\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"EXIT%d:\n", _off);
	
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '!';
		temp->value[1] = '=';
		temp->right = $4;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = (temp->left->intVal != temp->right->intVal);
		$$ = temp;
	}
	|
	E GQ
	{	
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}
	E
	{
		int _off = offset_count++;
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        blt t0, t1, ELSE%d\n", _off);
		fprintf(f_asm,"        li t0, 1\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"        j EXIT%d\n", _off);
		fprintf(f_asm,"ELSE%d:\n", _off);
		fprintf(f_asm,"        li t0, 0\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"EXIT%d:\n", _off);
	
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '<';
		temp->value[1] = '=';
		temp->right = $4;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = (temp->left->intVal <= temp->right->intVal);
		$$ = temp;
	}
	|
	E LQ 
	{	
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}
	E
	{
		int _off = offset_count++;
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        blt t1, t0, ELSE%d\n", _off);
		fprintf(f_asm,"        li t0, 1\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"        j EXIT%d\n", _off);
		fprintf(f_asm,"ELSE%d:\n", _off);
		fprintf(f_asm,"        li t0, 0\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"EXIT%d:\n", _off);
	
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '>';
		temp->value[1] = '=';
		temp->right = $4;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = (temp->left->intVal >= temp->right->intVal);
		$$ = temp;
	}
	|
	E GT
	{	
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}
	E
	{
		int _off = offset_count++;
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        bge t1, t0, ELSE%d\n", _off);
		fprintf(f_asm,"        li t0, 1\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"        j EXIT%d\n", _off);
		fprintf(f_asm,"ELSE%d:\n", _off);
		fprintf(f_asm,"        li t0, 0\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"EXIT%d:\n", _off);
		
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '>';
		temp->right = $4;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = (temp->left->intVal > temp->right->intVal);
		$$ = temp;
	}
	|
	E LT 
	{	
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}
	E
	{
		int _off = offset_count++;
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        bge t0, t1, ELSE%d\n", _off);
		fprintf(f_asm,"        li t0, 1\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"        j EXIT%d\n", _off);
		fprintf(f_asm,"ELSE%d:\n", _off);
		fprintf(f_asm,"        li t0, 0\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		fprintf(f_asm,"EXIT%d:\n", _off);
	
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '<';
		temp->right = $4;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = (temp->left->intVal < temp->right->intVal);
		$$ = temp;
	}
	|
	E '+'
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}
	E
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        add t0, t0, t1\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
	
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '+';
		temp->right = $4;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = temp->left->intVal + temp->right->intVal;
		$$ = temp;
	}
	| 
	E '-'
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}
	E
	{
	
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        sub t0, t1, t0\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '-';
		temp->right = $4;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = temp->left->intVal - temp->right->intVal;
		$$ = temp;
	}
     |   
	E '*'
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}
	E
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        mul t0, t0, t1\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
	
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '*';
		temp->right = $4;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = temp->left->intVal * temp->right->intVal;
		$$ = temp;
		} 
     | 	
	E '/'
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}	
	E
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        div t0, t1, t0\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
	
		if ($4 == 0)
			yyerror("zero division error");
			else
			{
				TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
				temp->left = $1;
				temp->value[0] = '/';
				temp->right = $4;
				temp->Expr = 1; temp->Print = 1;
				temp->intVal = temp->left->intVal / temp->right->intVal;
				$$ = temp;
			}
	}
	|
	E '%'
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
	}
	E
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        lw t1, 0(sp)\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        rem t0, t1, t0\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
	
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = $1;
		temp->value[0] = '%';
		temp->right = $4;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = temp->left->intVal % temp->right->intVal;
		$$ = temp;
		} 
    | 
	'-' E %prec UMINUS
	{
		fprintf(f_asm,"        addi sp, sp, -4\n");
		fprintf(f_asm,"        lw t0, 0(sp)\n");
		fprintf(f_asm,"        li t1, -1\n");
		fprintf(f_asm,"        mul t0, t0, t1\n");
		fprintf(f_asm,"        addi sp, sp, 4\n");
		fprintf(f_asm,"        sw t0, -4(sp)\n");
	
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = NULL;
		temp->value[0] = '\0';
		temp->right = NULL;
		temp->Expr = 1; temp->Print = 2;
		temp->intVal = -($2->intVal);
		$$ = temp;
	}
    | 
	'!' E %prec NOT
	{
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = NULL;
		temp->value[0] = '!';
		temp->right = NULL;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = !($2->intVal);
		$$ = temp;
	}
    | 
	'(' E ')'
	{
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = NULL;
		temp->value[0] = '(';
		temp->right = $2;
		temp->Expr = 1; temp->Print = 1;
		temp->intVal = $2->intVal;
		$$ = temp;
	}
    |
	 iVal
	{	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = NULL;
		temp->value[0] = '\0';
		temp->right = NULL;
		temp->Expr = 1; temp->Print = 2;
		temp->intVal = $1;
		$$ = temp;
		
		fprintf(f_asm,"        li t0, %d\n", $1);
		fprintf(f_asm,"        sw t0, -4(sp)\n");
	}
    | 
	ID
	{ 
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = NULL;
		strcpy(temp->value, $1);
		temp->right = NULL;
		temp->Expr = 1; temp->Print = 1;
		/*temp->intVal = GetValue($1);*/
		temp->intVal = 0;
		$$ = temp;
		
		/*fprintf(f_asm,"        lw t0, %d(fp) \n",GetNode($1)->offset*4*(-1)-16);*/
		fprintf(f_asm,"        lw t0, %d(s0)\n", GetNode($1)->offset*4*(-1)-8);///////////////////////////////
		fprintf(f_asm,"        sw t0, -4(sp)\n");
	}
	|
	ID '[' E ']' arr_option
	{
		TreeNode* per = (TreeNode*)malloc(sizeof(TreeNode));
		per->left = $3;
		per->value[0] = '[';
		per->right = $5;
		per->Expr = 0; per->Print = 0;
		
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = NULL;
		strcpy(temp->value, $1);
		temp->right = per;
		/*temp->intVal = GetValue($1);*/
		temp->intVal = 0;
		temp->Expr = 1; temp->Print = 1;
		$$ = temp;
	}
	|
	ID '(' 
	{
		
	}
		para_call ')'
	{
		fprintf(f_asm, "        sw ra, -4(sp)\n");
		fprintf(f_asm, "        addi sp, sp, -4\n");
		fprintf(f_asm, "        jal ra, %s\n", $1);
		fprintf(f_asm, "        lw ra, 0(sp)\n");
		fprintf(f_asm, "        addi sp, sp, 4\n");
		para_num = 0;
		TreeNode* per = (TreeNode*)malloc(sizeof(TreeNode));
		per->Expr = 0; per->Print = 0;
		per->left = $4;
		per->value[0] = '(';
		per->right = NULL;
		
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = NULL;
		strcpy(temp->value, $1);
		temp->right = per;
		/*temp->intVal = GetValue($1);*/
		temp->intVal = 0;
		temp->Expr = 1; temp->Print = 1;
		$$ = temp;
	}
	| INC ID
	{
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = NULL;
		strcpy(temp->value, "++");
		strcat(temp->value, $2);
		temp->right = NULL;
		/*temp->intVal = GetValue($2) + 1;*/
		temp->intVal = 1;
		temp->Expr = 1; temp->Print = 1;
		$$ = temp;
		
		fprintf(f_asm,"        lw t0, %d(s0)\n", GetNode($2)->offset*4*(-1)-8);///////////////////////////////
		fprintf(f_asm,"        addi t0, t0, 1\n");
		fprintf(f_asm,"        sw t0, %d(s0)\n", GetNode($2)->offset*4*(-1)-8);///////////////////////////////
		fprintf(f_asm,"        sw t0, -4(sp)\n");
	}
	| DEC ID
	{
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = NULL;
		strcpy(temp->value, "--");
		strcat(temp->value, $2);
		temp->right = NULL;
		/*temp->intVal = GetValue($2) - 1;*/
		temp->intVal = -1;
		temp->Expr = 1; temp->Print = 1;
		$$ = temp;
		
		fprintf(f_asm,"        lw t0, %d(s0)\n", GetNode($2)->offset*4*(-1)-8);///////////////////////////////
		fprintf(f_asm,"        addi t0, t0, -1\n");
		fprintf(f_asm,"        sw t0, %d(s0)\n", GetNode($2)->offset*4*(-1)-8);///////////////////////////////
		fprintf(f_asm,"        sw t0, -4(sp)\n");
	}
	| ID INC
	{
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = NULL;
		strcpy(temp->value, $1);
		strcat(temp->value, "++");
		temp->right = NULL;
		temp->Expr = 1; temp->Print = 1;
		$$ = temp;
		/*temp->intVal = GetValue($1) + 1;*/
		temp->intVal = 1;		
				
		fprintf(f_asm,"        lw t0, %d(s0)\n", GetNode($1)->offset*4*(-1)-8);///////////////////////////////
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		
		fprintf(f_asm,"        lw t1, %d(s0)\n", GetNode($1)->offset*4*(-1)-8);///////////////////////////////
		fprintf(f_asm,"        addi t1, t1, 1\n");
		fprintf(f_asm,"        sw t1, %d(s0)\n", GetNode($1)->offset*4*(-1)-8);///////////////////////////////
	}
	| ID DEC
	{
		TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = NULL;
		strcpy(temp->value, $1);
		strcat(temp->value, "--");
		temp->right = NULL;
		temp->Expr = 1; temp->Print = 1;
		$$ = temp;
		/*temp->intVal = GetValue($1) - 1;*/
		temp->intVal = -1;
		
		fprintf(f_asm,"        lw t0, %d(s0)\n", GetNode($1)->offset*4*(-1)-8);///////////////////////////////
		fprintf(f_asm,"        sw t0, -4(sp)\n");
		
		fprintf(f_asm,"        lw t1, %d(s0)\n", GetNode($1)->offset*4*(-1)-8);///////////////////////////////
		fprintf(f_asm,"        addi t1, t1, -1\n");
		fprintf(f_asm,"        sw t1, %d(s0)\n", GetNode($1)->offset*4*(-1)-8);///////////////////////////////
	}
	;
arr_option : { $$ = NULL; }
		|	'[' E ']' arr_option
		{
			TreeNode* per = (TreeNode*)malloc(sizeof(TreeNode));
			per->left = $2;
			per->value[0] = '[';
			per->right = $4;
			per->Expr = 0; per->Print = 0;
		
			$$ = per;
		}
    ;
para_call :	{ $$ = NULL; }
		| E
		{
			fprintf(f_asm, "        lw a%d, -4(sp)\n", para_num++);//////////////////////////////////////
		} 
		para_call_option
		{
			TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
			temp->left = $1;
			temp->value[0] = '\0';
			temp->right = $3;
			/*temp->intVal = GetValue($1);*/
			temp->intVal = 0;
			temp->Expr = 0; temp->Print = 0;
			$$ = temp;
		}
		;
para_call_option: { $$ = NULL; }
		| ',' E
		{
			fprintf(f_asm, "        lw a%d, -4(sp)\n", para_num++);
		}
		para_call_option
		{
			TreeNode* comma = (TreeNode*)malloc(sizeof(TreeNode));
			comma->left = NULL;
			comma->value[0] = ',';
			comma->right = $4;
			comma->intVal = 0;
			comma->Expr = 0; comma->Print = 1;
			
			TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
			temp->left = $2;
			temp->value[0] = '\0';
			temp->right = comma;
			/*temp->intVal = GetValue($1);*/
			temp->intVal = 0;
			temp->Expr = 0; temp->Print = 0;
			$$ = temp;
		}
		;

Decl :	type
	ID
        {
			type = $1;
			if( prag_parse == 1 )
				printf("Line %d - declare ", lineNo);
			if( prag_tag == 1 )
			{
				printf("<scalar_decl>");
				PrintType(type);			
				printf("%s", $2);
			}
			if( prag_parse == 1 )
				printf("%s ", $2);
				
			Insert(type, $2, lineNo);
			IDENT = GetNode($2);
			
			fprintf(f_asm,"// declare %s at %d(s0) \n", $2 , GetNode($2)->offset*4*(-1)-8);
	}
	assign_option
	{
		/*IDENT->intVal = $4;*/
	}
	decl_option
	';'			{ if( prag_tag == 1 )
					printf(";</scalar_decl>");	}
	|
	CONST
	type
	ID
	'='
	{	type = $2;	
		if( prag_tag == 1 )
		{
			printf("<const_decl>const");
			PrintType(type);
			printf("%s=", $3);
		}
	}
	Expr
	';'	{ if( prag_tag == 1 )
			printf(";</const_decl>"); }
	|	
	type
	ID '[' 
	{
	type = $1;
		if( prag_parse == 1 )
			printf("Line %d - declare ", lineNo);
		if( prag_tag == 1 )
		{
			printf("<arr_decl>");
			PrintType(type);
		}
	}
	iVal ']'
		{ printf("%s[%d]", $2, $5); }
	arr_dem_option
	arr_assign_option
	arr_decl_option
	';'			{ printf(";</array_decl>");	}
      |
 	  type ID '(' parameter ')' ';'
	{
		type = $1;
		if( prag_parse == 1 )
			printf("Line %d - declare ", lineNo);
		if( prag_tag == 1 )
			printf("<func_decl>");	
		PrintType(type); printf("%s(", $2);
		PrintParameter(parameter); printf(");</func_decl>");
		
		/*if (global)*/
		fprintf(f_asm, ".global ");
		fprintf(f_asm, "%s\n", $2);
	}
	|
	type ID '(' parameter ')' '{'
	{
		type = $1;
		if( prag_parse == 1 )
			printf("Line %d - declare ", lineNo);
		if( prag_tag == 1 )
			printf("<func_def>");	
		PrintType(type); printf("%s(", $2);
		PrintParameter(parameter); printf("){");
		
		fprintf(f_asm, "%s:\n", $2);
		fprintf(f_asm, "// BEGIN PROLOGUE\n");
		fprintf(f_asm, "	sw s0, -4(sp) // save frame pointer\n");
		fprintf(f_asm, "	addi sp, sp, -4\n");
		fprintf(f_asm, "	addi s0, sp, 0 // set new frame\n");
		fprintf(f_asm, "	sw sp, -4(s0)\n");
		fprintf(f_asm, "	sw s1, -8(s0)\n");
		fprintf(f_asm, "	sw s2, -12(s0)\n");
		fprintf(f_asm, "	sw s3, -16(s0)\n");
		fprintf(f_asm, "	sw s4, -20(s0)\n");
		fprintf(f_asm, "	sw s5, -24(s0)\n");
		fprintf(f_asm, "	sw s6, -28(s0)\n");
		fprintf(f_asm, "	sw s7, -32(s0)\n");
		fprintf(f_asm, "	sw s8, -36(s0)\n");
		fprintf(f_asm, "	sw s9, -40(s0)\n");
		fprintf(f_asm, "	sw s10, -44(s0)\n");
		fprintf(f_asm, "	sw s11, -48(s0)\n");
		fprintf(f_asm, "	addi sp, s0, -48 // update stack pointer\n");
		fprintf(f_asm, "// END PROLOGUE\n");
	}
	Cmp_Stmt '}'
				{ if( prag_tag == 1 )
				printf("}</func_def>"); 
				
				fprintf(f_asm, "// BEGIN EPILOGUE\n");
				fprintf(f_asm, "	lw s11, -48(s0)\n");
				fprintf(f_asm, "	lw s10, -44(s0)\n");
				fprintf(f_asm, "	lw s9, -40(s0)\n");
				fprintf(f_asm, "	lw s8, -36(s0)\n");
				fprintf(f_asm, "	lw s7, -32(s0)\n");
				fprintf(f_asm, "	lw s6, -28(s0)\n");
				fprintf(f_asm, "	lw s5, -24(s0)\n");
				fprintf(f_asm, "	lw s4, -20(s0)\n");
				fprintf(f_asm, "	lw s3, -16(s0)\n");
				fprintf(f_asm, "	lw s2, -12(s0)\n");
				fprintf(f_asm, "	lw s1, -8(s0)\n");
				fprintf(f_asm, "	lw sp, -4(s0)\n");
				fprintf(f_asm, "	addi sp, sp, 4\n");
				fprintf(f_asm, "	lw s0, -4(sp)\n");
				fprintf(f_asm, "// END EPILOGUE\n");
				fprintf(f_asm, "\n");
				fprintf(f_asm, "	jalr zero, 0(ra) // return\n");
  }
      ;
assign_option :		 { $$ = 0; }
	      | '='	{ 
			if( prag_parse == 1 )
				printf("assign ");
			if( prag_tag == 1 )
				printf("="); }
		Expr
			{	
				fprintf(f_asm, "	addi sp, sp, -4\n");
				fprintf(f_asm, "	lw t0, 0(sp)\n");
				fprintf(f_asm, "	sw t0, %d(s0)\n", IDENT->offset*4*(-1) - 8);//////////////////////////
				fprintf(f_asm, "	addi sp, sp, 4\n");			
				$$ = $3;
			}
	      ;
arr_assign_option : {;}
		  | '=' '{'
			{ if( prag_tag == 1 )
				printf("={"); }
			Expr
			{ if( prag_tag == 1 )
				printf("<Expr>%d</Expr>", $4); } 
			arr_val_option
			'}'
			{ if( prag_tag == 1 )
				printf("}"); }
		  ;
arr_val_option : {;}
	       | ',' Expr
			{ if( prag_tag == 1 )
		 		printf(",<Expr>%d</Expr>", $2); } 
		 arr_val_option
	       ;
decl_option : {;}
	    | ',' 
		{ if( prag_parse == 1 ) printf(", "); 
		  if( prag_tag == 1) printf(",");	}
		ID
		{
			if( prag_tag == 1 )
				printf("%s", $3);
			/*Insert(type, $3, lineNo);
			IDENT = GetNode($3);*/
		}
		assign_option
		{
			/*IDENT->intVal = $5;*/
		}
		decl_option	
	    ;
arr_dem_option :
	       | '[' iVal ']'	{ if( prag_tag == 1 )
					printf("[%d]", $2); }
		 arr_dem_option
	       ;
arr_decl_option : {;}
		|
		','
		ID '[' iVal ']'
		{
			if( prag_tag == 1)
				printf(",%s[%d]", $2, $4);
		}
		arr_dem_option
		arr_assign_option
		arr_decl_option
		;
parameter :	{ $$ = NULL; parameter = NULL; }
	  | type ID para_option
		{
			Parameter* temp = (Parameter*)malloc(sizeof(Parameter));
			temp->type = $1;
			strcpy(temp->name, $2);
			temp->next = $3;
			$$ = temp;
			parameter = temp;
		}
	  ;
para_option : {	$$ = NULL; }
	    | ',' type ID para_option
		{
			Parameter* temp = (Parameter*)malloc(sizeof(Parameter));
			temp->type = $2;
			strcpy(temp->name, $3);
			temp->next = $4;
			$$ = temp;
		}
	    ;

type : VOID	{ $$ = 0; }
     | INT	{ $$ = INT_TYPE;	}
     | DOUBLE   { $$ = DOUBLE_TYPE; 	}
     | CHAR	{ $$ = CHAR_TYPE;	}
     | FLOAT	{ $$ = FLOAT_TYPE;	}
     ;

%%

/*int main()
{	
	prag_source = 0;
	prag_token = 0;
	prag_parse = 0;
	prag_tag = 1;
	
	Table = (Node*)malloc(sizeof(Node));
	Table->next = NULL;

	IDENT = (Node*)malloc(sizeof(Node));

	Expression = (TreeNode*)malloc(sizeof(TreeNode));
	parameter = (Parameter*)malloc(sizeof(Parameter));

	yyparse();

}*/
void main(int argc, char **argv)
{
	int i;

	--argc; ++argv;
	lineNo = 0;
	prag_source = 0;
	prag_token = 0;
	prag_parse = 0;
	prag_tag = 1;
	
	Table = (Node*)malloc(sizeof(Node));
	Table->next = NULL;

	IDENT = (Node*)malloc(sizeof(Node));

	Expression = (TreeNode*)malloc(sizeof(TreeNode));
	parameter = (Parameter*)malloc(sizeof(Parameter));
	
	if (argc > 0) 
		yyin=fopen(argv[0], "r");
	else 
		yyin=stdin;

	if ((f_asm = fopen("codegen.S", "w")) == NULL) {
		fprintf(stderr, "Cant open the file %s for write\n", "codegen.S");
		exit(1);
	}

	//init_symbol_table();
	//code_gen_with_header(argv[0]);
	if (i = yyparse()) {
		fprintf(stderr,"Bad parse, return code %d\n", i);
	}
	else
		fprintf(stdout,"\nParsing Successfully\n");

	//code_gen_global_vars();
}
void yyerror(char* msg)
{
	fprintf(stderr, "Error at Line %d", lineNo);
	exit(1);
}
