#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

class Player                    //Klasa Player
    : public sf::RectangleShape //Dziedziczy po sf::RectangleShape, sama dodaje tylko kilka pomocniczych składowych publicznych.
{
public:
    sf::Uint8  ballsLeft;       //Pozostałe piłki
    sf::Uint16 points;          //Punkty
    sf::Uint8  combo;           //"Combo" - ilość zniszczonych prostokątów, zerowane po odbiciu od gracza albo zniszczeniu piłki, używane przy dodawaniu punktów
};

#endif // PLAYER_HPP_INCLUDED
