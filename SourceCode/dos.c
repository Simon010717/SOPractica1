#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "general.h"

int verificacion(int id){
    FILE* fp;

    int f, tid, hash, size;

    hash = id % 1000;
    
    char *dir;
    dir = malloc(15);
    bzero(dir,15);
    char num[3];
    strcat(dir,"./hash/");
    sprintf(num,"%i",hash);
    strcat(dir,num);

    fp = fopen(dir,"a");
    size = ftell(fp)/36;
    fclose(fp);

    fp = fopen(dir,"r");

    for(int i = 0; i < size; i++){
        fread(&tid,sizeof(int),1,fp);
        if(tid == id){
            f = 1;
            break;
        }else{
            fseek(fp,36-sizeof(int),SEEK_CUR);
        }
    }
       
    /*while(!f && ftell(fp)<(size*100)){
        //printw("%li\n",ftell(fp));
        fread(&tid,sizeof(int),1,fp);
        //printw("%i\n",tid);
        if(tid==id){f=1;break;}
        fseek(fp,100-sizeof(int),SEEK_CUR);
    }*/
    fclose(fp);
    return f;
}



int verRegistro(){
    int size,id,v, tid;
    FILE *fp;
    fp = fopen("./dataDogs.dat","a");
    fseek(fp, 0L, SEEK_END);
    size = (int)(ftell(fp)/100);
    fclose(fp);

    printw("Número de registros actuales: %i\nIngrese ID: ",size);
    
    //printw("ID: ");
    scanw("%i",&id);

    v = verificacion(id);

    if(!v){printw("\nNo existe registro con ID %i\n",id);return -1;}
    
    /*Buscar en archivo grande datadogs, imprime toda 
    la info. si encuentra id imprimo la info
    leer del archivo a un struct e imprimirlo en consola*/ 
    fp = fopen("./dataDogs.dat","r");

    struct dogType *data;
    data = malloc(sizeof(struct dogType));

    for(int i = 0; i < size; i++){
        fread(&tid,sizeof(int),1,fp);
        if(tid == id){
            fread(data->nombre,32,1,fp);
            printw("\n\nRegistro  con el ID: %i\n",id);
            printw("Nombre: %s\n", data->nombre);
            fread(data->tipo,32,1,fp);
            printw("Tipo: %s\n", data->tipo);
            fread(&data->edad,sizeof(int),1,fp);
            printw("Edad: %i\n", data->edad);
            fread(data->raza,16,1,fp);
            printw("Raza: %s\n", data->raza);
            fread(&data->estatura,sizeof(int),1,fp);
            printw("Estatura: %i\n", data->estatura);
            fread(&data->peso,sizeof(double),1,fp);
            printw("Peso: %f\n", data->peso);
            fread(&data->sexo,1,1,fp);
            printw("Sexo: %c\n", data->sexo);
            break;
        }else{
            fseek(fp,100-sizeof(int),SEEK_CUR);
        }
    }

    char* dir;
    dir = malloc(25);
    bzero(dir,25);
    char num[8];
    strcat(dir,"./historias/");
    sprintf(num,"%i",id);
    strcat(dir,num);
    strcat(dir,".txt");

    //printw("dir %s\n",dir);
    
    fp = fopen(dir,"a");
    fclose(fp);
    
    char* com;
    com = malloc(35);
    bzero(com,35);
    strcat(com,"gedit ");
    strcat(com,dir);

    //printw("%s\n",com);

    system(com);

    return 0;
}