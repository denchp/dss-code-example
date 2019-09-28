#ifndef GAMECONTAINER_H
#define GAMECONTAINER_H

#include <QWidget>
#include <QHBoxLayout>

namespace Ui {
class gameContainer;
}

class gameContainer : public QWidget
{
    Q_OBJECT

public:
    explicit gameContainer(QWidget *parent = nullptr);
    ~gameContainer();

private:
    Ui::gameContainer *ui;
};

#endif // GAMECONTAINER_H
