#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//structure of the types INSTRUCTION and PROGRAM used to build the program
struct model_elem {

	int type, value;
	char color[10];
	struct model_elem *next, *subprogram;

};
typedef struct model_elem INSTRUCTION;
typedef INSTRUCTION* PROGRAM;

INSTRUCTION* createInstruction (int, int, INSTRUCTION *, INSTRUCTION *, char *);
void addAtEnd (PROGRAM* , INSTRUCTION *);
void addAtEndOfRepeat (INSTRUCTION *, INSTRUCTION *);
void displayProgram (PROGRAM, int);
void freeProgram(PROGRAM);

//structure of the type POINT used to update the position in the svg file
struct model_elem2 {

	double x;
	double y;
	double angle;

};
typedef struct model_elem2* POINT;

void obligatoryLines(FILE*, int, int);
void IntermediateLanguageToSVG(PROGRAM, FILE*, POINT);
double conversionDegToRad(int);
void forwardTreatment(FILE*, POINT, PROGRAM);
void leftTreatment(POINT, PROGRAM);
void rightTreatment(POINT, PROGRAM);
void writtingOfTheSVGFile(PROGRAM, POINT, int, int);

#endif
