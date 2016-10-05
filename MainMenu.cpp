#include "MainMenu.hpp"

void mainMenu()
{
	Game game;
	game.window.create(sf::VideoMode(800, 600), "Bricks Of The Bit (Beta 1.0)");
	sf::RenderWindow & app = game.window;

	qsf::QResourceStream textureStream;
	Game::backgroundTexture.loadFromStream(textureStream("://city.png"));
	Game::framesTexture.loadFromStream(textureStream("://frames.png"));
	Game::TGELogoTexture.loadFromStream(textureStream("://logo.png"));
	Game::ballTexture.loadFromStream(textureStream("://ball.png"));

	/*
	 * true - load bricks textures from tex folder
	 * false - load from assets
	 */
	const auto DEBUG_TEXTURES = false;
	if(DEBUG_TEXTURES)
	{
		Game::brickTextures[Brick::Property::NONE].loadFromFile("tex/brick.png");
		Game::brickTextures[Brick::Property::BONUS].loadFromFile("tex/brick-bonus.png");
		Game::brickTextures[Brick::Property::EXPLOSIVE].loadFromFile("tex/brick-explosive.png");
		Game::brickTextures[Brick::Property::RESISTANT_3].loadFromFile("tex/brick-resistant-3.png");
		Game::brickTextures[Brick::Property::RESISTANT_2].loadFromFile("tex/brick-resistant-2.png");
		Game::brickTextures[Brick::Property::RESISTANT_1].loadFromFile("tex/brick-resistant-1.png");
		Game::brickTextures[Brick::Property::RANDOM_EXPLOSIVE].loadFromFile("tex/brick-random-explosive.png");
	}
	else
	{
		Game::brickTextures[Brick::Property::NONE].loadFromStream(textureStream("://brick.png"));
		Game::brickTextures[Brick::Property::BONUS].loadFromStream(textureStream("://brick-bonus.png"));
		Game::brickTextures[Brick::Property::EXPLOSIVE].loadFromStream(textureStream("://brick-explosive.png"));
		Game::brickTextures[Brick::Property::RESISTANT_3].loadFromStream(textureStream("://brick-resistant-3.png"));
		Game::brickTextures[Brick::Property::RESISTANT_2].loadFromStream(textureStream("://brick-resistant-2.png"));
		Game::brickTextures[Brick::Property::RESISTANT_1].loadFromStream(textureStream("://brick-resistant-1.png"));
		Game::brickTextures[Brick::Property::RANDOM_EXPLOSIVE].loadFromStream(textureStream("://brick-random-explosive.png"));
	}

	const auto BUTTONS = 4u;
	sf::RectangleShape buttons[BUTTONS];
	sf::Text           texts[BUTTONS];

	//Uruchamianie gry
	buttons[0].setOutlineThickness(3.f);
	buttons[0].setSize(sf::Vector2f(300, 70));
	buttons[0].setOrigin(buttons[0].getSize() / 2.f);
	buttons[0].setPosition(sf::Vector2f(app.getSize().x / 2, app.getSize().y / 2 - 100));

	texts[0].setString("Play!");
	texts[0].setFont(game.font);
	texts[0].setCharacterSize(90);
	texts[0].setFillColor(sf::Color(255, 255, 0));
	texts[0].setPosition(buttons[0].getPosition() + sf::Vector2f(-75, -63));
	//================

	//Wyjście z gry
	buttons[1].setOutlineThickness(2.f);
	buttons[1].setSize(sf::Vector2f(200, 50));
	buttons[1].setOrigin(buttons[1].getSize() / 2.f);
	buttons[1].setPosition(sf::Vector2f(app.getSize().x / 2, app.getSize().y / 2 + 205));

	texts[1].setString("Exit");
	texts[1].setFont(game.font);
	texts[1].setCharacterSize(70);
	texts[1].setFillColor(sf::Color(255, 255, 0));
	texts[1].setPosition(buttons[1].getPosition() + sf::Vector2f(-40, -48));
	//=============

	//Tablica rekordów
	buttons[2].setOutlineThickness(2.f);
	buttons[2].setSize(sf::Vector2f(200, 50));
	buttons[2].setOrigin(buttons[1].getSize() / 2.f);
	buttons[2].setPosition(sf::Vector2f(app.getSize().x / 2, app.getSize().y / 2 + 130));

	texts[2].setString("Records");
	texts[2].setFont(game.font);
	texts[2].setCharacterSize(70);
	texts[2].setFillColor(sf::Color(255, 255, 0));
	texts[2].setPosition(buttons[2].getPosition() + sf::Vector2f(-90, -48));
	//================

	//Autorzy
	buttons[3].setOutlineThickness(2.f);
	buttons[3].setSize(sf::Vector2f(200, 50));
	buttons[3].setOrigin(buttons[1].getSize() / 2.f);
	buttons[3].setPosition(sf::Vector2f(app.getSize().x / 2, app.getSize().y / 2 + 55));

	texts[3].setString("Credits");
	texts[3].setFont(game.font);
	texts[3].setCharacterSize(70);
	texts[3].setFillColor(sf::Color(255, 255, 0));
	texts[3].setPosition(buttons[3].getPosition() + sf::Vector2f(-80, -48));
	//=======

	//Nazwa gry
	sf::Text gameName;
	gameName.setString("Bricks of the Bit");
	gameName.setFont(game.font);
	gameName.setCharacterSize(96);
	gameName.setFillColor(sf::Color(255, 0, 0));
	gameName.setPosition(app.getSize().x / 2 - gameName.getGlobalBounds().width / 2, 20);

	//Wersja gry
	sf::Text gameVersion;
	gameVersion.setString("Game in version Beta 1.0");
	gameVersion.setFont(game.font);
	gameVersion.setCharacterSize(32);
	gameVersion.setFillColor(sf::Color(255, 127, 0));
	gameVersion.setPosition(app.getSize().x / 2 - gameVersion.getGlobalBounds().width / 2, 100);

	//Studio
	sf::Text studioText;
	studioText.setString("Created by Thunder Games Entertainment, 11-07-2016.");
	studioText.setFont(game.font);
	studioText.setCharacterSize(32);
	studioText.setFillColor(sf::Color(255, 255, 0));
	studioText.setPosition(app.getSize().x / 2 - studioText.getGlobalBounds().width / 2, app.getSize().y - 65);

	//Prawa
	sf::Text rightsText;
	rightsText.setString(L"©2016, TGE. All rights reserved.");
	rightsText.setFont(game.font);
	rightsText.setCharacterSize(32);
	rightsText.setFillColor(sf::Color(255, 255, 0));
	rightsText.setPosition(app.getSize().x / 2 - rightsText.getGlobalBounds().width / 2, app.getSize().y - 40);

	Ball decoration(10.f, 1.f, static_cast<sf::Vector2f>(app.getSize()) / 2.f, game.colors[rand() % game.colors.size()], &Game::ballTexture);

	bool exit = false;
	sf::Clock frameClock;
	for(sf::Time frameTime; app.isOpen() && !exit; frameTime = frameClock.restart())
	{
		for(sf::Event ev; app.pollEvent(ev);)
		{
			if(ev.type == sf::Event::Closed)
				exit = true;
			else if(ev.type == sf::Event::MouseButtonPressed and ev.mouseButton.button == sf::Mouse::Left and buttons[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))))
			{
				records(app, game.mainLoop(), game.font);
				frameTime = sf::seconds(0);
				frameClock.restart();
			}
			else if(ev.type == sf::Event::MouseButtonPressed and ev.mouseButton.button == sf::Mouse::Left and buttons[2].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))))
			{
				records(app, 0, game.font, false);
				frameTime = sf::seconds(0);
				frameClock.restart();
			}
			else if(ev.type == sf::Event::MouseButtonPressed and ev.mouseButton.button == sf::Mouse::Left and buttons[3].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))))
			{
				credits(app, game.font, Game::TGELogoTexture);
				frameTime = sf::seconds(0);
				frameClock.restart();
			}
			else if(ev.type == sf::Event::MouseButtonPressed and ev.mouseButton.button == sf::Mouse::Left and buttons[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))))
				exit = true;
		}

		app.clear(sf::Color(20, 20, 20));

		buttons[0].setFillColor(buttons[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(0, 0, 200) : sf::Color(0, 0, 100));
		buttons[0].setOutlineColor(buttons[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(255, 255, 0) : sf::Color(155, 155, 0));

		buttons[1].setFillColor(buttons[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(0, 0, 200) : sf::Color(0, 0, 100));
		buttons[1].setOutlineColor(buttons[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(255, 255, 0) : sf::Color(155, 155, 0));

		buttons[2].setFillColor(buttons[2].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(0, 0, 200) : sf::Color(0, 0, 100));
		buttons[2].setOutlineColor(buttons[2].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(255, 255, 0) : sf::Color(155, 155, 0));

		buttons[3].setFillColor(buttons[3].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(0, 0, 200) : sf::Color(0, 0, 100));
		buttons[3].setOutlineColor(buttons[3].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(255, 255, 0) : sf::Color(155, 155, 0));

		app.draw(gameName);
		app.draw(gameVersion);
		app.draw(studioText);
		app.draw(rightsText);
		for(auto i = 0; i < BUTTONS; i++)
		{
			app.draw(buttons[i]);
			app.draw(texts[i]);
		}

		sf::Vector2f acc = decoration.getMomentum();
		float acceleration = 1.02f;
		if(sqrt(acc.x * acc.x + acc.y * acc.y) > 15.f * 60.f * frameTime.asSeconds())
			acceleration = 1.f;

		decoration.update(sf::FloatRect(0, 0, app.getView().getSize().x, app.getView().getSize().y), frameTime);
		for(auto i = 0; i < BUTTONS; i++)
			decoration.collision(buttons[i], acceleration);

		decoration.move();
		app.draw(decoration);

		app.display();
	}
}
