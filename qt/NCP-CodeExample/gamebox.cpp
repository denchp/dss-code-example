#include "gamebox.h"
#include "ui_gamebox.h"
#include <QPainter>
#include <QPalette>
#include <QVBoxLayout>
#include <QLabel>
#include <game.h>

gameBox::gameBox(QWidget *parent, game gameData) :
    QWidget(parent),
    ui(new Ui::gameBox)
{
    ui->setupUi(this);
    this->setLayout(new QVBoxLayout());
    QPalette p = palette();

    p.setColor(QPalette::Background, Qt::black);

    QLabel *t = new QLabel(QString::fromStdString(gameData.away.name + " @ " + gameData.home.name), this);
    t->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QLabel *s = new QLabel("[THUMBNAIL]", this);
    s->setAlignment(Qt::AlignHCenter);

    QLabel *b1 = new QLabel(QString::fromStdString(gameData.away.name), this);
    b1->setAlignment(Qt::AlignHCenter);

    QLabel *b2 = new QLabel("Bottom 2", this);
    b2->setAlignment(Qt::AlignHCenter);

    this->layout()->addWidget(t);
    this->layout()->addWidget(s);
    this->layout()->addWidget(b1);
    this->layout()->addWidget(b2);

    this->setFixedSize(400, 200);
}

gameBox::~gameBox()
{
    delete ui;
}
