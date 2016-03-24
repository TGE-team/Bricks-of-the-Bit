#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Ball.hpp"
#include "Brick.hpp"
#include "Player.hpp"
#include "toString.hpp"

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
public:
    sf::RenderWindow window;            //Okno aplikacji

    Game();                             //Domyślny konstruktor
    void mainLoop();                    //Główna pętla gry
};

Game::Game()
{
    player.setSize(sf::Vector2f(61, 11));          //Ustawienie rozmiaru gracze
    player.setFillColor(sf::Color(20, 20, 200));   //Ustawienie koloru wypełnienia gracza
    player.setOutlineColor(sf::Color(0, 0, 255));  //Ustawienie koloru obramowania gracza
    player.setOutlineThickness(3.f);               //Ustawienie grubości obramowania gracza
    player.setOrigin(30, 5);                       //Wysrodkowanie gracza
    player.ballsLeft = 3;                          //Ustawienie ilosci pozostałych piłek
    player.points = 0;                             //Wyzerowanie punktów
    player.combo = 0;                              //Wyzerowanie "combo"

    bitFont.loadFromFile("assets/bitfont.ttf");    //Wczytanie czcionku z pliku

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

    deathSpace.setFillColor(sf::Color(230, 20, 20, 170)); //Ustawienie koloru prostokąta reprezentujacego obszar niszczenia piłek
}
void Game::mainLoop()
{
    deathSpace.setSize(sf::Vector2f(window.getView().getSize().x, 40));
    deathSpace.setOrigin(0, 40);
    deathSpace.setPosition(0, window.getView().getSize().y);
    player.setPosition(sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y - 40));

    ball = Ball(10.f, sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y / 2.f));

    for(int x = 1; x < 9; x++)
    for(int y = 3; y < 7; y++)
    {
        bricks.push_back(Brick());

        sf::Color color(rand() % 155 + 100, rand() % 155 + 100, rand() % 155 + 100);
        bricks.back().setFillColor(color);
        bricks.back().setPosition(x * 95 - 72, y * 30);
        bricks.back().setSize(sf::Vector2f(91, 21));
    }

    sf::Clock frameClock;
    for(sf::Time frameTime; window.isOpen(); frameTime = frameClock.restart())
    {
        for(sf::Event ev; window.pollEvent(ev);)
        {
            if(ev.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(20, 20, 20));

        window.draw(deathSpace);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and player.getPosition().x + (player.getSize().x / 2.f) < window.getView().getSize().x - 10)
            player.move(frameTime.asSeconds() / (1.f / +300.f), 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and player.getPosition().x - (player.getSize().x / 2.f) > 10.f)
            player.move(frameTime.asSeconds() / (1.f / -300.f), 0);
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
        if(ball.collision(player))
            player.combo = 0;

        for(size_t i = 0; i < bricks.size(); i++)
        {
            window.draw(bricks[i]);
            if(ball.collision(bricks[i]))
            {
                bricks.erase(bricks.begin() + i);
                player.points += player.combo + 1;
                player.combo++;
            }
        }
        if(ball.collision(deathSpace))
        {
            ball = Ball(10.f, sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y / 2.f));
            player.setPosition(sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y - 40));
            player.combo = 0;

            player.ballsLeft--;
            if(player.ballsLeft == 0)
                window.close();
            else
            {
                sf::Image   screenshot = window.capture();
                sf::Texture screenshotT;
                screenshotT.loadFromImage(screenshot);
                sf::Sprite  screenshotS(screenshotT);
                screenshotS.setPosition(0, 0);

                continueText.setString("Press [enter] to start");
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
                }
            }
        }

        ball.move();
        window.draw(ball);

        window.display();
    }
}

#endif // GAME_HPP_INCLUDED
