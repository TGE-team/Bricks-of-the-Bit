#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Ball.hpp"
#include "Brick.hpp"
#include "Player.hpp"
#include "toString.hpp"

#include "QSFML/qresourcestream.hpp"
#include <array>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

class Game //Klasa odpowiadająca za rozgrywkę
{
private:
    std::vector<Brick> bricks;          //Cegły do zniszczenia
    Player             player;          //Gracz
    Ball               ball;            //Piłka

    bool               backgroundOffsetRight;
    float              backgroundOffset;
    sf::Clock          backgroundTimer;
    sf::Sprite         background;

    float level;

    sf::Sprite         framesSprite;

    sf::Font           bitFont;         //Czcionka BitFont
    sf::Text           comboText;       //Informacja o obecnym "combo"
    sf::Text           pointsText;      //Informacja o ilości punktów
    sf::Text           continueText;    //Informacja wyświetlana po zniszczeniu piłki
    sf::Text           ballsLeftText;   //Informacja o ilości pozostałych piłek
    sf::RectangleShape continueTextRect;

    sf::Texture        blurTexture;

    qsf::QResourceStream fontStream;    //Strumień do wczytywania czcionki z zasobów

public:
    static sf::Texture        brickTexture;    //Textura cegiełek
    static sf::Texture        ballTexture;     //Tekstura piłek
    static sf::Texture        backgroundTexture;
    static sf::Texture        framesTexture;

    sf::Font          &font = bitFont;
    sf::RenderWindow window;            //Okno aplikacji
    std::array<sf::Color, 4> colors;    //Kolory

    Game();                             //Domyślny konstruktor
    uint16_t mainLoop();                //Główna pętla gry
};

#endif // GAME_HPP_INCLUDED
