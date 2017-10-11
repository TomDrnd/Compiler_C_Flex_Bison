CC = gcc
CFLAGS = -g

all : exec logo

logo : lex.yy.c bisLogo.tab.c IntermediateLanguage.o logoSVG.o
	$(CC) lex.yy.c bisLogo.tab.c IntermediateLanguage.o logoSVG.o -o logo $(CFLAGS) -lm

bisLogo.tab.c : bisLogo.y
	bison -d bisLogo.y

lex.yy.c : flexLogo.l
	flex flexLogo.l

exec : testMain.o IntermediateLanguage.o
	$(CC) testMain.o IntermediateLanguage.o -o exec $(CFLAGS)

testMain.o : testMain.c
	$(CC) -c testMain.c -o testMain.o $(CFLAGS)

IntermediateProgramme.o : IntermediateLanguage.c
	$(CC) -c IntermediateLanguage.c -o IntermediateLanguage.o $(CFLAGS)

logoSVG.o : logoSVG.c
	$(CC) -c logoSVG.c -o logoSVG.o $(CFLAGS) -lm

clean : 
	rm -rf *.o

cleanAll : 
	rm -rf *.o
	rm bisLogo.tab.c lex.yy.c exec logo logo.svg
