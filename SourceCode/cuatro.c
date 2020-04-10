#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include "general.h"

int buscarRegistro(){
    int hash,size,fs,tid,l,i;
    char tnombre[32];
    char nombre[32];
    bzero(tnombre,32); bzero(nombre,32);
    printw("Ingrese nombre a buscar: ");
    scanw("%s",nombre);

    for(i=0;i<32;i++){nombre[i] = tolower(nombre[i]);}

    hash = hashf(nombre,32);
    printw("hash %i\n",hash);

    char* dir;
    dir = malloc(15);
    bzero(dir,15);
    char num[3];
    strcat(dir,"./hash/");
    sprintf(num,"%i",hash);
    strcat(dir,num);

    FILE *fp;
    fp = fopen(dir,"a");
    fseek(fp, 0L, SEEK_END);
    size = (int)(ftell(fp)/36);
    printw("size %i\n",size);
    fclose(fp);

    fp = fopen(dir,"r");
    printw("ID de registros con nombre \"%s\":\n",nombre);
    while(ftell(fp)<(size*36)){
        fread(&tid,4,1,fp);
        fread(tnombre,32,1,fp);
        for(i=0;i<32;i++){tnombre[i] = tolower(tnombre[i]);}
        if(strcmp(nombre,tnombre) == 0){
            printw("   - %i\n",tid);    
            fs++;
        }
        fseek(fp,36-sizeof(int)-32,SEEK_CUR);
    }

    return 0;
}