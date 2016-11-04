#ifndef BRICK_HPP_INCLUDED
#define BRICK_HPP_INCLUDED

#include <SFML/Graphics/RectangleShape.hpp>

class Brick
: public sf::RectangleShape
{
public:
	enum Property
	{
		NONE = 0,
		BONUS,
		EXPLOSIVE,
		RESISTANT_3,
		RESISTANT_2,
		RESISTANT_1,
		RANDOM_EXPLOSIVE,
		COUNT //Not a real type
	};

	Brick(Property = NONE);

	static float generation;
	static unsigned layers;
	static unsigned x;
	static unsigned y;

	Property property;
};

#endif // BRICK_HPP_INCLUDED
