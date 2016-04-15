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

    bool getName;
    item & currentPlayer =
    [&](std::vector < item > & vect)->item &
    {
        for(int i = 0; i < vect.size(); i++)
        {
            if(vect[i].first == "___________")
            {
                getName = i < 10;
                return vect[i];
            }
        }

        return vect[0];

    }(sorted);
    currentPlayer.first.erase(currentPlayer.first.end() - 1);

    sf::Text record[2];
    for(sf::Text & rec : record)
    {
        rec.setFont(font);
        rec.setCharacterSize(55);
        rec.setColor(sf::Color(255, 255, 0));
    }
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(app.getSize().x - 40, 35));

    sf::Text instructions[2];
    for(sf::Text & ref : instructions)
    {
        ref.setColor(sf::Color(255, 255, 0));
        ref.setFont(font);
    }

    instructions[0].setCharacterSize(35);
    instructions[0].setString(getName ? "Enter your name and press [enter] (or leave empty to skip saving)" : "Press [enter] to continue");
    instructions[0].setPosition((app.getSize().x - instructions[0].getLocalBounds().width) / 2.f, 450);
    if(getName)
    {
        instructions[1].setCharacterSize(30);
        instructions[1].setString("Remember, using existing name will overwirite previus score!");
        instructions[1].setPosition((app.getSize().x - instructions[1].getLocalBounds().width) / 2.f, 485);
    }

    int namePos = 0;
    bool mode = true;
    for(bool exit = false; !exit;)
    {
        app.clear(sf::Color(20, 20, 20));

        for(sf::Event ev; app.pollEvent(ev);)
        {
            if(ev.type == sf::Event::KeyPressed and ev.key.code == sf::Keyboard::Return)
                exit = true;
            else if(ev.type == sf::Event::TextEntered and getName)
            {
                if(namePos < currentPlayer.first.size() and isalpha(ev.text.unicode))
                {
                    if(!mode and namePos != 0)
                        namePos++;
                    mode = true;
                    currentPlayer.first[namePos++] = (char) ev.text.unicode;
                }
                else if(ev.text.unicode == 8)
                {
                    if(mode)
                        namePos--;
                    mode = false;
                    currentPlayer.first[namePos] = '_';
                    if(namePos > 0)
                        namePos--;
                }
            }
        }

        //Instrukcja
        app.draw(instructions[0]);
        if(getName)
            app.draw(instructions[1]);

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

    if(getName and currentPlayer.first != "__________")
    {
        currentPlayer.first.erase(currentPlayer.first.begin() + namePos, currentPlayer.first.end());

        Leaderboard::getMap().clear();
        for(auto & a : sorted)
            Leaderboard::getMap()[a.first] = a.second;
        Leaderboard::getMap()[currentPlayer.first] = currentPlayer.second;

        Leaderboard::writeToFile("leaderboard.dat");
    }
}

#endif // RECORDS_HPP_INCLUDED
