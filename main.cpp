/***************************************/
/**     @author Francisco Cabeza      **/
/**      01/09/2022                   **/
/***************************************/
/** TODO - Realizar el giro del bloque **
 * Implementar el método rompeFila()   **
 ***************************************/ 
/***************************************/

#include <iostream>
#include <conio.h>

#include "Classes/Vector2.h"
#include "Classes/Game.h"

using namespace std;

int main()
{
   Game juego;

   juego.start();

   cout << "El juego ha terminado..." << endl;

   _getch();

   return EXIT_SUCCESS;
} // fin de la función main