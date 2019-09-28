#ifndef DATE_H
#define DATE_H
#include<iostream>
#include <vector>
#include <game.h>

using namespace std;

struct date {
    string date;
    int totalItems;
    int totalEvents;
    int totalGames;
    int totalGamesInProgress;
    vector<game> games;
};

#endif // DATE_H
