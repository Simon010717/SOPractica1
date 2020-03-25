#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verificacion(int id, int size){
    int f,tid;
    f = 0;
    FILE *fp;
    fp = fopen("../data.dat","r");
    while(!f && ftell(fp)<(size*100)){
        //printf("%li\n",ftell(fp));
        fread(&tid,sizeof(int),1,fp);
        //printf("%i\n",tid);
        if(tid==id){f=1;break;}
        fseek(fp,100-sizeof(int),SEEK_CUR);
    }
    fclose(fp);
    return f;
}

int verRegistro(){
    int size,id,v;
    FILE *fp;
    fp = fopen("../data.dat","a");
    fseek(fp, 0L, SEEK_END);
    size = (int)(ftell(fp)/100);
    fclose(fp);
/*
    int f,tid;
    f = 0;
    fp = fopen("../data.dat","r");
    while(!f && ftell(fp)<(size*100)){
        //printf("%li\n",ftell(fp));
        fread(&tid,sizeof(int),1,fp);
        printf("- %i\n",tid);
        fseek(fp,100-sizeof(int),SEEK_CUR);
    }
    fclose(fp);
*/
    printf("Número de registros actuales: %i\nIngrese ID: ",size);
    
    //printf("ID: ");
    scanf("%i",&id);

    v = verificacion(id,size);

    if(!v){printf("\nNo existe registro con ID %i\n",id);return -1;}

    char* dir;
    dir = malloc(25);
    bzero(dir,25);
    char num[8];
    strcat(dir,"./historias/");
    //printf("%s\n",dir);
    sprintf(num,"%i",id);
    //printf("%s\n",num);
    strcat(dir,num);
    strcat(dir,".txt");

    //printf("dir %s\n",dir);
    
    fp = fopen(dir,"a");
    fclose(fp);
    
    char* com;
    com = malloc(35);
    bzero(com,35);
    strcat(com,"gedit ");
    strcat(com,dir);

    //printf("%s\n",com);

    system(com);

    return 0;
}

int main(){
    verRegistro();

    return 0;
}