#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

using namespace std;

class httpRequest : public QObject
{
public:
    httpRequest(string url);
    void send(function<void(string)> onDataReceived);

private:
    void requestComplete(QNetworkReply *reply);
    QNetworkAccessManager * manager;
    QNetworkRequest * request;
};

#endif // HTTPREQUEST_H
