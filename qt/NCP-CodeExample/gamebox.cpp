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
#include <QPropertyAnimation>

#define HEIGHT 150
#define WIDTH 266

gameBox::gameBox(game g, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameBox)
{
    ui->setupUi(this);
    this->setLayout(new QVBoxLayout());
    this->layout()->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
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
    thumbnail->setScaledContents(true);
    thumbnail->setStyleSheet("background: black");
    thumbnail->setAlignment(Qt::AlignVCenter);
    thumbnail->resize(WIDTH, HEIGHT);
    this->setMinimumSize(0,0);
    this->setMaximumSize(static_cast<int>(WIDTH * 20), static_cast<int>(HEIGHT * 20));

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


    QSize *startSize = new QSize(WIDTH, HEIGHT);
    QSize *endSize = new QSize(QSize(static_cast<int>(WIDTH * 1.5), static_cast<int>(HEIGHT * 1.5)));

    this->animation = new QPropertyAnimation(thumbnail, "size");
    animation->setDuration(200);
    animation->setStartValue(*startSize);
    animation->setEndValue(*endSize);
    connect(animation, &QPropertyAnimation::valueChanged, this, [=](QVariant size) {
        thumbnail->setMinimumSize(size.toSize());
    });

    this->reverseAnimation = new QPropertyAnimation(thumbnail, "size");
    reverseAnimation->setDuration(200);
    reverseAnimation->setStartValue(*endSize);
    reverseAnimation->setEndValue(*startSize);
    connect(reverseAnimation, &QPropertyAnimation::valueChanged, this, [=](QVariant size) {
        thumbnail->setMinimumSize(size.toSize());
    });

    client->getImage(g.recap.imgUrl, [=](QByteArray d) { onImageReceived(d); });

    this->layout()->addWidget(top);
    this->layout()->addWidget(thumbnail);
    this->layout()->addWidget(bottomTop);
    this->layout()->addWidget(bottomMiddle);
    this->layout()->addWidget(bottomBottom);

    this->adjustSize();
    this->setStyleSheet(QString::fromStdString("QLabel { color: white; font-weight: bold }"));
}


void gameBox::setFocus(bool hasFocus) {
    if (hasFocus) {
        qDebug() << "Size up";
        this->animation->start();
        top->show();
        bottomTop->show();
        bottomBottom->show();
        bottomMiddle->show();
    } else {
        qDebug() << "Size down";
        this->reverseAnimation->start();
        top->hide();
        bottomTop->hide();
        bottomBottom->hide();
        bottomMiddle->hide();
    }

    this->adjustSize();
}

void gameBox::onImageReceived(QByteArray data) {
    qDebug() << "Image received: " << data.size();
    QPixmap pixmap;
    pixmap.loadFromData(data);
    this->image = pixmap.scaledToWidth(WIDTH);
    this->thumbnail->setPixmap(image);
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
