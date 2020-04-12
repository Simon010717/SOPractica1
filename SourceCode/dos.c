#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "general.h"

/*----------------- verificacion --------------------------------
   |  Funcion: verificacion
   |
   |  Proposito: Verifica la existencia de una estructura
   |  almacenada que tiene el id ingresado por el usuario.
   |
   |  Parametros:
   |    id (IN) -- id de la estructura a comprobar
   |
   |  Retorna:  f = 1 si existe una estructura con el id ingresado.
   |            f = 0 si no existe una estructura con el id ingresado.
   -------------------------------------------------------------------/*/
int verificacion(int id){
    FILE* fp;                                             // Inicializacion del apuntador al archivo hash donde se hara la verificacion.

    int f, tid, hash, size;                               // Declaracion de las variables enteras.

    hash = id % 1000;                                     // Obtencion del codigo hash utilizando el id con la operacion id % 1000.
    
    char *dir;                                            // Arreglo de caracteres que contendra la direccion del archivo de la tabla hash.
    dir = malloc(15);                                     // Reserva del espacio de memoria para la direccion
    bzero(dir,15);                                        // Limpieza del espacio de memoria de la direccion
    char num[3];                                          // Arreglo de caracteres que contiene el codigo hash de la estructura
    strcat(dir,"./hash/");                                // Concatenacion de la cadena "./hash/" a dir
    sprintf(num,"%i",hash);                               // Conversion del numero entero hash a arreglo de caracteres (num)
    strcat(dir,num);                                      // Concatenacion del numero (num) a dir. Ahora dir contiene la direccion del archivo hash correspondiente

    fp = fopen(dir,"a");                                  // Apertura del archivo hash "a" (para escritura al final del archivo) 
    size = ftell(fp);                                     // Se guarda en la variable size la posicion en Bytes del apuntador interno del archivo. Esto nos permite saber el tamaño del archivo en Bytes.
    fclose(fp);                                           // Cierre del archivo

    fp = fopen(dir,"r");                                  // Apertura del archivo hash "r" (para lectura).

    for(int i = 0; i < size; i++){                        // Iteracion sobre los paquetes alamacenados en el archivo hash (un paquete contiene la id y el nombre de una estructura almacenada).
        fread(&tid,sizeof(int),1,fp);                     // Lectura del id y almacenamiento de este en la variable temporal tid.
        if(tid == id){                                    // Se verifica si la id leida (tid) corresponde a la id que se busca.
            f = 1;                                        // f (encontrado) = 1 (verdadero)
            break;                                        // Se sale del ciclo
        }else{                                            // El id leido (tid) no corresponde con el id que busca
            fseek(fp,36-sizeof(int),SEEK_CUR);            // Salta al inicio del siguiente paquete para iniciar nuevamente con la verificación
        }
    }
       
    fclose(fp);                                           // Cierre del archivo.
    free(dir);                                            // Se libera el espacio de memoria reservado para dir
    return f;                                             // Se retorna f (encontrado/no encontrado)
}


/*----------------- verRegistro --------------------------------
   |  Funcion: verRegistro
   |
   |  Proposito: Muestra el registro correspondiente al id
   |  ingresado por el usuario
   |
   |  Parametros: 
   |
   |  Retorna:  0 si la operacion es exitosa.
   -------------------------------------------------------------------/*/
int verRegistro(){
    int size,id,v, tid;                               // Declaracion de las variables enteras.
    FILE *fp;                               // Inicializacion del apuntador al archivo dataDogs.dat.
    fp = fopen("./dataDogs.dat","a");                                                   // Apertura del archivo "a" (para escritura al final del archivo).
    size = (int)(ftell(fp)/100);                                                        // Se guarda en la variable size la posicion en Bytes del apuntador interno del archivo. Esto nos permite saber el numero de estructuras almacenadas en el archivo al dividir por el tamaño de una unica estructura.
    fclose(fp);                                                                         // Cierre del archivo.

    printw("Número de registros actuales: %i\nIngrese ID: ",size);                      // Impresion del numero de registros actuales y solicitud de ingreso del id del registro que se desea ver.
    
    scanw("%i",&id);                               // Lectura del id del registro que se desea ver.

    v = verificacion(id);                               // Llamada a la función verificacion.

    if(!v){                               // Si el id no fue encontrado
        printw("\nNo existe registro con ID %i\n",id);                                // Se informa al usuario
        return -1;                               // La función retorna -1 (no exitoso)
        }                               
    
    fp = fopen("./dataDogs.dat","r");                               // Apertura del archivo dataDogs.dat "r" (para lectura)

    struct dogType *data;                               // Declaracion de un apuntador de una estructura dogType.
    data = malloc(sizeof(struct dogType));                               // Reserva del espacio de memora de la estructura dogType

    for(int i = 0; i < size; i++){                               // Iteracion sobre las estructuras almacenadas en el archivo datadogs.dat
        fread(&tid,sizeof(int),1,fp);                           // Lectura del id y almacenamiento de este en la variable temporal tid.
        if(tid == id){                                    // Se verifica si la id leida (tid) corresponde a la id que se busca.
            fread(data->nombre,32,1,fp);                                    // Se lee la informacion del archivo y se imprime en consola.
            printw("\n\nRegistro  con el ID: %i\n",id);                                    
            printw("Nombre: %s\n", data->nombre);
            fread(data->tipo,32,1,fp);
            printw("Tipo: %s\n", data->tipo);
            fread(&data->edad,sizeof(int),1,fp);
            printw("Edad: %i\n", data->edad);
            fread(data->raza,16,1,fp);
            printw("Raza: %s\n", data->raza);
            fread(&data->estatura,sizeof(int),1,fp);
            printw("Estatura: %i\n", data->estatura);
            fread(&data->peso,sizeof(double),1,fp);
            printw("Peso: %f\n", data->peso);
            fread(&data->sexo,1,1,fp);
            printw("Sexo: %c\n", data->sexo);
            break;
        }else{                                          // Si no corresponde,
            fseek(fp,100-sizeof(int),SEEK_CUR);                                 // Salta al inicio de la siguiente estructura 
        } 
    }

    char* dir;                                          // Arreglo de caracteres que contendra la direccion del archivo de historia clinica.
    dir = malloc(25);                                   // Reserva del espacio de memoria para la direccion.
    bzero(dir,25);                                      // Limpieza del espacio de memoria de la direccion.
    char num[8];                                        // Arreglo de caracteres que contendra el numero de historia clinica correspondiente.
    strcat(dir,"./historias/");                         // Concatenacion de la cadena "./historias/" a dir.
    sprintf(num,"%i",id);                               // Conversion del numero entero id a arreglo de caracteres (num).
    strcat(dir,num);                                    // Concatenacion del numero (num) a dir.
    strcat(dir,".txt");                                 // Concatenacion de la cadena ".txt" a dir.  Ahora dir contiene la direccion del archivo de historia clinica correspondiente.
    
    fp = fopen(dir,"a");                                // Creacion del archivo de historia clinica "a" (para escritura al final del archivo).
    fclose(fp);                                         // Cierre del archivo.
    
    char* com;                                          // Arreglo de caracteres que contendrá el comando para la apertura por consola de la historia clinica. 
    com = malloc(35);                                   // Reserva del espacio de memoria para el comando.
    bzero(com,35);                                      // Limpieza del espacio de memora para el comando.
    strcat(com,"gedit ");                               // Concatenacion de la cadena "gedit " a com.
    strcat(com,dir);                                    // Concatenacion de dir a com.

    system(com);                                        // Ejecucion en consola del comando (com).

    free(data);                                            // Se libera el espacio de memoria reservado para data
    free(dir);                                            // Se libera el espacio de memoria reservado para dir
    free(com);                                            // Se libera el espacio de memoria reservado para com
    
    return 0;
}