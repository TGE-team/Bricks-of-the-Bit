#include "Brick.hpp"

Brick::Brick(Brick::Property prop)
: property { prop }
{ }

float Brick::generation = 0.f;
unsigned Brick::layers = 2;
unsigned Brick::x = 0;
unsigned Brick::y = 0;
