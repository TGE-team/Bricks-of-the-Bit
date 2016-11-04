#include "Game.hpp"
#include <iostream>

sf::Texture Game::ballTexture;
sf::Texture Game::framesTexture;
sf::Texture Game::TGELogoTexture;
sf::Texture Game::backgroundTexture;
std::map<Brick::Property, sf::Texture> Game::brickTextures;

Game::Game()
{
	fpsMeter = FpsMeter("Loading...", font, 30);
	fpsMeter.setFillColor({255, 255, 0});
	fpsMeter.setPosition({75, 30});

	colors = {
	sf::Color(255, 0, 0),
	sf::Color(255, 255, 0),
	sf::Color(0, 255, 0),
	sf::Color(50, 50, 255)
	};

	player.setTexture(&brickTextures[Brick::Property::NONE]);
	player.setSize(sf::Vector2f(61, 11));          //Ustawienie rozmiaru gracza
	player.setFillColor(sf::Color(20, 20, 200));   //Ustawienie koloru wypełnienia gracza
	player.setOutlineColor(sf::Color(0, 0, 255));  //Ustawienie koloru obramowania gracza
	player.setOutlineThickness(3.f);               //Ustawienie grubości obramowania gracza
	player.setOrigin(30, 5);                       //Wysrodkowanie gracza

	bitFont.loadFromStream(fontStream("://bitfont.ttf")); //Wczytanie czcionki z zasobów

	//Utworzenie wszystkich tekstów (ustawienie czcionki, rozmiaru i koloru)
	pointsText.setFont(bitFont);                                          //
	pointsText.setCharacterSize(38);                                      //
	pointsText.setFillColor(sf::Color(255, 255, 0));                      //
	//
	comboText.setFont(bitFont);                                           //
	comboText.setCharacterSize(32);                                       //
	comboText.setFillColor(sf::Color(255, 255, 0));                       //
	//
	continueText.setFont(bitFont);                                        //
	continueText.setCharacterSize(45);                                    //
	continueText.setFillColor(sf::Color(255, 255, 0));                    //
	//
	ballsLeftText.setFont(bitFont);                                       //
	ballsLeftText.setCharacterSize(32);                                   //
	ballsLeftText.setFillColor(sf::Color(255, 255, 0));                   //
	//======================================================================
}
bool Game::pause()
{
	sf::Texture screenshot;
	screenshot.create(window.getSize().x, window.getSize().y);
	screenshot.update(window);

	sf::Sprite background(screenshot);

	const auto BUTTONS = 3u;
	sf::RectangleShape buttons[BUTTONS];
	sf::Text           texts[BUTTONS];

	//Kontynuacja
	buttons[0].setOutlineThickness(3.f);
	buttons[0].setSize(sf::Vector2f(300, 70));
	buttons[0].setOrigin(buttons[0].getSize() / 2.f);
	buttons[0].setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 50));

	texts[0].setString("Continue");
	texts[0].setFont(this->font);
	texts[0].setCharacterSize(90);
	texts[0].setFillColor(sf::Color(255, 255, 0));
	texts[0].setPosition(buttons[0].getPosition() + sf::Vector2f(-120, -63));
	//================

	//Menu
	buttons[1].setOutlineThickness(3.f);
	buttons[1].setSize(sf::Vector2f(300, 70));
	buttons[1].setOrigin(buttons[0].getSize() / 2.f);
	buttons[1].setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + 35));

	texts[1].setString("Menu");
	texts[1].setFont(this->font);
	texts[1].setCharacterSize(90);
	texts[1].setFillColor(sf::Color(255, 255, 0));
	texts[1].setPosition(buttons[1].getPosition() + sf::Vector2f(-50, -63));
	//================

	//Wyjście z gry
	buttons[2].setOutlineThickness(2.f);
	buttons[2].setSize(sf::Vector2f(200, 50));
	buttons[2].setOrigin(buttons[2].getSize() / 2.f);
	buttons[2].setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + 110));

	texts[2].setString("Exit");
	texts[2].setFont(this->font);
	texts[2].setCharacterSize(70);
	texts[2].setFillColor(sf::Color(255, 255, 0));
	texts[2].setPosition(buttons[2].getPosition() + sf::Vector2f(-40, -48));
	//=============

	sf::Clock pauseClock;
	for(bool paused = true; paused && window.isOpen();)
	{
		for(sf::Event ev; window.pollEvent(ev);)
		{
			if(ev.type == sf::Event::Closed)
				window.close();
			else if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
				paused = false;
			else if(ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
			{
				if(buttons[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
					paused = false;
				else if(buttons[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
					return true;
				else if(buttons[2].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
				{
					window.close();
					::exit(0);
				}
			}
		}

		float factor = pauseClock.getElapsedTime().asSeconds() * 3.f;
		if(factor > 1.f)
			factor = 1.f;
		background.setColor({255 - (factor * 130), 255 - (factor * 130), 255 - (factor * 130)});

		buttons[0].setFillColor(buttons[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) ? sf::Color(0, 0, 200) : sf::Color(0, 0, 100));
		buttons[0].setOutlineColor(buttons[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) ? sf::Color(255, 255, 0) : sf::Color(155, 155, 0));

		buttons[1].setFillColor(buttons[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) ? sf::Color(0, 0, 200) : sf::Color(0, 0, 100));
		buttons[1].setOutlineColor(buttons[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) ? sf::Color(255, 255, 0) : sf::Color(155, 155, 0));


		buttons[2].setFillColor(buttons[2].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) ? sf::Color(0, 0, 200) : sf::Color(0, 0, 100));
		buttons[2].setOutlineColor(buttons[2].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) ? sf::Color(255, 255, 0) : sf::Color(155, 155, 0));

		window.clear();
		window.draw(background);
		for(auto i = 0u; i < BUTTONS; i++)
		{
			window.draw(buttons[i]);
			window.draw(texts[i]);
		}
		window.display();
	}

	return false;
}

uint16_t Game::mainLoop()
{
	level = 0;

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
	float drawAccumulate = 1;

	auto internalFrameCount = 0u;
	sf::Clock internalFpsCountClock;
	for(sf::Time frameTime; window.isOpen() and !exit; frameTime = frameClock.restart())
	{
		++internalFrameCount;
		float acceleration = 1.0f + (11 - level) * 0.002;
		if(level >= 11)
			acceleration = 1.005;

		backgroundOffset += backgroundTimer.restart().asSeconds() * 10.f * (static_cast<int>(backgroundOffsetRight) * 2 - 1);
		if(backgroundOffset + window.getSize().x > background.getGlobalBounds().width && backgroundOffsetRight)
			backgroundOffsetRight = false;
		else if(backgroundOffset < 0 && !backgroundOffsetRight)
			backgroundOffsetRight = true;

		background.setPosition({-backgroundOffset, -100});

		if(!ready and Brick::generation >= 0.1f)
		{
			Brick::Property prop = Brick::Property::NONE;
			if(rand() % 100 > 75)
				prop = static_cast<Brick::Property>(rand() % (Brick::Property::COUNT - 1) + 1);

			bricks.push_back(Brick(prop));
			bricks.back().setTexture(&brickTextures[prop]);
			bricks.back().setFillColor(colors[Brick::y - 3]);
			bricks.back().setPosition(Brick::x * 82 - 8, Brick::y * 30);
			bricks.back().setSize(sf::Vector2f(79, 21));

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
			else if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				if(pause())
					exit = true;
				frameClock.restart();
			}
		}

		sf::Vector2f diff = player.getPosition();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and player.getPosition().x + (player.getSize().x / 2.f) < window.getView().getSize().x - 70)
			player.move(frameTime.asSeconds() * +350.f, 0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and player.getPosition().x - (player.getSize().x / 2.f) > 70.f)
			player.move(frameTime.asSeconds() * -350.f, 0);
		diff -= player.getPosition();

		int roundPoints = player.points * 100;
		float toPrint = roundPoints / 100.f;
		pointsText.setString("Points: " + toString(toPrint));
		pointsText.setPosition(window.getView().getSize().x / 2.f - (pointsText.getGlobalBounds().width / 2.f), 0);

		comboText.setString("Combo: " + toString((int) player.combo + 1) + "x");
		comboText.setPosition(window.getView().getSize().x - 75 - pointsText.getGlobalBounds().width, 0);

		ballsLeftText.setString("Balls left: " + toString(player.ballsLeft - 1));
		ballsLeftText.setPosition(75, 0);

		ball.update(sf::FloatRect(60, 0, window.getView().getSize().x - 120, window.getView().getSize().y + 50), frameTime);
		if(ball.collision(player, acceleration, diff / -4.f))
			player.combo = 0;

		for(size_t i = 0; i < bricks.size(); i++)
		{
			if(ball.collision(bricks[i], acceleration))
			{
				bricks.erase(bricks.begin() + i);
				player.points += (player.combo + 1) * (1 + 0.05 * level);
				player.combo++;

				break;
			}
		}
		if(ready)
			ball.move();

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
				sf::Texture screenshotT;
				screenshotT.create(window.getSize().x, window.getSize().y);
				screenshotT.update(window);
				sf::Sprite  screenshotS(screenshotT);
				screenshotS.setPosition(0, 0);

				sf::Image screenshot = screenshotT.copyToImage();

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
					{
						if(ev.type == sf::Event::KeyPressed and ev.key.code == sf::Keyboard::Return)
							clicked = true;
						if(ev.type == sf::Event::Closed)
						{
							window.close();
							::exit(0);
						}
					}
				}
				frameClock.restart();
				backgroundTimer.restart();
			}
		}
		else if(bricks.size() == 0 && ready)
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

		drawAccumulate += frameTime.asSeconds();
		if(drawAccumulate >= 2.f / 600.f) {
			window.draw(background);
			window.draw(framesSprite);

			window.draw(ballsLeftText);
			window.draw(pointsText);
			window.draw(comboText);

			fpsMeter.update();
			window.draw(fpsMeter);

			window.draw(player);

			for(const Brick& brick: bricks)
				window.draw(brick);

			window.draw(ball);
			window.display();

			drawAccumulate = 0.f;
		}
		if(internalFpsCountClock.getElapsedTime() > sf::seconds(1)) {
			std::cout << static_cast<double>(internalFrameCount) / internalFpsCountClock.restart().asSeconds() << " iFPS" << std::endl;
		}
	}

	bricks.clear();
	return player.points;
}
