codegen : y.tab.c lex.yy.c SymbolTable.h
	gcc -o codegen lex.yy.c y.tab.c SymbolTable.h -lfl

y.tab.c : parser.y
	yacc -d parser.y

y.tab.h : parser.y
	yacc -d parser.y

lex.yy.c : scanner.l
	flex scanner.l
