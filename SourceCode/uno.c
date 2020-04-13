#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "general.h"

/*----------------- loadStruct --------------------------------
   |  Funcion: loadStruct
   |
   |  Proposito: Carga los datos ingresados por el usuario a un apuntador dogType que se pasa como parametro. 
   |
   |  Parametros:
   |    ap (IN) -- Apuntador al lugar donde se quiere guardar la informacion leida.
   |
   |  Retorna:  0 si la operacion es exitosa.
   -------------------------------------------------------------------/*/
int loadStruct(void *ap){
   struct dogType *data;                                                      // Declaracion de la estructura sobre el apuntador parametro
   data = ap;
   printw("Nombre: ");                                                        // Lectura de cada dato y almacenamiento sobre la estructura declarada
   bzero(data->nombre,32);
   scanw(" %s", data->nombre);
   printw("Tipo: ");
   scanw(" %s", data->tipo);
   printw("Edad: ");
   scanw(" %i", &data->edad);
   printw("Raza: ");
   scanw(" %s", data->raza);
   printw("Estatura: ");
   scanw(" %i", &data->estatura);
   printw("Peso: ");
   scanw(" %f", &data->peso);
   printw("Sexo: ");
   scanw(" %c", &data->sexo);

   return 0;
}


/*----------------- ingresarRegistro --------------------------------
   |  Funcion ingresarRegistro
   |
   |  Proposito: Guarda la informacion ingresada por el usuario en el 
   |  archivo dataDogs.dat e ingresa los datos a la tabla hash (que se
   |  encuentra en la carpeta hash) 
   |
   |  Parametros:
   |
   |  Retorna:  0 si la operacion es exitosa.
   -------------------------------------------------------------------/*/
int ingresarRegistro(){
   int r,pos,id,hash,size;                                                   // Declaracion de variables enteros
   int *tempid;                                                              // Declaracion del apuntador donde se guardara el id leido en la interacion de los archivos

   struct dogType *data;                                                     // Declaracion del apuntador a una estructura dogType donde se guardara la informacion ingresada
   data = malloc(sizeof(struct dogType));                                    // Reserva del espacio de memoria de la estuctura dogType

   r = loadStruct(data);                                                     // Llamada a la funcion que cargara la informacion ingresada al apuntador data

   hash = hashf(data->nombre,32);                                            // Llamada a la funcion hashf obteniendo el coidgo hash del nombre ingresado, que se encuentra en SourceCode/general.c

   char* dir;                                                                // Arreglo de caracteres que contendra la direccion del archivo de la tabla hash donde se debera ingresar los datos
   dir = malloc(15);                                                         // Reserva del espacio de memoria para la direccion
   bzero(dir,15);                                                            // Limpieza del espacio de memoria de la direccion
   char num[3];                                                              // Arreglo de caracteres que contiene el codigo hash de la estructura
   strcat(dir,"./hash/");                                                    // Concatenacion de la cadena "./hash/" a dir
   sprintf(num,"%i",hash);                                                   // Conversion del numero entero hash a arreglo de caracteres (num)
   strcat(dir,num);                                                          // Concatenacion del numero (num) a dir. Ahora dir contiene la direccion del archivo hash correspondiente


   FILE *fp;                                                                 // Declaracion del apuntador del archivo de la entrada a la tabla hash
   fp = fopen(dir,"a");                                                      // Apertura del archivo hash "a" (para escritura al final del archivo) 
   size = ftell(fp);                                                         // Se guarda en la variable size la posicion en Bytes del apuntador interno del archivo. Esto nos permite saber el tamaño del archivo en Bytes.
   fclose(fp);                                                               // Cierre del archivo

   id = 1000*(int)(size/36)+hash;                                            // Sabiendo el tamaño del archivo de esa entrada hash especifica, podemos calcular un id unico almaceando en la variable id
   data->id = id;                                                            // Se almacena este id en la estructura dogType donde ya se ha almecenado los datos ingresados

   fp = fopen(dir,"a");                                                      // Apertura del documento hash con argumento "a" para escribir al final del fichero
   fwrite(&id,sizeof(int),1,fp);                                             // Escritura del id de la estructura
   fwrite(data->nombre,32,1,fp);                                             // Escritura del nombre ingresado

   fclose(fp);                                                               // Cierre del archivo
   
   fp = fopen("dataDogs.dat","a");                                           // Apertura del archivo dataDogs.dat con argumento "a" para esciribr al final del fichero

   r = fwrite(data,sizeof(struct dogType),1,fp);                             // Escritura al final del archivo de la estructura entera con todos los datos ingresados

   fclose(fp);                                                               // Cierre del archivo

   free(data);                                                               // Liberacion de la memoria reservada en data (estructura donde se guardaron los datos)
   free(dir);                                                                // Liberacion de la memoria reservada en dir (arreglo que contenia la direccion del archivo hash)

   printw("ID: %i. ",id);                                                    // Impresion del ID con el que se guardo la informacion ingresada
      
   return 0;
}