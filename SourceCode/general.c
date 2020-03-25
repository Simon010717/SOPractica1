#include "general.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int hashf(char word[],int l){
    int m,h,i,x,p;
    m = 1000;

    p = 10007;
    x = 22;

    for(i=0;i<l;i++){
        word[i] = tolower(word[i]);
    }

    h = 1;
    for(i=0; i<l; i++){
        h = (p + h*x+(int)word[i])%p;
    }

    return h%m;
}