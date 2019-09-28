#ifndef TEAMS_H
#define TEAMS_H
#include <iostream>

using namespace std;

struct record {
    int wins;
    int losses;
    string pct;
};

struct teamDetail {
    int id;
    string name;
    string link;
};

struct team {
    teamDetail team;
    record leagueRecord;
};

struct teams {
    team away;
    team home;
};

#endif // TEAMS_H
