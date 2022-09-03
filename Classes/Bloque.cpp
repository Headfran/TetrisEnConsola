// Definición de las funciones miembro de la clase Bloque
#include <cstdlib>
#include <ctime>

#include "Bloque.h"
#include "Vector2.h"

// constructor que inicializa el objeto bloque
Bloque::Bloque()
{
   generarBloque();
} // fin del constructor

// destructor
Bloque::~Bloque()
{

} // fin de destructor

// función que genera un bloque de manera aleatoria
void Bloque::generarBloque()
{
   // contiene las coordenadas de los 7 bloques entre los cuales se elegirá uno
   static Vector2 bloques[ 7 ][ 4 ] = {
           { { 3, 1 }, { 4, 1 }, { 3, 2 }, { 4, 2 } },
           { { 3, 1 }, { 3, 2 }, { -1, -1 }, { -1, -1 } },
           { { 2, 1 }, { 3, 1 }, { 4, 1 }, { 5, 1 } },
           { { 3, 1 }, { 4, 1 }, { 4, 2 }, { -1, -1 } },
           { { 3, 1 }, { 3, 2 }, { 3, 3 }, { 4, 2 } },
           { { 3, 1 }, { 3, 2 }, { 3, 3 }, { 4, 1 } },
           { { 3, 1 }, { 4, 1 }, { 4, 2 }, { 4, 3 } }
   };

   // genera un número aleatorio para seleccionar un bloque
   int numero = rand() % 7;

   for ( int i = 0; i < 4; i++ ) {
      nBlock[ i ] = bloques[ numero ][ i ];
   } // fin de for
} // fin de la función generarBloque

// función que mueve el bloque verticalmente
void Bloque::mover( Vector2 move )
{
   for ( int i = 0; i < 4; i++ ) {
      // solo para bloques con menos de 4 partes.
      if ( nBlock[ i ] == -1 ) { break; }

      nBlock[ i ] = nBlock[ i ] + move;
   } // fin de for
} // fin de la función mover