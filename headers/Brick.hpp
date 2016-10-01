#ifndef BRICK_HPP_INCLUDED
#define BRICK_HPP_INCLUDED

#include <SFML/Graphics/RectangleShape.hpp>

class Brick
: public sf::RectangleShape
{
public:
	enum Property
	{
		NONE,
		BONUS,
		RESISTANT,
		EXPLOSIVE,
		RANDOM_EXPLOSIVE
	};

	Brick(Property = NONE);

	static float generation;
	static unsigned layers;
	static unsigned x;
	static unsigned y;

	Property property;
};

#endif // BRICK_HPP_INCLUDED
