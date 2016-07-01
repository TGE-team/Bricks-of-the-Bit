#include "Ball.hpp"

Ball::Ball() { }
Ball::Ball(float radiaus, float speedMod, sf::Vector2f pos, sf::Color color, sf::Texture * tx)
{
    if(tx != NULL)
        shape.setTexture(tx, false);
    shape.setFillColor(color);
    shape.setSize(sf::Vector2f(2 * radiaus + 1, 2 * radiaus + 1));
    shape.setOrigin(radiaus, radiaus);
    shape.setPosition(pos);                                                                    //UStawienie początkowej pozycji
    shape.setOrigin(radiaus, radiaus);                                                         //Wyśrodkowanie piłki

    this -> radiaus = radiaus;                                                                 //Zapisanie promienia w osobnej zmiennej, przydatne podczas dalszych obliczeń

    momentum = sf::Vector2f(rand() % 2 * 2 - 1, -1);                                           //Nadanie (w pewnym stopniu) losowego pedu
    momentum *= 3.f;                                                                           //Zwielokrotnienie pędu (możliwe zmiany)
    momentum *= speedMod;
}

void Ball::move()
{
    shape.move(momentum * lastTimeMod);
}
void Ball::update(sf::FloatRect rect, sf::Time t)
{
    lastTimeMod = (t.asSeconds() / (1.f / 60.f));

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
bool Ball::collision(sf::RectangleShape& box, float acceleration, sf::Vector2f accelerate)
{
    sf::FloatRect rect = box.getGlobalBounds(); //Pobranie prostokąta obiektu typu sf::RectangleShape

    //Pomniejszenie ścian prostokątu o 2*radiaus i wyśrodkowanie
    rect.top    -= radiaus;                                   //
    rect.left   -= radiaus;                                   //
    rect.width  += radiaus * 2.f;                             //
    rect.height += radiaus * 2.f;                             //
    //==========================================================

    sf::Vector2f theoretical = shape.getPosition() + momentum * lastTimeMod * 1.05f;     //Teoretyczna pozycja, minimalnie różniąca się od tej w następnej klatce w przypadku braku kolizji
    auto changed = false;

    if(rect.contains(theoretical) and !rect.contains(shape.getPosition())) //Jeżeli doszłoby do kolizji, ale piłka nie jest w środku obiektu
    {
        //Ściany góra/dół==========================================================================
        if(momentum.y < 0                                                                        //
        and theoretical.y < rect.top + rect.height                                               //
        and shape.getPosition().x > rect.left and shape.getPosition().x < rect.left + rect.width)//
        {
            momentum.y = -momentum.y;                                                            //
            changed = true;
        }
                                                                                                 //
        else if(momentum.y > 0                                                                   //
        and theoretical.y > rect.top                                                             //
        and shape.getPosition().x > rect.left and shape.getPosition().x < rect.left + rect.width)//
        {
            momentum.y = -momentum.y;                                                            //
            changed = true;
        }
        //=========================================================================================

        //Ściany lewa/prawa=======================================================================
        if(momentum.x < 0                                                                       //
        and theoretical.x < rect.left + rect.width                                              //
        and shape.getPosition().y > rect.top and shape.getPosition().y < rect.top + rect.height)//
        {
            momentum.x = -momentum.x;                                                           //
            changed = true;
        }
                                                                                                //
        else if(momentum.x > 0                                                                  //
        and theoretical.x > rect.left                                                           //
        and shape.getPosition().y > rect.top and shape.getPosition().y < rect.top + rect.height)//
        {
            momentum.x = -momentum.x;                                                           //
            changed = true;
        }
        //========================================================================================

        momentum *= acceleration; //Przyspiesznie piłki
        momentum += accelerate / lastTimeMod;

        if(!changed)
            momentum = -momentum;

        return true;       //Potwierdzenie kolizji
    }

    return false;    //Informacja o braku kolizji
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const //Funkcja wywoływana podczas np. app.draw(pilka);
{
    target.draw(shape, states);                                          //Narysowanie na docelowym sf::RenderTarget (np. ekran) piłki
}

sf::Vector2f Ball::getMomentum()
{
    return momentum;
}

float Ball::getRadius()
{
    return radiaus;
}

sf::Vector2f Ball::getPosition()
{
    return shape.getPosition();
}
