#ifndef MAINMENU_HPP_INCLUDED
#define MAINMENU_HPP_INCLUDED

void mainMenu()
{
    Game game;
    game.window.create(sf::VideoMode(800, 600), "Brick Breaker");
    game.window.setFramerateLimit(120);
    sf::RenderWindow & app = game.window;

    const unsigned BUTTONS = 2;
    sf::RectangleShape buttons[BUTTONS];
    sf::Text           texts[BUTTONS];

    //Uruchamianie gry
    buttons[0].setOutlineThickness(3.f);
    buttons[0].setSize(sf::Vector2f(300, 70));
    buttons[0].setOrigin(buttons[0].getSize() / 2.f);
    buttons[0].setPosition(sf::Vector2f(app.getSize().x / 2, app.getSize().y / 2 - 120));

    texts[0].setString("Play!");
    texts[0].setFont(game.font);
    texts[0].setCharacterSize(90);
    texts[0].setColor(sf::Color(255, 255, 0));
    texts[0].setPosition(buttons[0].getPosition() + sf::Vector2f(-75, -63));
    //================

    //Wyjście z gry
    buttons[1].setOutlineThickness(2.f);
    buttons[1].setSize(sf::Vector2f(200, 50));
    buttons[1].setOrigin(buttons[1].getSize() / 2.f);
    buttons[1].setPosition(sf::Vector2f(app.getSize().x / 2, app.getSize().y / 2 + 120));

    texts[1].setString("Exit");
    texts[1].setFont(game.font);
    texts[1].setCharacterSize(70);
    texts[1].setColor(sf::Color(255, 255, 0));
    texts[1].setPosition(buttons[1].getPosition() + sf::Vector2f(-40, -48));
    //=============

    for(bool exit = false; !exit and app.isOpen();)
    {
        for(sf::Event ev; app.pollEvent(ev);)
        {
            if(ev.type == sf::Event::Closed)
                exit = true;
            else if(ev.type == sf::Event::MouseButtonPressed and ev.mouseButton.button == sf::Mouse::Left and buttons[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))))
                game.mainLoop();
            else if(ev.type == sf::Event::MouseButtonPressed and ev.mouseButton.button == sf::Mouse::Left and buttons[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))))
                exit = true;
        }

        app.clear(sf::Color(20, 20, 20));

        buttons[0].setFillColor(buttons[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(0, 0, 200) : sf::Color(0, 0, 100));
        buttons[0].setOutlineColor(buttons[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(255, 255, 0) : sf::Color(155, 155, 0));
        app.draw(buttons[0]);
        app.draw(texts[0]);

        buttons[1].setFillColor(buttons[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(0, 0, 200) : sf::Color(0, 0, 100));
        buttons[1].setOutlineColor(buttons[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(255, 255, 0) : sf::Color(155, 155, 0));
        app.draw(buttons[1]);
        app.draw(texts[1]);

        app.display();
    }
}

#endif // MAINMENU_HPP_INCLUDED
