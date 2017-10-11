#include"CommonFunctions.h"
#include<math.h>

/*---------------------------------------
  Writes the first obligatory lines for a svg file in the svg file
  //Parameters 
  //FILE * file : pointer to the file in which the lines will be written
  //int width : width of the svg's window
  //int height : height of the svg's window
  ----------------------------------------*/

void obligatoryLines(FILE * file, int width, int height){
	fprintf(file, "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\n<svg width=\"%d\" height=\"%d\" version=\"1.1\"\nxmlns=\"http://www.w3.org/2000/svg\">\n<title>TP LOGO</title>\n\n", width, height);

}

/*---------------------------------------
  Writes in the svg file the lines corresponding to the instructions
  //Parameters 
  //PROGRAM prog : pointer to the first INSTRUCTION of the PROGRAM
  //FILE * file : pointer to the file in which the lines will be wiritten
  //POINT beginning : contains the angle and the coordinates of the starting point
  ----------------------------------------*/

void IntermediateLanguageToSVG(PROGRAM prog, FILE* file, POINT beginning){
	int i;
	if(prog!=NULL){
		if(prog->type==1){ //FORWARD
			forwardTreatment(file, beginning, prog);
			IntermediateLanguageToSVG(prog->next, file, beginning);
		}else if(prog->type==2){ //LEFT
			leftTreatment(beginning, prog);
			IntermediateLanguageToSVG(prog->next, file, beginning);
		}else if(prog->type==3){ //RIGHT
			rightTreatment(beginning, prog);
			IntermediateLanguageToSVG(prog->next, file, beginning);
		}else{ //REPEAT
			for(i=0; i<prog->value; i++){
				IntermediateLanguageToSVG(prog->subprogram, file, beginning);
			}
			IntermediateLanguageToSVG(prog->next, file, beginning);
		}
	}

}

/*---------------------------------------
  Converts an angle in degree to an angle in radian to use the cosinus and sinus functions
  //return the angle in radian
  //Parameters 
  //int angleDeg : value in degree of the angle to convert
  ----------------------------------------*/

double conversionDegToRad(int angleDeg){

	double angleRad=0;
	angleRad=angleDeg*M_PI/180;
	return angleRad;

}

/*---------------------------------------
  Writes in the svg file the lines corresponding to the instruction FORWARD and updates the position of the current point
  //Parameters 
  //PROGRAM prog : pointer to the INSTRUCTION corresponding to the line
  //FILE * file : pointer to the file in which the lines will be wiritten
  //POINT cur : contains the angle and the coordinates of the point at this moment
  ----------------------------------------*/

void forwardTreatment(FILE * file, POINT cur, PROGRAM prog){

	fprintf(file, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" \n\t style=\" fill:%s; stroke:%s\"/>\n", cur->x, cur->y, (cur->x)+=cos(cur->angle)*prog->value, (cur->y)-=sin(cur->angle)*prog->value, prog->color, prog->color);

}

/*---------------------------------------
  Updates the value of the angle in in radian according to the value of the INSTRUCTION given as parameter in degree
  //Parameters 
  //PROGRAM prog : pointer to the INSTRUCTION corresponding to the line
  //FILE * file : pointer to the file in which the lines will be wiritten
  //POINT cur : contains the angle and the coordinates of the point at this moment
  ----------------------------------------*/

void leftTreatment(POINT cur, PROGRAM prog){

	cur->angle+=conversionDegToRad(prog->value);

}

/*---------------------------------------
  Updates the value of the angle in in radian according to the value of the INSTRUCTION given as parameter in degree
  //Parameters 
  //PROGRAM prog : pointer to the INSTRUCTION corresponding to the line
  //FILE * file : pointer to the file in which the lines will be wiritten
  //POINT cur : contains the angle and the coordinates of the point at this moment
  ----------------------------------------*/

void rightTreatment(POINT cur, PROGRAM prog){

	cur->angle-=conversionDegToRad(prog->value);

}

/*---------------------------------------
  Writes in the svg file all the lines corresponding to the program
  //Parameters 
  //PROGRAM prog : pointer to the first INSTRUCTION of the PROGRAM
  //POINT beginning : contains the angle and the coordinates of the starting point
  //int width : width of the svg's window
  //int heigth : height of the svg's window
  ----------------------------------------*/
  
void writtingOfTheSVGFile(PROGRAM logo, POINT beginning, int width, int height){

	FILE* file = NULL;
	file=fopen("logo.svg", "w");//opening of the file
	if(file!=NULL){
		obligatoryLines(file, width , height);
		IntermediateLanguageToSVG(logo, file, beginning);
		fprintf(file, "\n\n</svg>");
		fclose(file);
	}else{
		printf("Error opening of the file\n");
		exit(0);
	}
}
