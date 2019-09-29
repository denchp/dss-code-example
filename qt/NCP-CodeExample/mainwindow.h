#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <gamebox.h>
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
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent*) override;
    void onDataReceived(vector<game>);
    apiClient *client;
    gameContainer *container;
    vector<gameBox> games;
    int selectedGame;
};
#endif // MAINWINDOW_H
