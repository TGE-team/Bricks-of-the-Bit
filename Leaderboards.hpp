#ifndef LEADERBOARDS_HPP_INCLUDED
#define LEADERBOARDS_HPP_INCLUDED

#include <map>
#include <string>

class Leaderboard
{
private:
    static std::map<std::string, uint16_t> scores;
    static unsigned maximum;

public:
    static void readFromFile(std::string);
    static void writeToFile(std::string);

    static void addScore(std::string, uint16_t);
    static const std::map & getBoard();
}
std::map<std::string, uint16_t> Leaderboard::scores;
unsigned Leaderboard::maximum;

#endif // LEADERBOARDS_HPP_INCLUDED
