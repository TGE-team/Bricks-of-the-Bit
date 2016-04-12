#ifndef BALL_HPP_INCLUDED
#define BALL_HPP_INCLUDED

#include <cstdlib>

class Ball                 //Klasa piłki
    : public sf::Drawable  //Dziedziczy po sf::Drawable
{
private:
    sf::CircleShape shape; //Właściwa piłka wyświetlana na ekranie
    sf::Vector2f momentum; //Pęd
    float radiaus;         //Promień piłki
public:
    Ball();                               //Konstruktor domyślny, jedynym zadaniem jest pozwolenie na stworzenie obiektu bez parametrów, taki obiekt nie może być wykorzystywany w przydatny sposób
    Ball(float, sf::Vector2f, sf::Color); //Konstruktor tworzący właściwą piłkę, brak odpowaidającej metody create(...) z uwagi na pełną poprawność Ball b = Ball(...)

    void move(sf::Time t);                //Automatyczne poruszanie się piłki na podstawie pędu
    void update(sf::FloatRect);           //Kolizja z ramkami okna
    bool collision(sf::RectangleShape&);  //Kolizje ze wszystkim dziedziczącym po sf::RectangleShape lub nim samym

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const; //Funkcja z sf::Drawable, niezbędna do window.draw(instancja_klasy_Ball)
};

Ball::Ball() { }
Ball::Ball(float radiaus, sf::Vector2f pos, sf::Color color)
{
    shape.setFillColor(color);
    shape.setRadius(radiaus);                                                                  //Ustawienie rozmiaru piłki
    shape.setPosition(pos);                                                                    //UStawienie początkowej pozycji
    shape.setOrigin(radiaus, radiaus);                                                         //Wyśrodkowanie piłki

    this -> radiaus = radiaus;                                                                 //Zapisanie promienia w osobnej zmiennej, przydatne podczas dalszych obliczeń

    momentum = sf::Vector2f(rand() % 2 * 2 - 1, rand() % 2 * 2 - 1);                           //Nadanie (w pewnym stopniu) losowego pedu
    momentum *= 3.f;                                                                           //Zwielokrotnienie pędu (możliwe zmiany)
}

void Ball::move(sf::Time t)
{
    shape.move(momentum * (t.asSeconds() / (1.f / 60.f)));
}
void Ball::update(sf::FloatRect rect)
{
    //Pomniejszenie ścian prostokątu o 2*radiaus i wyśrodkowanie
    rect.top    += radiaus;                                   //
    rect.left   += radiaus;                                   //
    rect.width  -= radiaus * 2.f;                             //
    rect.height -= radiaus * 2.f;                             //
    //==========================================================

    if(!rect.contains(shape.getPosition() + momentum)) //Wykrycie kolizji ze ścianami (opuszczenie wyznaczonego wcześniej prostokąta przez środek piłki)
    {
        if(shape.getPosition().x + momentum.x > rect.left + rect.width or shape.getPosition().x + momentum.x < rect.left) //W wypadku ściany bocznej
            momentum.x *= -1.f;                                                                                           //Odwrócenie pędu względem osi X
        if(shape.getPosition().y + momentum.y > rect.top + rect.height or shape.getPosition().y + momentum.y < rect.top)  //W wypadku ściany górnej/dolnej
            momentum.y *= -1.f;                                                                                           //Odwrócenie pędu względem osi Y
    }
}
bool Ball::collision(sf::RectangleShape& box)
{
    sf::FloatRect rect = box.getGlobalBounds(); //Pobranie prostokąta obiektu typu sf::RectangleShape

    //Pomniejszenie ścian prostokątu o 2*radiaus i wyśrodkowanie
    rect.top    -= radiaus;                                   //
    rect.left   -= radiaus;                                   //
    rect.width  += radiaus * 2.f;                             //
    rect.height += radiaus * 2.f;                             //
    //==========================================================

    sf::Vector2f theoretical = shape.getPosition() + momentum * 1.01f;     //Teoretyczna pozycja, minimalnie różniąca się od tej w następnej klatce w przypadku braku kolizji

    if(rect.contains(theoretical) and !rect.contains(shape.getPosition())) //Jeżeli doszłoby do kolizji, ale piłka nie jest w środku obiektu
    {
        //Ściany góra/dół==========================================================================
        if(momentum.y < 0                                                                        //
        and theoretical.y < rect.top + rect.height                                               //
        and shape.getPosition().x > rect.left and shape.getPosition().x < rect.left + rect.width)//
            momentum.y = -momentum.y;                                                            //
                                                                                                 //
        else if(momentum.y > 0                                                                   //
        and theoretical.y > rect.top                                                             //
        and shape.getPosition().x > rect.left and shape.getPosition().x < rect.left + rect.width)//
            momentum.y = -momentum.y;                                                            //
        //=========================================================================================

        //Ściany lewa/prawa=======================================================================
        if(momentum.x < 0                                                                       //
        and theoretical.x < rect.left + rect.width                                              //
        and shape.getPosition().y > rect.top and shape.getPosition().y < rect.top + rect.height)//
            momentum.x = -momentum.x;                                                           //
                                                                                                //
        else if(momentum.x > 0                                                                  //
        and theoretical.x > rect.left                                                           //
        and shape.getPosition().y > rect.top and shape.getPosition().y < rect.top + rect.height)//
            momentum.x = -momentum.x;                                                           //
        //========================================================================================


        momentum *= 1.02f; //Przyspiesznie piłki
        return true;       //Potwierdzenie kolizji
    }

    return false;    //Informacja o braku kolizji
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const //Funkcja wywoływana podczas np. app.draw(pilka);
{
    target.draw(shape, states);                                          //Narysowanie na docelowym sf::RenderTarget (np. ekran) piłki
}

#endif // BALL_HPP_INCLUDED
