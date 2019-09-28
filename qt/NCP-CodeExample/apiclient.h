#ifndef APICLIENT_H
#define APICLIENT_H

#include <string>
#include <vector>
#include <functional>

#include <QJsonDocument>

#include <game.h>

using namespace std;

class apiClient
{
public:
    apiClient();
    void getGames(string, function<void(vector<game>)>);

private:
    vector<game> parseData(QJsonDocument &json);
};

#endif // APICLIENT_H
