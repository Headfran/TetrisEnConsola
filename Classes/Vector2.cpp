// Definición de las funciones miembro de la clase Vector2
#include "Vector2.h"

// constantes
const Vector2 Vector2::ZERO = Vector2( 0, 0 );
const Vector2 Vector2::RIGHT = Vector2( 1, 0 );
const Vector2 Vector2::LEFT = Vector2( -1, 0 );
const Vector2 Vector2::UP = Vector2( 0, -1 );
const Vector2 Vector2::DOWN = Vector2( 0, 1 );

ostream &operator<<( ostream &out, const Vector2 &pVec )
{
   out << '(' << pVec.x << ", " << pVec.y << ')';
   return out;
} // fin de la función operator<<