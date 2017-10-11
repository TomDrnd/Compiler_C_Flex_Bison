%{
#include"CommonFunctions.h"
#include"bisLogo.tab.h"
%}
%%
[1-9][0-9]*|0	yylval.INT=atoi(yytext); return TNUMBER;
FORWARD		return TFORWARD;
RIGHT		return TRIGHT; 
LEFT		return TLEFT;
REPEAT		return TREPEAT;
HEXAGONE	return THEXAGONE;
RED		return TRED;
GREEN		return TGREEN;
BLUE		return TBLUE;
BLACK		return TBLACK;
YELLOW		return TYELLOW;
WHITE		return TWHITE;
"["		return TBEGIN;
"]"		return TEND;
\n
%%
