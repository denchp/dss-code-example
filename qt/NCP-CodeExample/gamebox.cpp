#include "gamebox.h"
#include "ui_gamebox.h"
#include <game.h>
#include <apiclient.h>

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

    QLabel *top = new QLabel(this);
    top->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    top->setPalette(labelPallete);
    top->setMaximumHeight(24);
    top->setText(QString::fromStdString(g.away.name + " @ " + g.home.name));

    thumbnail = new QLabel();
    thumbnail->setFixedSize(WIDTH, HEIGHT);
    thumbnail->setScaledContents(true);
    thumbnail->setStyleSheet("background: black");
    thumbnail->setAlignment(Qt::AlignHCenter);


    QLabel *bottomTop = new QLabel(QString::fromStdString(g.recap.title));
    bottomTop->setAlignment(Qt::AlignHCenter);
    bottomTop->setMaximumHeight(48);
    bottomTop->setMaximumWidth(WIDTH);
    bottomTop->setWordWrap(true);

    QLabel *bottomMiddle =
            new QLabel(
                QString::fromStdString(g.away.name +
                                       " (" + to_string(g.away.record.wins) + "-" +
                                       to_string(g.away.record.losses) + ") " + to_string(g.away.score)));

    bottomMiddle->setAlignment(Qt::AlignHCenter);
    bottomMiddle->setMaximumHeight(24);

    QLabel *bottomBottom =
            new QLabel(
                QString::fromStdString(g.home.name +
                                       " (" + to_string(g.home.record.wins) + "-" +
                                       to_string(g.home.record.losses) + ") " + to_string(g.away.score)));
    bottomBottom->setAlignment(Qt::AlignHCenter);
    bottomBottom->setMaximumHeight(24);

    client->getImage(g.recap.imgUrl, [=](QByteArray d) { onImageReceived(d); });


    this->layout()->addWidget(top);
    this->layout()->addWidget(thumbnail);
    this->layout()->addWidget(bottomTop);
    this->layout()->addWidget(bottomMiddle);
    this->layout()->addWidget(bottomBottom);

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

void gameBox::onImageReceived(QByteArray data) {
    qDebug() << "Image received: " << data.size();
    QPixmap pixmap;
    pixmap.loadFromData(data);
    this->thumbnail->setPixmap(pixmap);
}

gameBox::~gameBox()
{
    delete ui;
}
