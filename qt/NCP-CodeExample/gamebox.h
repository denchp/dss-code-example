#ifndef GAMEBOX_H
#define GAMEBOX_H

#include <QWidget>
#include <QLabel>
#include <QFrame>

#include <game.h>

namespace Ui {
class gameBox;
}

class gameBox : public QWidget
{
    Q_OBJECT

public:
    explicit gameBox(QWidget *parent = nullptr, game gameData = {});

    void setFocus(bool);

    ~gameBox();

private:
    Ui::gameBox *ui;
    QLabel *top;
    QLabel *bottom1;
    QLabel *bottom2;
    QFrame *thumbnail;
};

#endif // GAMEBOX_H
