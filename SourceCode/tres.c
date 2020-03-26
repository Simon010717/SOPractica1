#include<stdio.h>

int delete(){
    int total, id, f, del, rname, tid, num, test;

    FILE *fp;
    FILE *newfp;
    fp = fopen("../data.dat","a");
    newfp = fopen("../newdata.dat","w");
    total = ftell(fp)/100;

    printf("%i\n",total);
    printf("ID de estructura que desea eliminar: ");
    scanf("%i",&id);

    printf("%i\n", id);
    fclose(fp);
    fp = fopen("../data.dat","r");

   
    test = 0;
    while(  test < (total) ){
         
        fread(&tid,sizeof(int),1,fp);

        printf("%i\n", tid);

        if(tid==id){
            fseek(fp,100-sizeof(int),SEEK_CUR);
            printf("ola\n");
        }
        else{
            test = test + 1;
            fseek(fp,-sizeof(int),SEEK_CUR);
            num = fwrite(fp, 100, 1, newfp);
            if (num = 1)
                printf("The file was copied successfully\n");
            else
            printf("the file has failed to copy\n"); 
        }
        
    }
    fclose(fp);

    /*
    del = remove("data.dat");
    if (!del)
      printf("The file is Deleted successfully");
    else
      printf("the file is not Deleted");
    rname = rename(c"newdata.dat", "data.dat");
    */

    fclose(newfp);

    

    
    
    
    return 0;
}

   



int main(){
    delete();
}
