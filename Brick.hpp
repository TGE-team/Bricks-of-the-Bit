#ifndef BRICK_HPP_INCLUDED
#define BRICK_HPP_INCLUDED

class Brick : public sf::RectangleShape
{
public:
    static float generation;
    static unsigned layers;
    static unsigned x;
    static unsigned y;
};
float Brick::generation = 0.f;
unsigned Brick::layers = 2;
unsigned Brick::x = 0;
unsigned Brick::y = 0;
#endif // BRICK_HPP_INCLUDED
