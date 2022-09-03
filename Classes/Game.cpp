// Definición de funciones miembro de Game
#include <windows.h> // para Sleep
#include <conio.h> // para kbhit
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

#include "Game.h"

// constructor inicializa el arreglo de elementos
Game::Game() : perdio( false ), salir( false )
{
   // establece una semilla aleatoria
   std::srand( std::time( NULL ) );

   // inicializa el escenario y las paredes.
   for ( int i = 0; i < HEIGHT; i++ ) {
      for ( int j = 0; j < WIDTH; j++ ) {

         if ( i == 0 || i == HEIGHT - 1 )
            escenario[ i ][ j ] = 205;
         else if ( j == 0 || j == WIDTH - 1 )
            escenario[ i ][ j ] = 186;
         else
            escenario[ i ][ j ] = 0;
         
      } // fin de for interno
   } // fin de for externo

   escenario[ 0 ][ 0 ] = 201; // esquina superior izquierda
   escenario[ 0 ][ WIDTH - 1 ] = 187; // esquina superior derecha
   escenario[ HEIGHT - 1 ][ 0 ] = 200; // esquina inferior izquierda
   escenario[ HEIGHT - 1 ][ WIDTH - 1 ] = 188; // esquina inferior derecha

   mueve = Vector2::ZERO; // no se ha presionado ninguna tecla
   pTemp = nullptr; // no está apuntando a ningún apuntador
   pBlock = nullptr; // inicializa el apuntador a bloque
} // fin del constructor

// destructor
Game::~Game()
{
} // fin del destructor

// función que comienza el loop del juego
void Game::start()
{
   pTemp = std::make_shared< Timer >(); // crea una instancia temporizador
   pTemp->init( 1 ); // comienza el temporizador en un segundo

   gameLoop(); // ejecuta el loop del juego
} // fin de la función start

// función que mantiene el juego en marcha
void Game::gameLoop()
{
   // crea una instancia de un bloque al iniciar el juego
   pBlock = std::make_shared< Bloque >();

   // se ejecuta el ciclo mientras no haya gameOver o se haya marcado fin de juego
   while ( !perdio && !salir ) { 
      // refresca la pantalla
      system( "cls" );

      // obtiene el estado del teclado.
      input();

      // actualiza la escena, moviendo el bloque si se da el estado.
      update();
      
      // verifica si se ha perdido el juego.
      gameOver();

      // dibuja el nuevo escenario
      draw();

      // espera 10 milisegundos antes de ejecutar
      Sleep( 10 );

      // actualiza el temporizador
      pTemp->update();

      // verifica si el temporizador se ha terminado para ejecutar mover el bloque hacia abajo
      if ( pTemp->is_ended() ) {
         mueve = Vector2::DOWN;
         pTemp->init( 1 ); // reinicia el temporizador
      } // fin de if
      // sino, reestablece el estado del Vector a cero
      else {
         mueve = Vector2::ZERO;
      } // fin de else
   } // fin de while
} // fin de la función gameLoop

// función que detecta cualquier momento en que se presiona alguna tecla
void Game::input()
{
   if ( kbhit() ) {
      int key = getch();

      switch( key ) {
         case '6':
            mueve = ( mueve == Vector2::DOWN ) ? Vector2( 1, 1 ) : Vector2::RIGHT;
            break;

         case '4':
            mueve = ( mueve == Vector2::DOWN ) ? Vector2( -1, 1 ) : Vector2::LEFT;
            break;

         case '2':
            mueve = Vector2::DOWN;
            break;
      } // fin de switch
   } // fin de if
} // fin de la función input

// función que actualiza la posición del bloque
void Game::update()
{
   CollisionType colision;
   ActionWithBlock drawingType = ActionWithBlock::DRAW;

   // si ha habido una colisión, dependiendo del tipo realiza una acción diferente
   if ( ( colision = placeMeeting() ) != CollisionType::NONE ) {

      switch( colision ) {
         // si ha colisionado con paredes horizontales, anula el movimiento horizontal
         case CollisionType::LEFT_WALL:
         case CollisionType::RIGHT_WALL:
         case CollisionType::WITH_BLOCK_HOR:
            mueve = Vector2( mueve.getX() - mueve.getX(), mueve.getY() );
            break;

         // si ha colisionado con el suelo o con un bloque. Anula el movimiento horizontal
         case CollisionType::FLOOR:
         case CollisionType::WITH_BLOCK:
            drawingType = ActionWithBlock::STICKY;

            mueve = Vector2::ZERO;
            // código para eliminar filas, si están llenas.
            break;

      } // fin de switch

   } // fin de if

   drawBlock( ActionWithBlock::UNDRAW );
   pBlock->mover( mueve );
   drawBlock( drawingType );

   // Pega, elimina el bloque y crea uno nuevo
   if ( drawingType == ActionWithBlock::STICKY ) {
      pBlock.reset(); // destruye el bloque
      pBlock = std::make_shared< Bloque >(); // crea uno nuevo
   } // fin de if

} // fin de la función update

// función que verifica si se ha perdido el juego
void Game::gameOver()
{
   for ( int i = 0; i < 4; i++ ) {
      if ( pBlock->nBlock[ i ] == -1 ) { break; } // se acabarón los componentes

      // si se dibuja un bloque sobre un bloque pegado y estamos en la fila 1, hemos perdido
      if ( escenario[ pBlock->nBlock[ i ].getY() ][ pBlock->nBlock[ i ].getX() ] == 2 ) {
         perdio = true;
         drawBlock( ActionWithBlock::DRAW );
         return;
      } // fin de if
   } // fin de for
} // fin de la función gameOver

// función que dibuja el tablero
void Game::draw() const
{
   for ( int i = 0; i < HEIGHT; i++ ) {
      for ( int j = 0; j < WIDTH; j++ ) {
         cout << ( escenario[ i ][ j ] == 1 || escenario[ i ][ j ] == 2 ? '#' : static_cast< char >( escenario[ i ][ j ] ) );
      } // fin de for interno
      cout << endl;
   } // fin de for externo
} // fin de la función draw

// verifica si el objeto bloque ha colisionado con otro bloque o una pared
Game::CollisionType Game::placeMeeting( int distancia )
{
   // verifica cada componente del bloque por colisión
   for ( int i = 0; i < 4; i++ ) {
      if ( pBlock->nBlock[ i ] == -1 ) { break; } // se acabarón los componentes

      // colisión con pared horizontal izquierda
      if ( pBlock->nBlock[ i ].getX() + mueve.getX() + distancia <= 0 )
         return CollisionType::LEFT_WALL;

      // colisión con pared horizontal derecha
      if ( pBlock->nBlock[ i ].getX() + mueve.getX() + distancia >= WIDTH - 1 )
         return CollisionType::RIGHT_WALL;

      if ( escenario[ pBlock->nBlock[ i ].getY() ][ pBlock->nBlock[ i ].getX() + mueve.getX() + distancia ] == 2 )
         return CollisionType::WITH_BLOCK_HOR;

      // colisiones con piso
      if ( pBlock->nBlock[ i ].getY() + mueve.getY() + distancia >= HEIGHT - 1 )
         return CollisionType::FLOOR;

      // colisiones con otros bloques
      if( escenario[ pBlock->nBlock[ i ].getY() + mueve.getY() + distancia ][ pBlock->nBlock[ i ].getX() ] == 2 )
         return CollisionType::WITH_BLOCK;

   } // fin de for

   return CollisionType::NONE;
} // fin de la función placeMeeting

// función de utilidad: dibuja un bloque en el escenario
void Game::drawBlock( ActionWithBlock draw )
{
   for ( int i = 0; i < 4; i++ ) {
      // termina tan pronto intenta dibujar un componente inexistente
      if ( pBlock->nBlock[ i ] == -1 ) { break; }

      escenario[ pBlock->nBlock[ i ].getY() ][ pBlock->nBlock[ i ].getX() ] = static_cast< int >( draw );
   } // fin de for interno
} // fin de la función drawBlock