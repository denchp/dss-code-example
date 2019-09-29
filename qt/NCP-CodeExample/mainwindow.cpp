#include "mainwindow.h"
#include <vector>

#include <QtCore>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QStyle>
#include <QScrollArea>
#include <QMainWindow>
#include <QKeyEvent>
#include <QPixmap>
#include <QPalette>

#include <apiclient.h>
#include <game.h>
#include <gamebox.h>
#include <gamecontainer.h>

MainWindow::MainWindow() : QMainWindow()
{
    this->showMaximized();
    this->setStyleSheet("* { background: transparent }");

    // Create the main window
    QFrame *window = new QFrame();
    window->setProperty("class", "mainWindow");
    window->setStyleSheet("QFrame.mainWindow { background: url(:/background.jpg) }");
    window->setLayout(new QHBoxLayout());

    // Create Scroll Area and GameContainer
    this->gameContainer = new QFrame();
    this->scrollArea = new QScrollArea(this);
    this->scrollArea->setWidgetResizable(true);
    this->scrollArea->setWidget(this->gameContainer);
    window->layout()->addWidget(this->scrollArea);

    // Set layout
    QHBoxLayout *layout = new QHBoxLayout();
    this->gameContainer->setLayout(layout);

    this->setCentralWidget(window);
    this->grabKeyboard();

    string date = "2019-09-28";

    client->getGames(date, [=](vector<game> g) {
        this->onDataReceived(g);
    });
}

void MainWindow::keyPressEvent(QKeyEvent * event) {
    // Removed existing highlight
    this->boxes[this->highlightedGame]->setFocus(false);
    qDebug() << "Moving from: " << this->highlightedGame;

    switch(event->key()) {
        case Qt::Key_Left:
            qDebug() << "Left arrow press";
            if (this->highlightedGame > 0) {
                qDebug() << "Scrolling by " << this->boxes[0]->width();
                this->scrollArea->scroll(this->boxes[0]->width(), 0);
                this->highlightedGame -= 1;
            }
            break;
        case Qt::Key_Right:
            qDebug() << "Right arrow press" << this->boxes.size();
            if (this->highlightedGame < this->boxes.size() - 1) {
                qDebug() << "Scrolling by -" << this->boxes[0]->width();
                this->scrollArea->scroll(-1 * this->boxes[0]->width(), 0);
                this->highlightedGame += 1;
            }
            break;
    }

    qDebug() << "Moving to: " << this->highlightedGame;
    //Apply the new focus property
    this->boxes[this->highlightedGame]->setFocus(true);
}

void MainWindow::onDataReceived(vector<game> games) {
    qDebug() << "Games received!";

    for (game g : games) {
        gameBox *newGame = new gameBox(g, this);
        this->boxes.push_back(newGame);
        this->gameContainer->layout()->addWidget(newGame);
    }

    this->boxes[0]->setFocus(true);
}

MainWindow::~MainWindow()
{
}

