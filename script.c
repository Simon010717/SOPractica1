#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 10000

struct petType{
   char nombre[32];
   char tipo[32];
   int edad;
   char raza[16];
   int estatura;
   float peso;
   char sexo;
   int hash;
   int *next;
};

int hashf(char word[]){
   int m,h,i,x,p;
   m = 10000;
   int ps[10] = {10007, 10009, 10037, 10039, 10061, 10067, 10069, 10079, 10091, 10093};

   p = 1007;
   int r = rand();
   x = 11 + r%(32-11);

   h = 1;

   for(i=0; i<32; i++){
      h = (h*x+(int)word[i])%p;
   }

   return h%m;
}


int loadStruct(void *ap){
   struct petType *data;
   data = ap;
   scanf(" %s", data->nombre);
   scanf(" %s", data->tipo);
   scanf(" %i", &data->edad);
   scanf(" %s", data->raza);
   scanf(" %i", &data->estatura);
   scanf(" %f", &data->peso);
   scanf(" %c", &data->sexo);
   scanf(" %i", &data->hash);
   //scanf(" %i", data->next);
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
   printf("\nhash: %i", data->hash);
}

int loadFile(FILE *fp, ){

}

int main(){
   struct petType *Sultan;

   void *table[10000];

   srand(666);

   char* w;
   w = "juanoElMasChimba";

   printf("%i\n",hashf(w));

   return 0;
}