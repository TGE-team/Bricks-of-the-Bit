#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.hpp"

using namespace std;

int main()
{
    srand(time(NULL));

    Game game;
    game.window.create(sf::VideoMode(800, 600), "Brick Breaker");
    game.window.setFramerateLimit(60);

    game.mainLoop();

    return 0;
}
