#include <stdio.h>
#include <ncurses.h>
#include <curses.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "general.h"
#include "uno.h"
#include "dos.h"
#include "tres.h"
#include "cuatro.h"


void pressToContinue(){
    printw("\nPulse cualquier tecla para continuar...\n");                        // Espera por una tecla para continuar.
    noecho();                                                                     // Impide que se muestre el caracter en consola.
    getch();                                                                      // Obtiene el caracter.
    echo();                                                                       // Permite de nuevo el ingreso de caracteres.    
    clear();                                                               
}


int main(){
    initscr();
    clear();
    refresh();

    while(1){
        
        int opcion,r;
    
        printw("------------Veterinaria Juano's------------\n\n");
        printw("Opciones: \n");
        printw("    1. Ingresar Registro\n");
        printw("    2. Ver Registro\n");
        printw("    3. Eliminar Registro\n");
        printw("    4. Buscar Registro\n");
        printw("    5. Salir\n");
        printw("\n\n");
        printw("Digite su opción: ");

        scanw("%i", &opcion);

        switch (opcion)
        {
        case 1:
            r = ingresarRegistro();

            if (r!=0) {printw("Registro fallido.\n");}
            else {printw("Registro exitoso.\n");} 
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
        
        case 5:
            break;
        
        default:
            printw("\n");
        }

        pressToContinue();
        
    }
    clear(); 
    endwin();
    return 0;
}