#include "apiclient.h"

#include <string>
#include <vector>
#include <iostream>

#include <httprequest.h>
#include <game.h>

#include <QJsonValue>
#include <QDebug>
#include <QJsonDocument>
#include <QByteArray>
#include <QString>

using namespace std;

void apiClient::getGames(string date, function<void(vector<game>)> onDataParsed){
    httpRequest *req = new httpRequest("http://statsapi.mlb.com/api/v1/schedule?hydrate=game(content(editorial(recap))),decisions&date=" + date + "&sportId=1");

    req->send([=](string data) {
        QJsonDocument doc = QJsonDocument::fromJson(QString::fromStdString(data).toUtf8());
        vector<game> games = this->parseData(doc);
        onDataParsed(games);
    });
}

void apiClient::getImage(string url, function<void (QByteArray)> onImageReceived) {
    httpRequest *req = new httpRequest(url);

    req->send([=](QByteArray data) {
        onImageReceived(data);
    });
}

vector<game> apiClient::parseData(QJsonDocument &json) {
    qDebug() << "Document parsed: ";
    vector<game> games = *new vector<game>();

    int totalGames = json["totalGames"].toInt();

    for(int i = 0; i < totalGames; i++) {
        QJsonValue root = json["dates"][0]["games"][i];
        game g {
            {
                root["teams"]["home"]["score"].toInt(), //score
                root["teams"]["home"]["team"]["name"].toString().toStdString(), //name
                {
                    root["teams"]["home"]["leagueRecord"]["wins"].toInt(),
                    root["teams"]["home"]["leagueRecord"]["losses"].toInt(),
                    root["teams"]["home"]["leagueRecord"]["pct"].toString().toStdString()
                } // record
            }, //home
            {
                root["teams"]["away"]["score"].toInt(), //score
                root["teams"]["away"]["team"]["name"].toString().toStdString(), //name
                {
                    root["teams"]["away"]["leagueRecord"]["wins"].toInt(),
                    root["teams"]["away"]["leagueRecord"]["losses"].toInt(),
                    root["teams"]["away"]["leagueRecord"]["pct"].toString().toStdString()
                } // record
            },//away
            {
                root["content"]["editorial"]["recap"]["mlb"]["image"]["cuts"][6]["src"].toString().toStdString(),
                root["content"]["editorial"]["recap"]["mlb"]["headline"].toString().toStdString()
            }, //recap
        };

        games.push_back(g);
    }

    return games;
}
