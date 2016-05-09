#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Ball.hpp"
#include "Brick.hpp"
#include "Player.hpp"
#include "toString.hpp"

#include "QSFML/qresourcestream.hpp"
#include <array>

class Game //Klasa odpowiadająca za rozgrywkę
{
private:
    sf::RectangleShape deathSpace;      //Obszar niszczenia spadających piłek
    std::vector<Brick> bricks;          //Cegły do zniszczenia
    Player             player;          //Gracz
    Ball               ball;            //Piłka

    sf::Font           bitFont;         //Czcionka BitFont
    sf::Text           comboText;       //Informacja o obecnym "combo"
    sf::Text           pointsText;      //Informacja o ilości punktów
    sf::Text           continueText;    //Informacja wyświetlana po zniszczeniu piłki
    sf::Text           ballsLeftText;   //Informacja o ilości pozostałych piłek

    qsf::QResourceStream fontStream;    //Strumień do wczytywania czcionki z zasobów

public:
    static sf::Texture        brickTexture;    //Textura cegiełek
    static sf::Texture        ballTexture;     //Tekstura piłek

    sf::Font          &font = bitFont;
    sf::RenderWindow window;            //Okno aplikacji
    std::array<sf::Color, 4> colors;    //Kolory

    Game();                             //Domyślny konstruktor
    uint16_t mainLoop();                //Główna pętla gry
};
sf::Texture Game::brickTexture;
sf::Texture Game::ballTexture;

Game::Game()
{
    colors = {
        sf::Color(255, 0, 0),
        sf::Color(255, 255, 0),
        sf::Color(0, 255, 0),
        sf::Color(0, 0, 255)
    };

    player.setTexture(&brickTexture);
    player.setSize(sf::Vector2f(61, 11));          //Ustawienie rozmiaru gracze
    player.setFillColor(sf::Color(20, 20, 200));   //Ustawienie koloru wypełnienia gracza
    player.setOutlineColor(sf::Color(0, 0, 255));  //Ustawienie koloru obramowania gracza
    player.setOutlineThickness(3.f);               //Ustawienie grubości obramowania gracza
    player.setOrigin(30, 5);                       //Wysrodkowanie gracza

    bitFont.loadFromStream(fontStream("://bitfont.ttf")); //Wczytanie czcionki z zasobów

    //Utworzenie wszystkich tekstów (ustawienie czcionki, rozmiaru i koloru)
    pointsText.setFont(bitFont);                                          //
    pointsText.setCharacterSize(38);                                      //
    pointsText.setColor(sf::Color(255, 255, 0));                          //
                                                                          //
    comboText.setFont(bitFont);                                           //
    comboText.setCharacterSize(32);                                       //
    comboText.setColor(sf::Color(255, 255, 0));                           //
                                                                          //
    continueText.setFont(bitFont);                                        //
    continueText.setCharacterSize(45);                                    //
    continueText.setColor(sf::Color(255, 255, 0));                        //
                                                                          //
    ballsLeftText.setFont(bitFont);                                       //
    ballsLeftText.setCharacterSize(32);                                   //
    ballsLeftText.setColor(sf::Color(255, 255, 0));                       //
    //======================================================================

    deathSpace.setFillColor(sf::Color(250, 20, 20, 250)); //Ustawienie koloru prostokąta reprezentujacego obszar niszczenia piłek
}
uint16_t Game::mainLoop()
{
    player.ballsLeft = 3;                          //Ustawienie ilosci pozostałych piłek
    player.points = 0;                             //Wyzerowanie punktów
    player.combo = 0;                              //Wyzerowanie "combo"

    deathSpace.setSize(sf::Vector2f(window.getView().getSize().x, 40));
    deathSpace.setOrigin(0, 40);
    deathSpace.setPosition(0, window.getView().getSize().y);
    player.setPosition(sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y - 40));

    ball = Ball(10.f, sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y / 2.f), colors[rand() % colors.size()], &ballTexture);

    sf::Clock frameClock;
    bool exit = false;
    bool ready = false;

    Brick::x = 1;
    Brick::y = 3;
    for(sf::Time frameTime; window.isOpen() and !exit; frameTime = frameClock.restart())
    {
        if(!ready and Brick::generation >= 0.1f)
        {
            bricks.push_back(Brick());
            bricks.back().setTexture(&brickTexture);
            bricks.back().setFillColor(colors[Brick::y - 3]);
            bricks.back().setPosition(Brick::x * 95 - 72, Brick::y * 30);
            bricks.back().setSize(sf::Vector2f(91, 21));

            Brick::x++;
            if(Brick::y == 2 + Brick::layers and Brick::x == 9)
                ready = true;
            else if(Brick::x == 9)
            {
                Brick::y++;
                Brick::x = 1;
            }

            Brick::generation = 0.f;
        }
        else
            Brick::generation += frameTime.asSeconds();

        for(sf::Event ev; window.pollEvent(ev);)
        {
            if(ev.type == sf::Event::Closed)
            {
                window.close();
                ::exit(0);
            }
        }

        window.clear(sf::Color(20, 20, 20));

        window.draw(deathSpace);

        sf::Vector2f diff = player.getPosition();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and player.getPosition().x + (player.getSize().x / 2.f) < window.getView().getSize().x - 10)
            player.move(frameTime.asSeconds() / (1.f / +300.f), 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and player.getPosition().x - (player.getSize().x / 2.f) > 10.f)
            player.move(frameTime.asSeconds() / (1.f / -300.f), 0);
        diff -= player.getPosition();
        window.draw(player);

        pointsText.setString("points: " + toString(player.points));
        pointsText.setPosition(window.getView().getSize().x / 2.f - (pointsText.getGlobalBounds().width / 2.f), 0);

        comboText.setString("combo: " + toString((int) player.combo + 1) + "x");
        comboText.setPosition(window.getView().getSize().x / 10.f * 9.f - (pointsText.getGlobalBounds().width / 2.f), 0);

        ballsLeftText.setString("balls left: " + toString(player.ballsLeft - 1));
        ballsLeftText.setPosition(10, 0);

        window.draw(ballsLeftText);
        window.draw(pointsText);
        window.draw(comboText);

        ball.update(sf::FloatRect(0, 0, window.getView().getSize().x, window.getView().getSize().y));
        if(ball.collision(player, 1.02f, diff / -4.f))
            player.combo = 0;

        for(size_t i = 0; i < bricks.size(); i++)
        {
            window.draw(bricks[i]);
            if(ball.collision(bricks[i], 1.02f))
            {
                bricks.erase(bricks.begin() + i);
                player.points += player.combo + 1;
                player.combo++;
            }
        }
        if(ball.collision(deathSpace))
        {
            ball = Ball(10.f, sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y / 2.f), colors[rand() % colors.size()], &ballTexture);
            player.setPosition(sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y - 40));
            player.combo = 0;

            player.ballsLeft--;
            if(player.ballsLeft == 0)
                exit = true;
            else
            {
                sf::Image   screenshot = window.capture();
                sf::Texture screenshotT;
                screenshotT.loadFromImage(screenshot);
                sf::Sprite  screenshotS(screenshotT);
                screenshotS.setPosition(0, 0);

                continueText.setString("Press [enter] to start!");
                continueText.setPosition(window.getView().getSize().x / 2.f - (pointsText.getGlobalBounds().width + 80),
                                         window.getView().getSize().y / 2.f - (pointsText.getGlobalBounds().height / 2.f));

                for(bool clicked = false; !clicked;)
                {
                    window.draw(screenshotS);
                    window.draw(continueText);
                    window.display();

                    for(sf::Event ev; window.pollEvent(ev);)
                        if(ev.type == sf::Event::KeyPressed and ev.key.code == sf::Keyboard::Return)
                            clicked = true;

                    frameClock.restart();
                }
            }
        }
        else if(bricks.size() == 0 and ready)
        {
            ready = false;
            ball = Ball(10.f, sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y / 2.f), colors[rand() % colors.size()], &ballTexture);
            player.ballsLeft++;
            Brick::x = 1;
            Brick::y = 3;
            if(Brick::layers < 4)
                Brick::layers++;
        }

        if(ready)
            ball.move(frameTime);
        window.draw(ball);

        window.display();
    }

    bricks.clear();
    return player.points;
}

#endif // GAME_HPP_INCLUDED
