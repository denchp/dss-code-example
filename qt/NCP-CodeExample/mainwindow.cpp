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
    this->scrollArea = new QScrollArea();
    this->scrollArea->setWidget(window);

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
            qDebug() << "Right arrow press";
            if (this->highlightedGame < this->boxes.size()) {
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
        this->centralWidget()->layout()->addWidget(newGame);
    }

    this->boxes[0]->setFocus(true);
}

MainWindow::~MainWindow()
{
}

