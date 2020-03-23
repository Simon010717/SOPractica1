#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct petType{
    char id[5];
    char nombre[32];
    char tipo[32];
    int edad;
    char raza[16];
    int estatura;
    float peso;
    char sexo;
    int idhash;
    int namehash;
    void *idnext;
    void *namenext;
};

int hashf(char word[]){
   int m,h,i,x,p;
   m = 1000;
   int ps[10] = {10007, 10009, 10037, 10039, 10061, 10067, 10069, 10079, 10091, 10093};

   p = 10007;
   int r = rand();
   x = 11 + r%(32-11);

   h = 1;

   for(i=0; i<32; i++){
      h = (h*x+(int)word[i])%p;
   }

   return h%m;
}

int idgiver(char id[5], int n){
   if(n<1){id = "aaaaa";}
   id = "zzzzz";

   return 0;
}
/*
int loadStruct(void *ap, int n){
    struct petType *data;
    data = ap;
    printf("Id (5 chars): ");
    sacnf("%s", data->id);
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
    data->idhash = hashf(data->id);
    data->namehash = hashf(data->nombre);
    data->idnext = NULL;
    data->namenext = NULL;

    return 0;
}*/

int main(){/*
    srand(time(0));

    int r;
    
    struct petType *data;
    data = malloc(sizeof(struct petType));
    
    sprintf(data->id,"aaaaa");
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
    data->idhash = hashf(data->id);
    data->namehash = hashf(data->nombre);
    data->idnext = NULL;
    data->namenext = NULL;

    r = 0;

    printf("%i", r);

    FILE *fp;
    fp = fopen("petsdata.dat","a");
    
    if(fp==NULL){perror("error fopen");exit(-1);}

    r = fwrite(data,sizeof(struct petType),1,fp);

    fclose(fp);

    printf("%i", r);
/*
    struct petType *pet;
    pet = malloc(sizeof(struct petType));
    sprintf(pet->id,"aaaaa");sprintf(pet->nombre,"Pepe");sprintf(pet->tipo,"Perro");pet->edad=5;sprintf(pet->raza,"Labrador");
    pet->estatura=56;pet->peso=26.2;pet->sexo='M';pet->idhash=hashf(pet->id);pet->namehash=hashf(pet->nombre);

    int r;
    r = fwrite((void *) fp,sizeof(struct petType),1,fp);
    if(r<0){perror("error fwrite");exit(-1);}
    r = fclose(fp);
    if(r<0){perror("error fclose");exit(-1);}

    char* nombres[10] = {"Aarón","Abanero","Abel","Abelardo","Abraham","Adán","Adolfo","Adrián","Agustín","Aire"};
    char* tipos[10] = {"Perro","Perro","Perro","Perro","Gato","Gato","Hamster","Tortuga","Gato"};
    char sexos[2] = "MH";

    int i;
    for(i=0; i<99;i++){
        FILE *fp;
        fp = fopen("petsdata.dat","a");
        
        if(fp==NULL){perror("error fopen");exit(-1);}

        struct petType *pet;
        pet = malloc(sizeof(struct petType));
        sprintf(pet->id,"aaaab");sprintf(pet->nombre,nombres[i%10]);sprintf(pet->tipo,tipos[i%10]);pet->edad=rand()%15;sprintf(pet->raza,"-");
        pet->estatura=rand()%90;pet->peso=rand()%70+0.2;pet->sexo=sexos[i%2];pet->idhash=hashf(pet->id);pet->namehash=hashf(pet->nombre);

        int r;
        r = fwrite((void *) fp,sizeof(struct petType),1,fp);
        if(r<0){perror("error fwrite");exit(-1);}
        r = fclose(fp);
        if(r<0){perror("error fclose");exit(-1);}
    }
*/
    int i;
    for(i=0; i<100; i++){
        char str[3];
        sprintf(str, "%i", i);
        FILE *fp;
        fp = fopen(str,"w+");
    }

    return 0;
}