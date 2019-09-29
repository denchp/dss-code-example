#include "gamebox.h"
#include "ui_gamebox.h"
#include <game.h>

#include <QtDebug>
#include <QPainter>
#include <QPalette>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>

const int HEIGHT = 100;
const int WIDTH = 200;

gameBox::gameBox(game g, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameBox)
{
    ui->setupUi(this);
    this->setLayout(new QVBoxLayout());
    this->layout()->setAlignment(Qt::AlignHCenter);

    QPalette p = palette();
    p.setColor(QPalette::Background, Qt::black);

    QPalette labelPallete = palette();
    p.setColor(QPalette::Background, Qt::yellow);
    p.setColor(QPalette::Foreground, Qt::blue);

    top = new QLabel(this);
    top->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    top->setPalette(labelPallete);
    top->setMaximumHeight(24);
    top->setText(QString::fromStdString(g.away.name));

    thumbnail = new QFrame();
    thumbnail->setFixedSize(WIDTH, HEIGHT);
    thumbnail->setStyleSheet("background: black");

    bottom1 = new QLabel(this);
    bottom1->setAlignment(Qt::AlignHCenter);
    bottom1->setMaximumHeight(24);

    bottom2 = new QLabel("Bottom 2", this);
    bottom2->setAlignment(Qt::AlignHCenter);
    bottom2->setMaximumHeight(24);

    this->layout()->addWidget(top);
    this->layout()->addWidget(thumbnail);
    this->layout()->addWidget(bottom1);
    this->layout()->addWidget(bottom2);
    this->adjustSize();
    this->setStyleSheet(".focused QLabel { font-weight: bold }");

}

void gameBox::setFocus(bool hasFocus) {
    if (hasFocus) {
        this->setProperty("class", "focused");
        qDebug() << "Size up";
        this->thumbnail->setFixedSize(WIDTH * 1.5, HEIGHT * 1.5);
    } else {
        qDebug() << "Size down";
        this->setProperty("class", "");
        this->thumbnail->setFixedSize(WIDTH, HEIGHT);
    }

    this->setStyleSheet(".focused QLabel { font-weight: bold }");
}

gameBox::~gameBox()
{
    delete ui;
}
