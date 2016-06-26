#include "Game.hpp"

sf::Texture Game::ballTexture;
sf::Texture Game::brickTexture;
sf::Texture Game::framesTexture;
sf::Texture Game::backgroundTexture;

Game::Game()
{
    colors = {
        sf::Color(255, 0, 0),
        sf::Color(255, 255, 0),
        sf::Color(0, 255, 0),
        sf::Color(50, 50, 255)
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

    level = 0;
}
uint16_t Game::mainLoop()
{
    framesSprite.setTexture(framesTexture);
    framesSprite.setPosition(0.f, 0.f);
    framesSprite.setScale(4.f / 3.f, 5.05f / 3.f);

    backgroundOffsetRight = true;
    backgroundOffset = 0.f;
    backgroundTimer.restart();

    background.setTexture(backgroundTexture);
    background.setScale(2.f, 2.f);
    background.setPosition(0, 0);

    Brick::layers = 2;  //Domyślna ilość warstw cegiełek na początku gry

    player.ballsLeft = 3;                          //Ustawienie ilosci pozostałych piłek
    player.points = 0;                             //Wyzerowanie punktów
    player.combo = 0;                              //Wyzerowanie "combo"

    player.setPosition(sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y - 8));

    ball = Ball(10.f, 1.f, sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y / 2.f), colors[rand() % colors.size()], &ballTexture);

    sf::Clock frameClock;
    bool exit = false;
    bool ready = false;

    Brick::x = 1;
    Brick::y = 3;
    for(sf::Time frameTime; window.isOpen() and !exit; frameTime = frameClock.restart())
    {
        backgroundOffset += backgroundTimer.restart().asSeconds() * 10.f * (static_cast<int>(backgroundOffsetRight) * 2 - 1);
        if(backgroundOffset + window.getSize().x > background.getGlobalBounds().width && backgroundOffsetRight)
            backgroundOffsetRight = false;
        else if(backgroundOffset < 0 && !backgroundOffsetRight)
            backgroundOffsetRight = true;

        background.setPosition({-backgroundOffset, -100});

        if(!ready and Brick::generation >= 0.1f)
        {
            bricks.push_back(Brick());
            bricks.back().setTexture(&brickTexture);
            bricks.back().setFillColor(colors[Brick::y - 3]);
            bricks.back().setPosition(Brick::x * 80, Brick::y * 30);
            bricks.back().setSize(sf::Vector2f(78, 21));

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

        window.draw(background);
        window.draw(framesSprite);

        sf::Vector2f diff = player.getPosition();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and player.getPosition().x + (player.getSize().x / 2.f) < window.getView().getSize().x - 70)
            player.move(frameTime.asSeconds() / (1.f / +300.f), 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and player.getPosition().x - (player.getSize().x / 2.f) > 70.f)
            player.move(frameTime.asSeconds() / (1.f / -300.f), 0);
        diff -= player.getPosition();
        window.draw(player);

        pointsText.setString("Points: " + toString(player.points));
        pointsText.setPosition(window.getView().getSize().x / 2.f - (pointsText.getGlobalBounds().width / 2.f), 0);

        comboText.setString("Combo: " + toString((int) player.combo + 1) + "x");
        comboText.setPosition(window.getView().getSize().x - 75 - pointsText.getGlobalBounds().width, 0);

        ballsLeftText.setString("Balls left: " + toString(player.ballsLeft - 1));
        ballsLeftText.setPosition(75, 0);


        window.draw(ballsLeftText);
        window.draw(pointsText);
        window.draw(comboText);

        ball.update(sf::FloatRect(60, 0, window.getView().getSize().x - 120, window.getView().getSize().y + 50));
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
        if(ball.getPosition().y - ball.getRadius() > window.getSize().y)
        {
            ball = Ball(10.f, 1.f + static_cast<float>(level) / 5, sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y / 2.f), colors[rand() % colors.size()], &ballTexture);
            player.setPosition(sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y - 8));
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

                sf::Vector2f rectPos = continueText.getPosition() + sf::Vector2f(-5, 13);

                sf::Image img;
                img.create(continueText.getGlobalBounds().width + 10, continueText.getGlobalBounds().height + 8);

                for(int x = 0; x < img.getSize().x; x++)
                for(int y = 0; y < img.getSize().y; y++)
                {
                    auto c = screenshot.getPixel(x + rectPos.x, y + rectPos.y);

                    auto u = screenshot.getPixel(x + rectPos.x, y + rectPos.y - 1);
                    auto d = screenshot.getPixel(x + rectPos.x, y + rectPos.y + 1);
                    auto r = screenshot.getPixel(x + rectPos.x + 1, y + rectPos.y);
                    auto l = screenshot.getPixel(x + rectPos.x - 1, y + rectPos.y);

                    c.r = (c.r + u.r + d.r + r.r + l.r) / 10;
                    c.g = (c.g + u.g + d.g + r.g + l.g) / 10;
                    c.b = (c.b + u.b + d.b + r.b + l.b) / 10;

                    img.setPixel(x, y, c);
                }

                blurTexture.loadFromImage(img);
                continueTextRect.setTexture(&blurTexture);

                continueTextRect.setPosition(rectPos);
                continueTextRect.setSize(sf::Vector2f(continueText.getGlobalBounds().width + 10, continueText.getGlobalBounds().height + 8));

                for(bool clicked = false; !clicked;)
                {
                    window.draw(screenshotS);
                    window.draw(continueTextRect);
                    window.draw(continueText);
                    window.display();

                    for(sf::Event ev; window.pollEvent(ev);)
                        if(ev.type == sf::Event::KeyPressed and ev.key.code == sf::Keyboard::Return)
                            clicked = true;
                }
                frameClock.restart();
                backgroundTimer.restart();
            }
        }
        else if(bricks.size() == 0 and ready)
        {
            ready = false;
            ball = Ball(10.f, 1.f + static_cast<float>(level) / 5, sf::Vector2f(window.getView().getSize().x / 2.f, window.getView().getSize().y / 2.f), colors[rand() % colors.size()], &ballTexture);
            player.ballsLeft++;
            Brick::x = 1;
            Brick::y = 3;
            if(Brick::layers < 4)
                Brick::layers++;

            level++;
        }

        if(ready)
            ball.move(frameTime);
        window.draw(ball);

        window.display();
    }

    bricks.clear();
    return player.points;
}
