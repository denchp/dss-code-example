#include "mainwindow.h"
#include <apiclient.h>
#include <vector>
#include <game.h>
#include <QtCore>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <gamebox.h>
#include <gamecontainer.h>
#include <QScrollArea>

MainWindow::MainWindow()
{
    this->setStyleSheet("background:url(:/background.jpg)");
    this->showMaximized();

    // Create central widget
    QWidget * window = new QWidget(this);

    // Create Scroll Area
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidget(window);

    // Set layout
    QHBoxLayout *layout = new QHBoxLayout(scrollArea);
    window->setLayout(layout);

    this->setCentralWidget(window);

    string date = "2019-09-28";

    client->getGames(date, [=](vector<game> g) {
        this->onDataReceived(g);
    });
}

void MainWindow::onDataReceived(vector<game> games) {
    qDebug() << "Games received!";

    for (game g : games) {
        gameBox *newGame = new gameBox(this, g);
        this->centralWidget()->layout()->addWidget(newGame);
    }
}

MainWindow::~MainWindow()
{
}

