#ifndef BRICK_HPP_INCLUDED
#define BRICK_HPP_INCLUDED

#include <SFML/Graphics/RectangleShape.hpp>

class Brick : public sf::RectangleShape
{
public:
    static float generation;
    static unsigned layers;
    static unsigned x;
    static unsigned y;
};

#endif // BRICK_HPP_INCLUDED
