#include "httprequest.h"
#include <string>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QByteArray>
#include <QUrl>
#include <QString>
#include <QtCore>

#include <iostream>

using namespace std;

httpRequest::httpRequest(string url)
{
    QString urlQString = QString::fromStdString(url);
    request = new QNetworkRequest();
    request->setUrl(urlQString);
}

void httpRequest::send(function<void(string)> onDataReceived) {
    manager = new QNetworkAccessManager();

    connect(manager, &QNetworkAccessManager::finished,
            this, [=](QNetworkReply * reply) {
        string data = reply->readAll().toStdString();
        qDebug() << "Data received";
        onDataReceived(data);
    });

    manager->get(*request);
}


void httpRequest::send(function<void(QByteArray)> onDataReceived) {
    manager = new QNetworkAccessManager();

    connect(manager, &QNetworkAccessManager::finished,
            this, [=](QNetworkReply * reply) {
        if (reply->error()) {
            qDebug() << "Error completing request";
            return;
        }

        QByteArray data = reply->readAll();
        qDebug() << "Data received: " << data.size();
        onDataReceived(data);
    });

    qDebug() << "Requesting url: " << request->url();
    manager->get(*request);
}


void httpRequest::requestComplete(QNetworkReply * reply) {
    if (reply->error()) {
        return; // No error handling, we're assuming happy path
    } else {
        qDebug() << reply->readAll(); // dump to the console for now
    }
}
