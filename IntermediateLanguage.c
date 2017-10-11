#include"CommonFunctions.h"

/*---------------------------------------
  Constructor of the structure INSTRUCTION, return a pointer to this INSTRUCTION
  //Parameters 
  //int tp : type of the instruction (1 for FORWARD, 2 for LEFT, ...)
  //int val : value of the instruction, number of repetition for the REPEAT one, angle in degree for LEFT and RIGHT and size of the line for FORWARD
  //INTRUCTION * nxt : link to to next INSTRUCTION in the program
  //INTRUCTION * subprog : link to to subprogram for a REPEAT instruction
  //char* clr : colour for the FORWARD instruction
  ----------------------------------------*/

INSTRUCTION* createInstruction (int tp, int val, INSTRUCTION * nxt, INSTRUCTION * subprog, char *clr){

	INSTRUCTION* instr=(PROGRAM)malloc(sizeof(INSTRUCTION));
	instr->type=tp;
	instr->value=val;
	instr->next=nxt;
	instr->subprogram=subprog;
	strcpy(instr->color,clr);
	return instr;

}

/*---------------------------------------
  Adds at the end of the PROGRAM a new INSTRUCTION given as parameter
  //Parameters 
  //PROGRAM * logo : pointer to the program. The program points to the first INSTRUCTION.
  //INTRUCTION * instr : pointer to the INSTRUCTION to add
  ----------------------------------------*/

void addAtEnd (PROGRAM* logo, INSTRUCTION * instr){

	if(*logo==NULL)	*logo=instr;
	else	addAtEnd(&((*logo)->next), instr);

}

/*---------------------------------------
  Adds at the end of the subprogram (in the case of a REPEAT) a new INSTRUCTION given as parameter
  //Parameters 
  //INTRUCTION * repeat : pointer to the REPEAT to which we want to add at the end of the subprogam the INSTRUCTION
  //INTRUCTION * instr : pointer to the INSTRUCTION to add
  ----------------------------------------*/

void addAtEndOfRepeat (INSTRUCTION * repeat, INSTRUCTION * instr){

	if(repeat->subprogram==NULL)	repeat->subprogram=instr;
	else	addAtEnd(&(repeat->subprogram->next), instr);

}

/*---------------------------------------
  Frees the memory allocated for all the INSTRUCTIONS (with a malloc in the constructor)
  //Parameters 
  //PROGRAM logo : pointer to the first INSTRUCTION of the PROGRAM
  ----------------------------------------*/

void freeProgram (PROGRAM logo){

	if(logo->subprogram!=NULL)
		freeProgram(logo->subprogram);
	if(logo->next!=NULL)
		freeProgram(logo->next);
	//printf("Value of the freed instruction : %d\n", logo->value); //just to see all the instructions that are freed as a control even if we can see it with valgrind
	free(logo);

}

/*---------------------------------------
  Displays the program on the standard output by going through the chained instructions
  //Parameters 
  //PROGRAM logo : pointer to the first INSTRUCTION to display
  //int i : a value that is used to make the indentation of the display
  ----------------------------------------*/

void displayProgram (PROGRAM logo, int i){
	if(logo!=NULL){
		int j=i;	
		while(i>0){
			printf("	");
			i--;
		}
		if(logo->type==1){
			printf("FORWARD %d %s\n", logo->value, logo->color);
			displayProgram(logo->next, j);
		}else if(logo->type==2){
			printf("LEFT %d\n", logo->value);
			displayProgram(logo->next, j);
		}else if(logo->type==3){
			printf("RIGHT %d\n", logo->value);
			displayProgram(logo->next, j);
		}else{
			printf("REPEAT %d [\n", logo->value);
			displayProgram(logo->subprogram, j+1);
			i=j;
			while(i>0){
				printf("	");
				i--;
			}
			printf("]\n");
			displayProgram(logo->next, j);
		}
	}

}
