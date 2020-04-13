#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include "general.h"


/*----------------- buscarRegistro -------------------------------------
   |  Funcion: buscarRegistro
   |
   |  Proposito: Busca y muestra todos los registros que coinciden con   
   |  el nombre ingresado sin tener en cuenta la capitalizacion
   |
   |  Parametros:
   |
   |  Retorna:  0 si la función es exitosa.
   -------------------------------------------------------------------/*/

int buscarRegistro(){
    int hash,size,tid,l,i;                                // Declaracion de variables enteras
    char tnombre[32];                                        // Declaracion del arreglo de caracteres temporal de la iteracion 
    char nombre[32];                                         // Declaracion del arreglo de caracteres del nombre buscado 
    bzero(tnombre,32); bzero(nombre,32);                     // Limpieza del espacio en memoria 
    printw("Ingrese nombre a buscar: ");                     // Solicitud de ingreso de nombre 
    scanw("%s",nombre);                                      // Lectura del nombre ingresado

    for(i=0;i<32;i++){                                       // Iteracion sobre los caracteres del nombre
        nombre[i] = tolower(nombre[i]);                      // Conversion de los caracteres a minusculas
    }

    hash = hashf(nombre,32);                                 // LLamada a la funcion de hashf
    printw("hash %i\n",hash);                                // Impresion del codigo hash


    char *dir;                                               // Arreglo de caracteres que contendra la direccion del archivo de la tabla hash.
    dir = malloc(15);                                        // Reserva del espacio de memoria para la direccion
    bzero(dir,15);                                           // Limpieza del espacio de memoria de la direccion
    char num[3];                                             // Arreglo de caracteres que contiene el codigo hash de la estructura
    strcat(dir,"./hash/");                                   // Concatenacion de la cadena "./hash/" a dir
    sprintf(num,"%i",hash);                                  // Conversion del numero entero hash a arreglo de caracteres (num)
    strcat(dir,num);                                         // Concatenacion del numero (num) a dir. Ahora dir contiene la direccion del archivo hash correspondiente


    FILE *fp;                                                // Inicializacion del apuntador al archivo hash donde se hara la verificacion.
    fp = fopen(dir,"a");                                     // Apertura del archivo hash con argumento "a" para escribir al final del fichero.
    size = (int)(ftell(fp)/36);                              // Guarda en la variable size la cantidad de paquetes en elarchivo hash                                
    fclose(fp);                                              // Cierre del archivo hash

    fp = fopen(dir,"r");                                     // Apertura del archivo hash con argumento "r" para lectutra
    printw("ID de registros con nombre \"%s\":\n",nombre);   // Impresion de mensaje
    while(ftell(fp)<(size*36)){                              // Iteracion sobre paquetes en el archivo hash. Todos los archivos con el mismo nombre se encuentran en el mismo archivo hash, pero dos nombres diferentes pueden tener el mismo codigo hash
        fread(&tid,4,1,fp);                                  // Lectura y almacenamiento del id del paquete en la variable tid
        fread(tnombre,32,1,fp);                              // Lectura de almacenamiento del nombre del paquete
        for(i=0;i<32;i++){tnombre[i] = tolower(tnombre[i]);} // Iteracion sobre los caracteres del nombre y conversion a minuscula 
        if(strcmp(nombre,tnombre) == 0){                     // Compara el nombre a buscar y el nombre leido
            printw("   - %i\n",tid);                         // Si coinciden imprime el id leido 
        }
        fseek(fp,36-sizeof(int)-32,SEEK_CUR);                // Salto al inicio del siguiente paquete
    }

    free(dir);                                               // Liberar memoria de dir
    return 0;
}