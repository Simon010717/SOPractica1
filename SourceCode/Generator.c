#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "general.h"
#include "uno.h"

#define SIZE 32
#define NAMES 1700

void readFile(FILE* file, char* AllNames[]){
    for(int j = 0; j < NAMES; j++){
        AllNames[j] = malloc(SIZE);
        int i = 0;
        char *a;
        do{
            a = AllNames[j]+i;
            fread(a,1,1,file);
            i++;
        }while(*a != '\n'  && i<SIZE);
    }
        
}

int main(int argc, char* argv[]){
    int hash, size, id;
    long NUMESTRUCTURAS;
    FILE *file, *names;
    char* AllNames[NAMES];

    NUMESTRUCTURAS = atoi(argv[1]);

    srand(time(NULL)); 

    char* Razas[] = {"Husky", "Labrador", "Pomerania", "Buldog", "Golden Retriever", "Pastor Aleman", "Pug", "Doberman", "Beagle"};
    char Generos[] = {'H', 'M'};
    int Edades[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    float Pesos[] = {5.5f, 10.2f, 15.7f, 20.0f, 25.7f, 30.3f};
    int Estaturas[] = {3, 4, 5, 6, 7, 8, 9, 10};

    file = fopen("../dataDogs.dat", "w+");
    names = fopen("nombres.txt", "r");
    if(names == NULL){
        perror("No se encontro el archivo de nombres.\n");
        exit(EXIT_FAILURE);
    }

    readFile(names,AllNames);
    fclose(names);

    struct petType PerroStruct;
    
    
    for(int i = 0; i < NUMESTRUCTURAS; i++){
        bzero(&PerroStruct, sizeof(struct petType));

        strcpy(PerroStruct.nombre, AllNames[rand()%NAMES]);
        //PerroStruct.nombre = AllNames[rand()%NAMES];
        strcpy(PerroStruct.raza, Razas[rand()%9]);
        //PerroStruct.raza = Razas[rand()%9];
        PerroStruct.sexo = Generos[rand()%2];
        PerroStruct.edad = Edades[rand()%9];
        PerroStruct.peso = Pesos[rand()%2];
        PerroStruct.estatura = Estaturas[rand()%8];

        hash = hashf(PerroStruct.nombre,sizeof(PerroStruct.nombre));

        char* dir;
        dir = malloc(15);
        bzero(dir,15);
        char num[3];
        strcat(dir,"../hash/");
        //printf("%s\n",dir);
        sprintf(num,"%i",hash);
        //printf("%s\n",num);
        strcat(dir,num);

        //printf("%s\n",dir);

        FILE *fp;
        fp = fopen(dir,"r");
        fseek(fp, 0L, SEEK_END);
        size = ftell(fp);
        //printf("size %i\n",size);
        fclose(fp);

        id = 1000*(int)(size/36)+hash;
        PerroStruct.id = id;
        //printf("id %i\n",id);

        fp = fopen(dir,"a");
        fwrite(&id,sizeof(int),1,fp);
        fwrite(&PerroStruct.nombre,32,1,fp);

        fclose(fp);
        //agregar a tabla hash
        fwrite(&PerroStruct, sizeof(struct petType), 1, file);  

    }
    printf("Creación de registro exitosa.");
    fclose(file);
    for(int i = 0; i < NAMES; i++){
        free(AllNames[i]);
    }
    
    return 0;



}