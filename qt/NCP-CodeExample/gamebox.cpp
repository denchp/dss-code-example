#include "gamebox.h"
#include "ui_gamebox.h"
#include <QPainter>
#include <QPalette>
#include <QVBoxLayout>
#include <QLabel>

gameBox::gameBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameBox)
{
    ui->setupUi(this);
    this->setLayout(new QVBoxLayout());
    QPalette p = palette();

    p.setColor(QPalette::Background, Qt::black);

    QLabel *t = new QLabel("TOP", this);
    t->setAlignment(Qt::AlignHCenter);

    QLabel *s = new QLabel("[THUMBNAIL]", this);
    s->setAlignment(Qt::AlignHCenter);

    QLabel *b1 = new QLabel("Bottom 1", this);
    b1->setAlignment(Qt::AlignHCenter);

    QLabel *b2 = new QLabel("Bottom 2", this);
    b2->setAlignment(Qt::AlignHCenter);

    this->layout()->addWidget(t);
    this->layout()->addWidget(s);
    this->layout()->addWidget(b1);
    this->layout()->addWidget(b2);

    this->setFixedSize(100, 200);
}

gameBox::~gameBox()
{
    delete ui;
}
