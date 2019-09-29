#include "mainwindow.h"
#include <vector>

#include <QtCore>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QStyle>
#include <QScrollArea>
#include <QMainWindow>
#include <QKeyEvent>

#include <apiclient.h>
#include <game.h>
#include <gamebox.h>
#include <gamecontainer.h>

MainWindow::MainWindow() : QMainWindow()
{
    this->showMaximized();

    // Create central widget
    QFrame * window = new QFrame(this);
    window->setProperty("class", "mainWindow");
    window->setStyleSheet("QFrame.mainWindow { background: url(:/background.jpg) }");

    // Create Scroll Area
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidget(window);

    // Set layout
    QHBoxLayout *layout = new QHBoxLayout(scrollArea);
    window->setLayout(layout);

    this->setCentralWidget(window);

    this->grabKeyboard();

    string date = "2019-09-28";

    client->getGames(date, [=](vector<game> g) {
        this->onDataReceived(g);
    });
}

void MainWindow::keyPressEvent(QKeyEvent * event) {
    switch(event->key()) {
        case Qt::Key_Left:
            qDebug() << "Left arrow press";
            break;
        case Qt::Key_Right:
            qDebug() << "Right arrow press";
            break;
    }
}
void MainWindow::onDataReceived(vector<game> games) {
    qDebug() << "Games received!";

    for (game g : games) {
        gameBox *newGame = new gameBox(this, g);
//        newGame->setFocus(true);
        this->centralWidget()->layout()->addWidget(newGame);
    }
}

MainWindow::~MainWindow()
{
}

