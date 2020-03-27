#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>


int delete(){
    int total, id, f, del, rname, tid, hash, size;


    FILE *fp;
    FILE *newfp;
    fp = fopen("../dataDogs.dat","a");
    total = ftell(fp)/100;

    printf("%i\n",total);
    printf("ID de estructura que desea eliminar: ");
    scanf("%i",&id);

    fclose(fp);
 
    hash = id % 1000;

    char *dir;
    dir = malloc(15);
    bzero(dir,15);
    char num[3];
    strcat(dir,"../hash/");
    sprintf(num,"%i",hash);
    strcat(dir,num);

    fp = fopen(dir,"a");
    size = ftell(fp)/36;
    fclose(fp);

    fp = fopen(dir,"r");
    newfp = fopen("../hash/temp","a");

    for ( int i = 0; i < size; i++ ){
        fread(&tid,sizeof(int),1,fp);

        if(tid==id){
            fseek(fp,36-sizeof(int),SEEK_CUR);
            f = 1;

        }
        else{
            fseek(fp,-sizeof(int),SEEK_CUR);
            fwrite(newfp, 36, 1, fp); 
            fseek(fp,36,SEEK_CUR);
        }
    }

    fclose(fp);
    fclose(newfp);


    remove(dir);
    rename("../hash/temp", dir);
    if(!f) return 0;

    bzero(&tid,sizeof(int));
    fp = fopen("../dataDogs.dat","r");
    newfp = fopen("../newdata.dat","a");

    for ( int i = 0; i < total; i++ ){
        printf("ola\n");
        printf("%li\n", fread(&tid,sizeof(int),1,fp));
        //fread(&tid,sizeof(int),1,fp);
        printf("%i\n",id);
        printf("%i\n",tid);
        if(tid==id){
            fseek(fp,100-sizeof(int),SEEK_CUR);
            printf("if\n");
        }

        else{
            printf("else\n");
            fseek(fp,-sizeof(int),SEEK_CUR);
            fwrite(newfp, 100, 1, fp); 
            fseek(fp,100,SEEK_CUR);
        }
    }
    fclose(fp);
    fclose(newfp);
    
    remove("../dataDogs.dat");
    rename("../newdata.dat", "../dataDogs.dat");
    
    return 0;
}

int main(){
    delete();
}
