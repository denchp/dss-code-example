#include "gamecontainer.h"
#include "ui_gamecontainer.h"
#include <QHBoxLayout>

gameContainer::gameContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameContainer)
{
    ui->setupUi(this);

    QHBoxLayout *boxLayout = new QHBoxLayout();
    this->setLayout(boxLayout);
}

gameContainer::~gameContainer()
{
    delete ui;
}
