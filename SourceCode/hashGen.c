#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(){
    int i,m;
    m = 1000;
    for(i=0; i<m; i++){
        char* dir;
        dir = malloc(15);
        char num[3];
        sprintf(num, "%i", i);
        strcat(dir,"./hash/");
        strcat(dir,num);
        FILE *fp;
        fp = fopen(dir,"w+");
        fclose(fp);
    }

    return 0;
}