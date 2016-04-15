#ifndef RECORDS_HPP_INCLUDED
#define RECORDS_HPP_INCLUDED

#include <vector>
#include "Leaderboards.hpp"

void records(sf::RenderWindow & app, uint16_t score, sf::Font & font)
{
    Leaderboard::readFromFile("leaderboard.dat");

    typedef std::pair<std::string, uint16_t> item;

    std::vector<item> sorted;
    for(const item & i : Leaderboard::getMap())
        sorted.push_back(i);

    sorted.push_back(item("___________", score));
    sort(sorted.begin(), sorted.end(), [](item & i1, item & i2) -> bool { return i1.second > i2.second; });

    item & currentPlayer =
    []( std::vector < item > & vect )->item &
    {
        for( item & i: vect )
            if( i.first == "___________" )
                 return i;

    }(sorted);
    bool getName = sorted.size() < 10 or (currentPlayer.second <= sorted[9].second);

    sf::Text record[2];
    for(sf::Text & rec : record)
    {
        rec.setFont(font);
        rec.setCharacterSize(55);
        rec.setColor(sf::Color(255, 255, 0));
    }
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(app.getSize().x - 40, 35));

    for(bool exit = false; !exit;)
    {
        app.clear(sf::Color(20, 20, 20));

        for(sf::Event ev; app.pollEvent(ev);)
        {
            if(ev.type == sf::Event::KeyPressed and ev.key.code == sf::Keyboard::Escape)
                exit = true;
        }

        for(unsigned i = 0; i < sorted.size() and i < 10; i++)
        {
            //Rysowanie prostokątów
            rect.setPosition(20, 70 + i * 35);
            rect.setFillColor(i % 2 ? sf::Color(20, 20, 255) : sf::Color(50, 50, 150));

            app.draw(rect);


            //Rysowanie rekordów
            for(sf::Text & rec : record)
                rec.setPosition(100, 50 + i * 35);
            record[1].move(400, 0);

            record[0].setString(sorted[i].first);
            record[1].setString(toString(sorted[i].second));

            app.draw(record[0]);
            app.draw(record[1]);
        }

        app.display();
    }
}

#endif // RECORDS_HPP_INCLUDED
