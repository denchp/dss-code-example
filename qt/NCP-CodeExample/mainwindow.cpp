#include "mainwindow.h"
#include <vector>

#include <QtCore>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
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

    // Create the main window
    QWidget *window = new QWidget();
    window->setProperty("class", "mainWindow");
    window->setStyleSheet("QWidget.mainWindow { background: url(:/background.jpg) }");
    window->setLayout(new QVBoxLayout());

    // Create Scroll Area and GameContainer
    this->gameContainer = new QFrame();

    this->scrollArea = new QScrollArea();
    this->scrollArea->setWidgetResizable(true);
    this->scrollArea->setWidget(this->gameContainer);
    this->scrollArea->setStyleSheet("background-color: transparent");
    this->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
    if (this->boxes.size() == 0) { // avoid crashing if someone mashes the keyboard before we've recieved games back
        return;
    }

    // Remove existing highlight
    this->boxes[this->highlightedGame]->setFocus(false);
    qDebug() << "Moving from: " << this->highlightedGame;

    switch(event->key()) {
        case Qt::Key_Left:
            qDebug() << "Left arrow press";
            if (this->highlightedGame > 0) {
                this->highlightedGame -= 1;
            }
            break;
        case Qt::Key_Right:
            qDebug() << "Right arrow press";
            if (this->highlightedGame < this->boxes.size() - 1) {
                this->highlightedGame += 1;
            }
            break;
    }

    // Scroll to the new item, and set the focus to 'enlarge' it.
    this->scrollArea->ensureWidgetVisible(this->boxes[this->highlightedGame], this->boxes[0]->width() / 2, 0);
    qDebug() << "Moving to: " << this->highlightedGame;
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

