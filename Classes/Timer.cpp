// Definición de las funciones miembro Timer
#include "Timer.h"

// inicializa los elementos del timer y los marca
void Timer::init( time_t temp_duration )
{
   initialTime = std::time( NULL );
   finalTime = 0;
   deltaTime = 0;
   temp = temp_duration;
} // fin de la función init

// Actualiza el tiempo y devuelve la diferencia de este
void Timer::update()
{
   // marca el tiempo
   finalTime = std::time( NULL );

   // obtiene la diferencia del tiempo
   deltaTime = finalTime - initialTime;

   // actualiza el tiempo del temporizador
   //temp -= deltaTime;

} // fin de la función update