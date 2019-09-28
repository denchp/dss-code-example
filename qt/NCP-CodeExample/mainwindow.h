#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <game.h>
#include <apiclient.h>
#include <gamecontainer.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void onDataReceived(vector<game>);
    apiClient *client;
    gameContainer *container;
};
#endif // MAINWINDOW_H
