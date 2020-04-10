#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include <ncurses.h>


int eliminarRegistro(){
    int total, id, f, tid, hash, size;


    FILE *fp;
    FILE *newfp;
    fp = fopen("./dataDogs.dat","a");
    total = ftell(fp)/100;

    printw("Existen %i registros.\n",total);
    printw("ID de estructura que desea eliminar: ");
    scanw("%i",&id);

    fclose(fp);
 
    hash = id % 1000;

    char *dir;
    dir = malloc(15);
    bzero(dir,15);
    char num[3];
    strcat(dir,"./hash/");
    sprintf(num,"%i",hash);
    strcat(dir,num);

    fp = fopen(dir,"a");
    size = ftell(fp)/36;
    fclose(fp);

    fp = fopen(dir,"r");
    newfp = fopen("./hash/temp","a");

    char *m = malloc(36);

    for ( int i = 0; i < size; i++ ){
        fread(&tid,sizeof(int),1,fp);
        if(tid==id){
            fseek(fp,36-sizeof(int),SEEK_CUR);
            f = 1;

        }
        else{
            fseek(fp,-sizeof(int),SEEK_CUR);
            fread(m, 36, 1, fp);
            fwrite(m, 36, 1, newfp);
        }
    }

    fclose(fp);
    fclose(newfp);


    remove(dir);
    rename("./hash/temp", dir);
    if(!f) {
        printw("No existe un registro con ese ID\n");
        return 0;
    }
    bzero(&tid,sizeof(int));
    fp = fopen("./dataDogs.dat","r");
    newfp = fopen("./newdata.dat","a");
    
    char *c = malloc(100);
    

    for ( int i = 0; i < total; i++ ){
        fread(&tid,sizeof(int),1,fp);
        if(tid==id){
            fseek(fp,100-sizeof(int),SEEK_CUR);
        }

        else{
            fseek(fp,-sizeof(int),SEEK_CUR);
            fread(c, 100, 1, fp);
            fwrite(c, 100, 1, newfp); 
        }
    }
    fclose(fp);
    fclose(newfp);

    free(c);
    free(m);
    
    printw("Registro eliminado exitosamente\n");
    remove("./dataDogs.dat");
    rename("./newdata.dat", "./dataDogs.dat");
    
    return 0;
}

