#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include <ncurses.h>

/*----------------- eliminarRegistro --------------------------------
   |  Funcion: eliminarRegistro
   |
   |  Proposito: Verificar si un registro existe, eliminarlo de dataDogs.dat y 
   |  de la entrada a la tabla hash disminuyendo el tamaño de los archivos. 
   |
   |  Parametros:
   |
   |  Retorna:  0 si la función es exitosa.
   -------------------------------------------------------------------/*/

int eliminarRegistro(){
    int total, id, f, tid, hash, size;                    // Declaración de las variables enteras


    FILE *fp;                                             // Inicializacion del apuntador al archivo dataDogs.dat
    FILE *newfp;                                          // Inicializacion del apuntador a una copia del archivo dataDogs.dat omitiendo el registro a eliminar.
    fp = fopen("./dataDogs.dat","a");                     // Apertura de dataDogs.dat con argumento "a" para escribir al final del fichero
    total = ftell(fp)/100;                                // Se guarda en la variable total la posicion en Bytes del apuntador interno del archivo. Esto nos permite saber el numero de estructuras almacenadas en el archivo al dividir por el tamaño de una unica estructura.

    printw("Existen %i registros.\n",total);              // Impresion del numero de registros
    printw("ID de estructura que desea eliminar: ");      // Impresion mensaje
    scanw("%i",&id);                                      // Lectura del id del registro a eliminare.

    fclose(fp);                                           // Cierra el archivo dataDogs.dat
 
    hash = id % 1000;                                     // Guardamos en la variable hash el codigo hash de la estructura aplicandole modulo mil a el id

    char *dir;                                            // Arreglo de caracteres que contendra la direccion del archivo de la tabla hash.
    dir = malloc(15);                                     // Reserva del espacio de memoria para la direccion
    bzero(dir,15);                                        // Limpieza del espacio de memoria de la direccion                                                    
    char num[3];                                          // Arreglo de caracteres que contiene el codigo hash de la estructura
    strcat(dir,"./hash/");                                // Concatenacion de la cadena "./hash/" a dir
    sprintf(num,"%i",hash);                               // Conversion del numero entero hash a arreglo de caracteres (num)
    strcat(dir,num);                                      // Concatenacion del numero (num) a dir. Ahora dir contiene la direccion del archivo hash correspondiente


    fp = fopen(dir,"a");                                  // Apertura de dataDogs.dat con argumento "a" para escribir al final del fichero.
    size = ftell(fp)/36;                                  // Se guarda en la variable size el numero de elementos en la tabla hash.
    fclose(fp);                                           // Cierra el archivo dataDogs.dat

    fp = fopen(dir,"r");                                  // Apertura del archivo hash "r" (para lectura).
    newfp = fopen("./hash/temp","a");                     // Creacion de la copia del archivo hash (Vacio) con argumento "a" para escribir al final del fichero.

    char *m = malloc(36);                                 // Reserva del espacio de memoria para el paquete (id,nombre) que copiamos al segundo archivo

    f = 0;
    for ( int i = 0; i < size; i++ ){                     // Itera sobre los paquetes almacenados en el archivo hash
        fread(&tid,sizeof(int),1,fp);                     // Lee la id del paquete en iteracion y la guarda en la variable tid
        if(tid==id){                                      // Evalua si el tid es igual a el id ingresado
            fseek(fp,36-sizeof(int),SEEK_CUR);            // Salta a la siguiente estructura en el archivo omitinedo la que se busca eliminar
            f = 1;                                        // Cambia el valor de f a 1, indicando que se encontro un paquete con el id ingresado

        }
        else{                                             // Si no coincide
            fseek(fp,-sizeof(int),SEEK_CUR);              // Devuelve el apuntador de lectura de fp 4 bytes (Al inicio del paquete actual)
            fread(m, 36, 1, fp);                          // Lee y guarda en m el paquete actual
            fwrite(m, 36, 1, newfp);                      // Escribe sobre el segundo archivo el paquete leido.
        }
    }

    fclose(fp);                                           // Cierra el archivo hash
    fclose(newfp);                                        // Cierra la copia del archivo hash


    remove(dir);                                          // Borra el archivo hash original
    rename("./hash/temp", dir);                           // Renombra el segundo archivo a el nombre de el archivo original 
    if(!f) {                                              // Evalua
        printw("No existe un registro con ese ID\n");     // Si f es 0 (queriendo decir que no encontro un paquete con ese id), imprime el mensaje
        return 0;                                         // Termina la funcion
    }
    bzero(&tid,sizeof(int));                              // Limpieza del espacio de memoria del tid
    fp = fopen("./dataDogs.dat","r");                     // Apertura de dataDogs.dat con argumento "r" para lectura.     
    newfp = fopen("./newdata.dat","a");                   // Creacion de newData.dat (copia de dataDogs omitiendo la estructura a eliminar) con
    
    char *c = malloc(100);                                // Reserva del espacio de memoria para la estructura que copiamos al segundo archivo
    

    for ( int i = 0; i < total; i++ ){                    // Iteracion sobre las estructuras del archivo
        fread(&tid,sizeof(int),1,fp);                     // Lee la id de la estructura en iteracion y la guarda en la variable tid
        if(tid==id){                                      // Evalua si el tid es igual a el id ingresado
            fseek(fp,100-sizeof(int),SEEK_CUR);           // Salta a la siguiente estructura en el archivo omitinedo la que se busca eliminar
        }
        else{                                             // Si no coincide
            fseek(fp,-sizeof(int),SEEK_CUR);              // Devuelve el apuntador de lectura de fp 4 bytes (Al inicio de la estructura actual actual)
            fread(c, 100, 1, fp);                         // Lee y guarda en c la estructura actual
            fwrite(c, 100, 1, newfp);                     // Escribe sobre el segundo archivo el paquete leido.
        }
    }

    fclose(fp);                                           // Cierre del archivo dataDogs.dat
    fclose(newfp);                                        // Cierre del archivo newData.dat

    free(c);                                              // Se libera el espacio de memoria reservado para c
    free(m);                                              // Se libera el espacio de memoria reservado para m
    
    printw("Registro eliminado exitosamente\n");          // Impresion del mensaje
    remove("./dataDogs.dat");                             // Eliminacion del archivo original dataDogs.dat
    rename("./newdata.dat", "./dataDogs.dat");            // Renombra el segundo archivo a el nombre de el archivo original 
    
    return 0;
}

