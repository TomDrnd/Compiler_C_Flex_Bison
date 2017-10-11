#include"CommonFunctions.h"

int main(){

	INSTRUCTION *instr1, *instr2, *instr3, *instr4, *instr5, *instr6, *instr7;
	instr5 = createInstruction (1, 100, NULL, NULL, "RED");
	instr4 = createInstruction (2, 90, NULL, NULL, "GREEN");
	instr7 = createInstruction (3, 90, NULL, NULL, "BLUE");
	instr3 = createInstruction (1, 50, NULL, NULL, "0");
	instr2 = createInstruction (0, 4, NULL, NULL, "0");
	instr6 = createInstruction (0, 3, NULL, NULL, "0");
	instr1 = createInstruction (1, 100, NULL, NULL, "BLACK");
	PROGRAM logo = NULL;
		
	addAtEnd(&logo, instr1);
	addAtEnd(&logo, instr2);
	addAtEndOfRepeat(instr2, instr3);
	addAtEndOfRepeat(instr2, instr4);
	addAtEnd(&logo, instr5);
	addAtEndOfRepeat(instr2, instr6);
	addAtEndOfRepeat(instr6, instr7);
	displayProgram(logo, 0);
	freeProgram(logo);
	printf("free done\n");

}
