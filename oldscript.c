#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "uno.h"
#include "dos.h"
#include "tres.h"
#include "cuatro.h"
#include "cinco.h"

struct petType{
   int id;
   char nombre[32];
   char tipo[32];
   int edad;
   char raza[16];
   int estatura;
   float peso;
   char sexo;
   int idhash;
   int namehash;
};

int hashf(char word[],int l){
   int m,h,i,x,p;
   m = 100;
   int ps[10] = {10007, 10009, 10037, 10039, 10061, 10067, 10069, 10079, 10091, 10093};

   p = 10007;
   int r = rand();
   x = 22;

   h = 1;
   for(i=0; i<l; i++){
      h = (p + h*x+(int)word[i])%p;
   }

   return h%m;
}

int idgiver(char id[5], int n){
   if(n<1){id = "aaaaa";}
   id = "zzzzz";

   printf("id %s\n",id);

   return 0;
}

int loadStruct(void *ap, int n){
   struct petType *data;
   data = ap;
   char id[5];
   idgiver(id,n);
   sprintf(data->id,id);
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
   data->idhash = hashf(data->id,5);
   data->namehash = hashf(data->nombre,sizeof(data->nombre));
   data->idnext = NULL;
   data->namenext = NULL;

   return 0;
}

int ingresarRegistro(int n, void* namet[], void* idt[]){
   int r;

   struct petType *data;
   data = malloc(sizeof(struct petType));

   r = loadStruct(data,n);

   printf("%i\n", r);

   FILE *fp;
   fp = fopen("petsdata.dat","a");
   void *ap = fp;
   printf("ap pointer %p\n",ap);
   
   if(fp==NULL){perror("error fopen");exit(-1);}

   r = fwrite(data,sizeof(struct petType),1,fp);

   printf("%i\n", r);

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

   return 0;
}

int printStruct(void * ap){
   struct petType *data;
   data = ap;
   printf("\nnombre: %s", data->nombre);
   printf("\ntipo: %s", data->tipo);
   printf("\nedad: %i", data->edad);
   printf("\nraza: %s", data->raza);
   printf("\nestatura: %i",data->estatura);
   printf("\npeso: %f", data->peso);
   printf("\nsexo: %c", data->sexo);
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