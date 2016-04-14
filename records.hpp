#ifndef RECORDS_HPP_INCLUDED
#define RECORDS_HPP_INCLUDED

#include <vector>
#include "Leaderboards.hpp"

void records(sf::RenderWindow & app, uint16_t score)
{
    Leaderboard::readFromFile("leaderboard.dat");

    typedef std::pair<std::string, uint16_t> item;

    std::vector<item> sorted;
    sorted.reserve(Leaderboard::getMap().size() + 1);
    transform(
        Leaderboard::getMap().begin(), Leaderboard::getMap().end(),
        back_inserter(sorted),
        [](item i) { return i; }
    );
    sorted.push_back(item("_______", score));
    sort(sorted.begin(), sorted.end(), [](item & i1, item & i2) -> bool { i1.second < i2.second; });

    bool fit = false;
    for(int i = 0; i < sorted.size(); i++)
    {
        std::cout << sorted[i].first << " " << sorted[i].second << std::endl;
    }

    for(bool exit = false; !exit;)
    {
        app.clear(sf::Color(20, 20, 20));

        for(sf::Event ev; app.pollEvent(ev);)
        {
            if(ev.type == sf::Event::KeyPressed and ev.key.code == sf::Keyboard::Escape)
                exit = true;
        }

        app.display();
    }
}

#endif // RECORDS_HPP_INCLUDED
