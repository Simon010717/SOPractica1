#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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
        *a = '\0';
    }
        
}
/*
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
        
        strcpy(PerroStruct.raza, Razas[rand()%9]);
        
        PerroStruct.sexo = Generos[rand()%2];
        PerroStruct.edad = Edades[rand()%9];
        PerroStruct.peso = Pesos[rand()%2];
        PerroStruct.estatura = Estaturas[rand()%8];

        printf("%s",PerroStruct.nombre);
        hash = hashf(PerroStruct.nombre,32);

        char* dir;
        dir = malloc(15);
        bzero(dir,15);
        char num[3];
        strcat(dir,"../hash/");
        
        sprintf(num,"%i",hash);
        
        strcat(dir,num);

        

        FILE *fp;
        fp = fopen(dir,"a");
        fseek(fp, 0L, SEEK_END);
        size = ftell(fp);
        
        fclose(fp);

        id = 1000*(int)(size/36)+hash;
        PerroStruct.id = id;
        

        fp = fopen(dir,"a");
        fwrite(&id,sizeof(int),1,fp);
        fwrite(&PerroStruct.nombre,32,1,fp);

        fclose(fp);
        
        fwrite(&PerroStruct, sizeof(struct petType), 1, file);  

    }
    printf("Creación de registro exitosa.");
    fclose(file);
    for(int i = 0; i < NAMES; i++){
        free(AllNames[i]);
    }
    
    return 0;



}*/

struct dogType{
   int id;
   char nombre[32];
   char tipo[32];
   int edad;
   char raza[16];
   int estatura;
   float peso;
   char sexo;
};

int hashf(char word[],int l){
    int m,h,i,x,p;                                      // Declaracion de enteros usados en la formula de calculo del codigo
    m = 1000;                                      // Declaracion de la cardinalidad de la tabla hash (valor maximo del codigo hash resultante)

    p = 1009;                                      // Valor primo p > m para el calculo del codigo hash
    x = 22;                                      // Valor 0 < x < 32 (longitud max.)para el calculo del cosigo hash 

    for(i=0;i<l;i++){                                      // Iteracion sobre los caracteres del arreglo
        word[i] = tolower(word[i]);                                      // Conversion a minuscula de los caracteres del arreglo
    }

    h = 1;                                      // Inicializacion del valor hash en 1. 
    for(i=0; i<l; i++){                                      // Iteracion sobre los caracteres del arreglo, pues la formula es una sumatoria de operaciones realizadas sobre los codigos ASCII de los caracteres
        h = (p + h*x+(int)word[i])%p;                                      // Suma del calculo sobre el caracter modulo p
    }

    return h%m;                                      // Retorna el valor del calculo (sumatoria) modulo m (cardinalidad de la tabla), este es el codigo hash resultante
}

int main(){
    FILE *names;
	char* AllNames[NAMES];

	names = fopen("nombres.txt", "r");
    if(names == NULL){
        perror("No se encontro el archivo de nombres.\n");
        exit(EXIT_FAILURE);
    }

    readFile(names,AllNames);
    fclose(names);

	char* Razas[] = {"Husky", "Labrador", "Pomerania", "Buldog", "Golden Retriever", "Pastor Aleman", "Pug", "Doberman", "Beagle"};
    char Generos[] = {'H', 'M'};
    int Edades[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    float Pesos[] = {5.5f, 10.2f, 15.7f, 20.0f, 25.7f, 30.3f};
    int Estaturas[] = {3, 4, 5, 6, 7, 8, 9, 10};

	for ( int i = 0; i < 10000000; i++ ){
		int r,pos,id,hash,size;                                                   
		int *tempid;                                                   

		struct dogType *data;                                                   
		data = malloc(sizeof(struct dogType));                                                   


		bzero(data->nombre,32);
		strcpy(data->nombre, AllNames[i%NAMES]);

		sprintf(data->tipo, "Perro");

		data->edad = Edades[i%15];

		sprintf(data->raza, "%s", Razas[i%9]);

		data->estatura = Estaturas[i%15];

		data->peso = Pesos[i%6];

		data->sexo = Generos[i%2];                                      

		hash = hashf(data->nombre,32);                                                   

		char* dir;                                      
		dir = malloc(15);                                       
		bzero(dir,15);                                      
		char num[3];                                      
		strcat(dir,"../hash/");                                      
		sprintf(num,"%i",hash);                                      
		strcat(dir,num);                                      


		FILE *fp;                                      
		fp = fopen(dir,"a");                                      
		size = ftell(fp);                                      
		fclose(fp);                                      

		id = 1000*(int)(size/36)+hash;                                      
		data->id = id;                                      

		fp = fopen(dir,"a");                                      
		fwrite(&id,sizeof(int),1,fp);                                      
		fwrite(data->nombre,32,1,fp);                                      

		fclose(fp);                                      

		fp = fopen("../dataDogs.dat","a");                                      

		r = fwrite(data,sizeof(struct dogType),1,fp);                                      

		fclose(fp);                                      

		free(data);                                      
		free(dir);                                                                           

	}

	return 0;
}