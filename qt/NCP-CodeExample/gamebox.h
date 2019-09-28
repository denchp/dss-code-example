#ifndef GAMEBOX_H
#define GAMEBOX_H

#include <QWidget>

namespace Ui {
class gameBox;
}

class gameBox : public QWidget
{
    Q_OBJECT

public:
    explicit gameBox(QWidget *parent = nullptr);
    ~gameBox();

private:
    Ui::gameBox *ui;
};

#endif // GAMEBOX_H
