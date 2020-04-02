#include <stdio.h>
#include "general.h"
#include "uno.h"
#include "dos.h"
#include "tres.h"
#include "cuatro.h"

int main(){
    int opcion,r;
    
    printf("------------Veterinaria Juano's------------\n\n");
    printf("Opciones: \n");
    printf("    1. Ingresar Registro\n");
    printf("    2. Ver Registro\n");
    printf("    3. Eliminar Registro\n");
    printf("    4. Buscar Registro\n");
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

    case 2:
        r = verRegistro();
        break;

    case 3:
        r = eliminarRegistro();
        break;

    case 4:
        r = buscarRegistro();
        break;
    
    default:
        break;
    }

}