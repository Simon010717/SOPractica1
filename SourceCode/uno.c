#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "general.h"

int loadStruct(void *ap){
   struct petType *data;
   data = ap;
   printf("Nombre: ");
   scanf(" %s", data->nombre);
   printf("Tipo: ");
   scanf(" %s", data->tipo);
   printf("Edad: ");
   scanf(" %i", &data->edad);
   printf("Raza: ");
   scanf(" %s", data->raza);
   printf("Estatura: ");
   scanf(" %i", &data->estatura);
   printf("Peso: ");
   scanf(" %f", &data->peso);
   printf("Sexo: ");
   scanf(" %c", &data->sexo);

   return 0;
}

int ingresarRegistro(){
   int r,pos,id,hash,size;
   int *tempid;

   struct petType *data;
   data = malloc(sizeof(struct petType));

   r = loadStruct(data);

   //printf("%i\n",r);

   hash = hashf(data->nombre,sizeof(*data->nombre));

   //printf("%i\n",hash);

   char* dir;
   dir = malloc(15);
   bzero(dir,15);
   char num[3];
   strcat(dir,"./hash/");
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
   data->id = id;
   //printf("id %i\n",id);

   fp = fopen(dir,"a");
   fwrite(&id,sizeof(int),1,fp);
   fwrite(data->nombre,32,1,fp);

   fclose(fp);
   
   fp = fopen("data.dat","a");
   
   if(fp==NULL){perror("error fopen");exit(-1);}

   r = fwrite(data,sizeof(struct petType),1,fp);

   fclose(fp);

   printf("ID: %i. ",id);
   
   return 0;
}
/*
int main(){
   int r;
   while(1){
      r = ingresarRegistro();

      if(r!=0){printf("Registro fallido.\n");}
      else{printf("Registro exitoso.\n");}  
   }
   return 0;
}*/