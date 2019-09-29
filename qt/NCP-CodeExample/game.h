#ifndef GAME_H
#define GAME_H
#include <string>

using namespace std;

struct leagueRecord {
    int wins;
    int losses;
    string pct;
};

struct team {
    int score;
    string name;
    leagueRecord record;
};

struct game {
    team home;
    team away;
    bool isHighlighted;
};

#endif // GAME_H
