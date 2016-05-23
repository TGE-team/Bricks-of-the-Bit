#ifndef LEADERBOARDS_HPP_INCLUDED
#define LEADERBOARDS_HPP_INCLUDED

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class Leaderboard
{
private:
    static std::map<std::string, uint16_t> scores;
    static unsigned maximum;

public:
    static void addScore(std::string, uint16_t);
    static std::map<std::string, uint16_t> & getMap()
    {
        return scores;
    }

    static void readFromFile(std::string);
    static void writeToFile(std::string);
};

#endif // LEADERBOARDS_HPP_INCLUDED
