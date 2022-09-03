// Definición de la clase Vector2
#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

using std::ostream;

struct Vector2 {
   friend ostream &operator<<( ostream &, const Vector2 & );

   int x, y;   // coordenadas

   Vector2() { x = 0, y = 0; } // constructor predeterminado
   Vector2( int a, int b ) { x = a, y = b; }

   // constantes
   static const Vector2 ZERO;
   static const Vector2 RIGHT;
   static const Vector2 LEFT;
   static const Vector2 UP;
   static const Vector2 DOWN;

   inline int getX() const { return x; }
   inline int getY() const { return y; }

   // sobrecarga de operadores para manipular Vectores
   inline Vector2 &operator+( const Vector2 &c ) { 
      x = x + c.x; 
      y = y + c.y;
      return *this; // permite las llamadas en cascada
   }
   inline Vector2 &operator-( const Vector2 &c ) { 
      x -= c.x; 
      y -= c.y; 
      return *this; // permite las llamadas en cascada
   }
   inline const Vector2 &operator=( const Vector2 &c ) {
      // impide la autoasignación
      if ( this != &c ) {
         x = c.x;
         y = c.y;
         return *this; // permite la cascada
      } 
   }
   inline bool operator==( const Vector2 &c ) {
      return ( x == c.x && y == c.y );
   }
   inline bool operator==( int n ) { return ( x == n && y == n ); }
   inline bool operator!=( const Vector2 &c ) {
      return !( *this == c );
   }
};

#endif // VECTOR2_H