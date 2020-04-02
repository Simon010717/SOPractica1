CC = gcc
all: main.c ./SourceCode/general.c ./SourceCode/uno.c ./SourceCode/dos.c ./SourceCode/tres.c ./SourceCode/cuatro.c
	@ $(CC) -IHeaders main.c ./SourceCode/general.c ./SourceCode/uno.c ./SourceCode/dos.c ./SourceCode/tres.c ./SourceCode/cuatro.c -o main 