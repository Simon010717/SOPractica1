#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "general.h"

int loadStruct(void *ap){
   struct dogType *data;
   data = ap;
   printw("Nombre: ");
   bzero(data->nombre,32);
   scanw(" %s", data->nombre);
   printw("Tipo: ");
   scanw(" %s", data->tipo);
   printw("Edad: ");
   scanw(" %i", &data->edad);
   printw("Raza: ");
   scanw(" %s", data->raza);
   printw("Estatura: ");
   scanw(" %i", &data->estatura);
   printw("Peso: ");
   scanw(" %f", &data->peso);
   printw("Sexo: ");
   scanw(" %c", &data->sexo);

   return 0;
}

int ingresarRegistro(){
   int r,pos,id,hash,size;
   int *tempid;

   struct dogType *data;
   data = malloc(sizeof(struct dogType));

   r = loadStruct(data);

   hash = hashf(data->nombre,32);

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
   size = ftell(fp);
   fclose(fp);

   id = 1000*(int)(size/36)+hash;
   data->id = id;

   fp = fopen(dir,"a");
   fwrite(&id,sizeof(int),1,fp);
   fwrite(data->nombre,32,1,fp);

   fclose(fp);
   
   fp = fopen("dataDogs.dat","a");
   
   if(fp==NULL){perror("error fopen");exit(-1);}

   r = fwrite(data,sizeof(struct dogType),1,fp);

   fclose(fp);

   printw("ID: %i. ",id);
   
   return 0;
}
/*
int main(){
   int r;
   while(1){
      r = ingresarRegistro();

      if(r!=0){printw("Registro fallido.\n");}
      else{printw("Registro exitoso.\n");}  
   }
   return 0;
}*/