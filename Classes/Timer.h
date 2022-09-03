// Definición de la clase Timer, que contará el tiempo necesario para mover el bloque hacia abajo
#ifndef TIMER_H
#define TIMER_H

#include <ctime>

class Timer {
public:
   Timer() {} // Constructor
   ~Timer() {} // Destructor

   void init( time_t temp_duration ); // comienza el temporizador
   void update(); // actualiza el estado del temporizador

   inline bool is_ended() const { return ( deltaTime >= temp ); } // verifica si se ha acabado el tiempo

private:
   std::time_t temp;
   std::time_t initialTime; // marca el tiempo inicial
   std::time_t deltaTime;  // dice la diferencia del tiempo entre dos invervalos
   std::time_t finalTime; // se marca al pasar una cierta cantidad tiempo
};

#endif // TIMER_H