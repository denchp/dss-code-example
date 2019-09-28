#include "apiclient.h"

#include <string>
#include <vector>
#include <iostream>
#include <httprequest.h>
#include <QJsonDocument>
#include <QString>
#include <game.h>

using namespace std;

void apiClient::getGames(string date, function<void(vector<game>)> onDataParsed){
    httpRequest * req = new httpRequest("http://statsapi.mlb.com/api/v1/schedule?hydrate=game(content(editorial(recap))),decisions&date=" + date + "&sportId=1");

    req->send([=](string data) {
        QJsonDocument doc = QJsonDocument::fromJson(QString::fromStdString(data).toUtf8());
        vector<game> games = this->parseData(doc);
        onDataParsed(games);
    });
}

vector<game> apiClient::parseData(QJsonDocument &json) {
    qDebug() << "Document parsed: ";
    qDebug() << json["copyright"].toString();

    vector<game> games = *new vector<game>();

    int totalGames = json["totalGames"].toInt();

    for(int i = 0; i < totalGames; i++) {
        game g {
            {
                json["dates"][0]["games"][i]["teams"]["home"]["score"].toInt(), //score
                json["dates"][0]["games"][i]["teams"]["home"]["team"]["name"].toString().toStdString(), //name
                {
                    json["dates"][0]["games"][i]["teams"]["home"]["leagueRecord"]["wins"].toInt(),
                    json["dates"][0]["games"][i]["teams"]["home"]["leagueRecord"]["losses"].toInt(),
                    json["dates"][0]["games"][i]["teams"]["home"]["leagueRecord"]["pct"].toString().toStdString()
                } // record
            }, //home
            {
                json["dates"][0]["games"][i]["teams"]["away"]["score"].toInt(), //score
                json["dates"][0]["games"][i]["teams"]["away"]["team"]["name"].toString().toStdString(), //name
                {
                    json["dates"][0]["games"][i]["teams"]["away"]["leagueRecord"]["wins"].toInt(),
                    json["dates"][0]["games"][i]["teams"]["away"]["leagueRecord"]["losses"].toInt(),
                    json["dates"][0]["games"][i]["teams"]["away"]["leagueRecord"]["pct"].toString().toStdString()
                } // record
            },//away
        };

        games.push_back(g);
    }

    return games;
}