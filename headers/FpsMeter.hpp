#ifndef FPSMETER_H
#define FPSMETER_H

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class FpsMeter
	: public sf::Text
{
	unsigned int frames;
	sf::Clock clock;
public:
	using sf::Text::Text;

	FpsMeter()
		: frames { 0 }
	{ }
	void update();
};

#endif // FPSMETER_H
