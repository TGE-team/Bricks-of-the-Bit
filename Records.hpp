#ifndef RECORDS_HPP_INCLUDED
#define RECORDS_HPP_INCLUDED

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "Leaderboards.hpp"
#include "toString.hpp"

void records(sf::RenderWindow & app, uint16_t score, sf::Font & font, bool save = true);

#endif // RECORDS_HPP_INCLUDED
