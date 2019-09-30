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

const string STYLES = "QLabel { color: white} .focused QLabel { font-weight: bold }";

gameBox::gameBox(game g, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameBox)
{
    ui->setupUi(this);
    this->setLayout(new QVBoxLayout());
    this->layout()->setAlignment(Qt::AlignHCenter);

    this->top = new QLabel(this);
    top->setMaximumHeight(24);
    top->setAlignment(Qt::AlignHCenter);

    QSizePolicy p = top->sizePolicy();
    p.setRetainSizeWhenHidden(true);
    top->setSizePolicy(p);

    top->hide();
    top->setText(QString::fromStdString(g.away.name + " (" + to_string(g.away.score) + ") @ " +
                                        g.home.name + " (" + to_string(g.home.score) + ")"));

    this->thumbnail = new QLabel();
    thumbnail->sizePolicy().setRetainSizeWhenHidden(true);
    thumbnail->setFixedSize(WIDTH, HEIGHT);
    thumbnail->setScaledContents(true);
    thumbnail->setStyleSheet("background: black");
    thumbnail->setAlignment(Qt::AlignHCenter);

    this->bottomTop = new QLabel(QString::fromStdString(g.recap.title));
    bottomTop->setSizePolicy(p);

    bottomTop->setMaximumHeight(24);
    bottomTop->hide();
    bottomTop->setWordWrap(true);
    bottomTop->setAlignment(Qt::AlignHCenter);

    this->bottomMiddle = new QLabel(
                QString::fromStdString(g.away.name +
                                       " (" + to_string(g.away.record.wins) + "-" +
                                       to_string(g.away.record.losses) + ") "));bottomMiddle->setMaximumHeight(24);
    bottomMiddle->setAlignment(Qt::AlignHCenter);
    bottomMiddle->setSizePolicy(p);
    bottomMiddle->hide();

    this->bottomBottom = new QLabel(
                QString::fromStdString(g.home.name +
                                       " (" + to_string(g.home.record.wins) + "-" +
                                       to_string(g.home.record.losses) + ") "));
    bottomBottom->setMaximumHeight(24);
    bottomBottom->setSizePolicy(p);
    bottomBottom->hide();
    bottomBottom->setAlignment(Qt::AlignHCenter);

    client->getImage(g.recap.imgUrl, [=](QByteArray d) { onImageReceived(d); });

    this->layout()->addWidget(top);
    this->layout()->addWidget(thumbnail);
    this->layout()->addWidget(bottomTop);
    this->layout()->addWidget(bottomMiddle);
    this->layout()->addWidget(bottomBottom);

    this->adjustSize();
    this->setStyleSheet(QString::fromStdString(STYLES));
}

void gameBox::setFocus(bool hasFocus) {
    if (hasFocus) {
        this->setProperty("class", "focused");
        qDebug() << "Size up";
        this->thumbnail->setFixedSize(WIDTH * 1.5, HEIGHT * 1.5);
        top->show();
        bottomTop->show();
        bottomBottom->show();
        bottomMiddle->show();

    } else {
        qDebug() << "Size down";
        this->setProperty("class", "");
        this->thumbnail->setFixedSize(WIDTH, HEIGHT);
        top->hide();
        bottomTop->hide();
        bottomBottom->hide();
        bottomMiddle->hide();
    }

    this->setStyleSheet(QString::fromStdString(STYLES));
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
    delete top;
    delete thumbnail;
    delete bottomTop;
    delete bottomMiddle;
    delete bottomBottom;
}
