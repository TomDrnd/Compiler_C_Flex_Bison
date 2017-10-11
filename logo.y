%{
#include<stdio.h>
#include<string.h>
#include"IntermediateLanguage.h"

PROGRAM ProgAll;

void yyerror(const char *str)
{
	fprintf(stderr, "error: %s\n", str);
}

int yywrap()
{
	return 1;
}


%}

%token TNUMBER
%token TFORWARD
%token TRIGHT
%token TLEFT
%token TREPEAT
%token TBEGIN
%token TEND

%union {
	PROGRAM INSTR;
	int INT;
};

%type <INT> TNUMBER;
%type <INSTR> PROG INST;

%%


PROG : INST
	{$$=$1;
	ProgAll=$$}
	| PROG INST
	{addAtEnd (&$1, $2);
	$$=$1;
	ProgAll=$$}

INST : TFORWARD TNUMBER
	{*$$=createInstruction(1, $2, NULL, NULL);}
	| TLEFT TNUMBER
	{*$$=createInstruction(2, $2, NULL, NULL);}
	| TRIGHT TNUMBER
	{*$$=createInstruction(3, $2, NULL, NULL);} 
	|TREPEAT TNUMBER TBEGIN PROG TEND
	{*$$=createInstruction(4, $2, NULL, NULL);
	addAtEndOfRepeat ($$, $4);}
	 
%%

int main(){

	printf("on est avant le yyparse\n");
	yyparse();
	printf("on est après le yyparse\n");
	displayProgram (ProgAll);	
	return 0;

}
