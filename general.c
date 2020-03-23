#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct petType{
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