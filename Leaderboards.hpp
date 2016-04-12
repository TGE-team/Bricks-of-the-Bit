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

    static void readFromFile(std::string);
    static void writeToFile(std::string);
};
std::map<std::string, uint16_t> Leaderboard::scores;
unsigned Leaderboard::maximum;

void Leaderboard::addScore(std::string name, uint16_t score)
{
    scores[name] = score;
}

void Leaderboard::readFromFile(std::string file)
{
    std::ifstream in(file.c_str());

    std::string tmpString;
    uint16_t    tmpNum;

    while(in >> tmpString >> tmpNum)
        scores[tmpString] = tmpNum;

    in.close();
}
void Leaderboard::writeToFile(std::string file)
{
    std::ofstream out(file.c_str());

    for(std::pair<std::string, uint16_t> p : scores)
    {
        out << p.first << " " << p.second << std::endl;
    }

    out.close();
}

#endif // LEADERBOARDS_HPP_INCLUDED
