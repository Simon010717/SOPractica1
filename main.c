#include <stdio.h>
#include "general.h"
#include "uno.h"

int main(){
    int opcion,r;
    
    printf("------------Veterinaria Juano------------\n\n");
    printf("Opciones: \n");
    printf("    1. Ingresar Registro");
    printf("\n\n");
    printf("Digite su opción: ");

    scanf("%i", &opcion);

    switch (opcion)
    {
    case 1:
        r = ingresarRegistro();

        if (r!=0) {printf("Registro fallido.\n");}
        else {printf("Registro exitoso.\n");} 
        break;
    
    default:
        break;
    }

}