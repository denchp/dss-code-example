#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <iostream>
#include <vector>
#include <date.h>

using namespace std;

struct schedule {
    string copyright;
    int totalItems;
    int totalEvents;
    int totalGames;
    vector<date> dates;
};

#endif // SCHEDULE_H
