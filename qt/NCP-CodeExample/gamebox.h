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
    explicit gameBox(game g, QWidget *parent = nullptr);

    void setFocus(bool);

    ~gameBox() override;

private:
    Ui::gameBox *ui;

    QLabel *top;
    QLabel *bottom1;
    QLabel *bottom2;
    QFrame *thumbnail;
};

#endif // GAMEBOX_H
