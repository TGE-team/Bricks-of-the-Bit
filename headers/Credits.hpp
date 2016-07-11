#ifndef CREDITS_HPP
#define CREDITS_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

inline unsigned char operator "" _uc(unsigned long long int i)
{
	return static_cast<unsigned char>(i);
}

void credits(sf::RenderWindow&, sf::Font&, sf::Texture);

#endif // CREDITS_HPP
