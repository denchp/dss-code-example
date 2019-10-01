#ifndef GAMEBOX_H
#define GAMEBOX_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QByteArray>
#include <QPropertyAnimation>
#include <apiclient.h>
#include <game.h>
#include <QPixmap>

namespace Ui {
class gameBox;
}

class gameBox : public QWidget
{
    Q_OBJECT

public:
    explicit gameBox(game g, QWidget *parent = nullptr);

    void setFocus(bool);

    ~gameBox() override;

private:
    Ui::gameBox *ui;

    apiClient *client;

    void onImageReceived(QByteArray);
    QLabel *thumbnail;
    QLabel *top;
    QLabel *bottomTop;
    QLabel *bottomMiddle;
    QLabel *bottomBottom;
    QPixmap image;
    QPropertyAnimation *animation;
    QPropertyAnimation *reverseAnimation;
};

#endif // GAMEBOX_H
