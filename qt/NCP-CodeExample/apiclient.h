#ifndef APICLIENT_H
#define APICLIENT_H

#include <string>
#include <vector>
#include <functional>

#include <QJsonDocument>
#include <QByteArray>

#include <game.h>

using namespace std;

class apiClient
{
public:
    apiClient();

    void getGames(string, function<void(vector<game>)>);
    void getImage(string, function<void(QByteArray)>);

private:
    vector<game> parseData(QJsonDocument &json);
};

#endif // APICLIENT_H
