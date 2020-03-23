#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "general.h"

int loadStruct(void *ap, int n){
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

   r = loadStruct(data,n);

   hash = hashf(data->nombre,sizeof(data->nombre));
   id = hash;

   char dir[10];
   char num[3];
   sprintf(dir,"%s","./hash/");
   sprintf(num,"%i",hash);
   strcat(num,dir);

   FILE *fp;
   fp = fopen(dir,"r");
   fseek(fp, 0L, SEEK_END);
   size = ftell(fp);
   fseek(fp, 0L, SEEK_SET);
   for(pos=0;pos<size;pos+=36){
      fseek(fp,pos,SEKK_SET);
      fread(tempid,4,1,fp);
      printf("%i",tempid);
   }

   /*
   FILE *fp;
   fp = fopen("petsdata.dat","a");
   void *ap = fp;
   printf("ap pointer %p\n",ap);
   
   if(fp==NULL){perror("error fopen");exit(-1);}

   r = fwrite(data,sizeof(struct petType),1,fp);

   //printf("%i\n", r);

   fclose(fp);

   int h;
   char id[5];
   idgiver(id,n);
   h = hashf(id,5);

   printf("hash %i\n",h);

   if(idt[h] == NULL){
      idt[h] = (void *) ap;
      printf("pointer: %p\n", idt[h]);
   } else {
      struct petType *d;
      d = malloc(sizeof(struct petType));
      d = idt[h];
      while(d->idnext != NULL){
         printf("here we go again\n");
         d = d->idnext;
      }
   }
   */
   return 0;
}

int main(){
   //inicializacion
   int m,n,r,o,i;

   n = 0;//numero de registros
   m = 1000;//cardinalidad de las tablas

   void *namet[m];
   void *idt[m];

   for(i=0; i<m; i++){
      namet[i] = NULL;
      idt[i] = NULL;
   }
   srand(666);
   while(1){
   //ingresarRegistro

   r = ingresarRegistro(fp,n,namet,idt);

   if(r!=0){printf("Registro fallido.");}
   else{printf("Registro agregado exitosamente.");n++;}
   }
   return 0;
}