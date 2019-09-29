#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

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
    QScrollArea *scrollArea;
    QFrame *gameContainer;

    void keyPressEvent(QKeyEvent*) override;
    void onDataReceived(vector<game>);
    apiClient *client;
    vector<gameBox*> boxes;
    ulong highlightedGame = 0;
};
#endif // MAINWINDOW_H
