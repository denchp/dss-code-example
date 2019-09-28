#include "mainwindow.h"
#include <apiclient.h>
#include <vector>
#include <game.h>
#include <QtCore>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <gamebox.h>
#include <gamecontainer.h>

MainWindow::MainWindow()
{
    // Set layout
    QHBoxLayout *layout = new QHBoxLayout;


    // Set layout in QWidget
    QWidget *window = new QWidget();
    window->setLayout(layout);
    window->setStyleSheet("background:url(:/background.jpg)");

    this->setCentralWidget(window);

    string date = "2019-09-28";

    client->getGames(date, [=](vector<game> g) {
        this->onDataReceived(g);
    });
}

void MainWindow::onDataReceived(vector<game> games) {
    qDebug() << "Games received!";

    for (game g : games) {
        gameBox *newGame = new gameBox();
        this->centralWidget()->layout()->addWidget(newGame);
    }
}

MainWindow::~MainWindow()
{
}

