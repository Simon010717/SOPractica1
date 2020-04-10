CC = gcc
all: p1-dogProgram.c ./SourceCode/general.c ./SourceCode/uno.c ./SourceCode/dos.c ./SourceCode/tres.c ./SourceCode/cuatro.c
	@ $(CC) -IHeaders p1-dogProgram.c ./SourceCode/general.c ./SourceCode/uno.c ./SourceCode/dos.c ./SourceCode/tres.c ./SourceCode/cuatro.c -o p1-dogProgram -lncurses