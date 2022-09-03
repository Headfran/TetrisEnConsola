// Definición de la clase que controla el juego
#ifndef GAME_H
#define GAME_H

#define HEIGHT 19
#define WIDTH 15

#include <memory> // para usar smart pointers

#include "Bloque.h"
#include "Timer.h"
#include "Vector2.h"

class Game {
public:
   Game(); // constructor predeterminado
   ~Game(); // destructor

   void start();  // comienza el juego
   void gameLoop(); // Ejecuta y mantiene el juego activo
   void input();  // encargada de los eventos de teclado
   void update();   // actualiza el estado del escenario
   void romperFila(); // verifica si hay una fila completa, si la hay, la rompe (no implementada aún)

   // funciones predicado
   void gameOver(); // encargada de terminar el juego

   void draw() const;   // pinta el tablero

private:
   // define cómo se dibujará el bloque en pantalla
   enum class ActionWithBlock : int {
      DRAW = 1,
      STICKY = 2,
      UNDRAW = ' '
   };
   // define el tipo de colisión que ocurre con los bloques
   enum class CollisionType {
      LEFT_WALL,
      RIGHT_WALL,
      FLOOR,
      WITH_BLOCK,
      WITH_BLOCK_HOR,
      NONE
   };

   int escenario[ HEIGHT ][ WIDTH ];

   std::shared_ptr< Bloque > pBlock; // apuntador a los bloques que se creen
   std::shared_ptr< Timer > pTemp; // apuntador al temporizador principal
   Vector2 mueve; // vector de movimiento del Bloque
   bool perdio;
   bool salir;

   // funciones de utilidad
   Game::CollisionType placeMeeting( int = 0 );  // verifica si ha habido alguna colisión con el bloque
   void drawBlock( ActionWithBlock ); // dibuja un bloque
};

#endif // GAME_H