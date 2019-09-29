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

struct recap {
    string imgUrl;
    string title;
};

struct game {
    team home;
    team away;
    recap recap;
};

#endif // GAME_H
