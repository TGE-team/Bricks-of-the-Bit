#ifndef BALL_HPP_INCLUDED
#define BALL_HPP_INCLUDED

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Ball                 //Klasa piłki
    : public sf::Drawable  //Dziedziczy po sf::Drawable
{
private:
    sf::RectangleShape shape; //Właściwa piłka wyświetlana na ekranie
    sf::Vector2f momentum;    //Pęd
    float radiaus;            //Promień piłki
public:
    Ball();                                                         //Konstruktor domyślny, jedynym zadaniem jest pozwolenie na stworzenie obiektu bez parametrów, taki obiekt nie może być wykorzystywany w przydatny sposób
    Ball(float ,float, sf::Vector2f, sf::Color, sf::Texture * tx);  //Konstruktor tworzący właściwą piłkę, brak odpowaidającej metody create(...) z uwagi na pełną poprawność Ball b = Ball(...)

    void move(sf::Time t);                                      //Automatyczne poruszanie się piłki na podstawie pędu
    void update(sf::FloatRect);                                 //Kolizja z ramkami okna
    bool collision(sf::RectangleShape& box, float acceleration = 1.f, sf::Vector2f accelerate = sf::Vector2f(0, 0));   //Kolizje ze wszystkim dziedziczącym po sf::RectangleShape lub nim samym

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const; //Funkcja z sf::Drawable, niezbędna do window.draw(instancja_klasy_Ball)

    float getRadius();
    sf::Vector2f getPosition();

    sf::Vector2f getMomentum();
};

#endif
