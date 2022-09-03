// Definición de la clase Bloque
#ifndef BLOQUE_H
#define BLOQUE_H

#include "Vector2.h"

class Game;

class Bloque {
   friend class Game;
public:
   Bloque();   // constructor predeterminado
   ~Bloque();  // destructor

   void generarBloque(); // genera un bloque
   void mover( Vector2 );  // mueve las coordenadas del bloque

private:
   Vector2 nBlock[ 4 ]; // contiene la forma del bloque
};

#endif // BLOQUE_H