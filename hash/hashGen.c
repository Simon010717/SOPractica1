#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int i,m;
    m = 100;
    for(i=0; i<m; i++){
        char str[3];
        sprintf(str, "%i", i);
        FILE *fp;
        fp = fopen(str,"w+");
        fclose(fp);
    }

    return 0;
}