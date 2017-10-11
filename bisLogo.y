%{
#include"CommonFunctions.h"

PROGRAM ProgAll;//Pointer to the first INSTRUCTION of the PROGRAM

/*---------------------------------------
  Funtion that is used when the bison detects a syntax error that displays the fprintf message on the standard output
  ----------------------------------------*/

void yyerror(const char *str)
{
	fprintf(stderr, "error: %s\n", str);
	//I added this exit(); after the presentation because it was one of my mistake to not quit the program if there was a syntax error
	exit(1);
}

/*---------------------------------------
  Funtion called at the end of the file
  ----------------------------------------*/

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
%token THEXAGONE
%token TGREEN
%token TRED
%token TWHITE
%token TBLACK
%token TYELLOW
%token TBLUE
%token TBEGIN
%token TEND

%union {
	PROGRAM INSTR;
	int INT;
	char COLO[10];
};

%type <COLO> COLOR;
%type <INT> TNUMBER;
%type <INSTR> PROG INST;

%%

PROG : INST
{$$=$1;
	ProgAll=$$;}
	| PROG INST
	{addAtEnd (&$1, $2);
	$$=$1;
	ProgAll=$$;}

INST : TFORWARD TNUMBER 
	{$$=createInstruction(1, $2, NULL, NULL, "0");}
	| TFORWARD COLOR TNUMBER
	{$$=createInstruction(1, $3, NULL, NULL, $2);}
	| TLEFT TNUMBER
	{$$=createInstruction(2, $2, NULL, NULL, "0");}
	| TRIGHT TNUMBER
	{$$=createInstruction(3, $2, NULL, NULL, "0");} 
	| TREPEAT TNUMBER TBEGIN PROG TEND
	{$$=createInstruction(4, $2, NULL, NULL, "0");
	addAtEndOfRepeat ($$, $4);}
	| THEXAGONE COLOR TNUMBER 
	{$$=createInstruction(4, 6, NULL, createInstruction(1, $3, createInstruction(3, 60, NULL, NULL, "0"), NULL, $2), "0");}

COLOR : TGREEN
	{strcpy($$, "green");}
	| TBLACK
	{strcpy($$, "black");}
	| TWHITE
	{strcpy($$, "white");}
	| TYELLOW
	{strcpy($$, "yellow");}
	| TRED
	{strcpy($$, "red");}
	| TBLUE
	{strcpy($$, "blue");}

%%

int main(int argc, char *argv[]){

	POINT startingPoint=(POINT)malloc(sizeof(POINT));//starting point of the logo on the window
	startingPoint->x=500;
	startingPoint->y=500;
	startingPoint->angle=0;
	yyparse();

	system("clear");
	displayProgram (ProgAll, 0);
	
	//dimensions of the svg's window
	int width=1000;
	int height=1000;

	if(argc==3){
		startingPoint->x=atoi(argv[1]);
		startingPoint->y=atoi(argv[2]);
	}
	if(argc==5){
		width=atoi(argv[1]);
		height=atoi(argv[2]);
		startingPoint->x=atoi(argv[3]);
		startingPoint->y=atoi(argv[4]);
	}

	writtingOfTheSVGFile(ProgAll, startingPoint, width, height);
	freeProgram(ProgAll);
	free(startingPoint);
	
	system("open -a /Applications/Safari.app logo.svg");//used on the macOS to open the svg automatically

	return 0;

}
