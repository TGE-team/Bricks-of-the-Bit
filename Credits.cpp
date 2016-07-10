#include "Credits.hpp"

void credits(sf::RenderWindow &app, sf::Font &font, sf::Texture TGELogoTex)
{
	sf::RectangleShape button;
	button.setOutlineThickness(3.f);
	button.setSize(sf::Vector2f(150, 55));
	button.setOrigin(button.getSize() / 2.f);
	button.setPosition(sf::Vector2f(app.getSize().x / 2, app.getSize().y - 100));

	sf::Text texts[4];
	for(auto i = 0u; i < 4; i++)
	{
		texts[i].setColor({255, i == 0u ? 127 : 255, 0});
		texts[i].setCharacterSize(i == 0u ? 80 : 66);
		texts[i].setFont(font);
	}
	texts[0].setString("Authors:");
	texts[1].setString("- Kamil Koczurek (code)");
	texts[2].setString("- Daniel Szczepanik (graphics)");
	texts[3].setString("Exit");

	texts[0].setPosition({(app.getSize().x / 2 - texts[0].getGlobalBounds().width / 2), 10});
	texts[1].setPosition({50, 75});
	texts[2].setPosition({50, 125});
	texts[3].setPosition(button.getPosition() + sf::Vector2f(-40, -45));

	//Nazwa studia
	sf::Text studioText;
	studioText.setColor({255, 255, 0});
	studioText.setCharacterSize(48);
	studioText.setFont(font);
	studioText.setString("Thunder Games Entertainment, 2016");
	studioText.setPosition(app.getSize().x / 2 - studioText.getGlobalBounds().width / 2, 385);

	sf::Sprite TGELogo(TGELogoTex);
	TGELogo.setPosition(app.getSize().x / 2 - TGELogo.getGlobalBounds().width / 2, 230);

	while(app.isOpen())
	{
		for(sf::Event ev; app.pollEvent(ev);)
		{
			if(ev.type == sf::Event::Closed)
				app.close();
			else if((ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
				or	(ev.type == sf::Event::MouseButtonPressed and ev.mouseButton.button == sf::Mouse::Left and button.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app)))))
				return;
		}

		button.setFillColor(button.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(0, 0, 200) : sf::Color(0, 0, 100));
		button.setOutlineColor(button.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app))) ? sf::Color(255, 255, 0) : sf::Color(155, 155, 0));

		app.clear({20, 20, 20});

		app.draw(studioText);
		app.draw(TGELogo);
		app.draw(button);
		for(auto & t : texts)
			app.draw(t);
		app.display();
	}
}
