#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QDebug>
#include <QMessageBox>

#include <inventory.h>
#include <dbcontroller.h>
#include <menu.h>
#include <server.h>
#include <client.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DBController *dbcontroller;
    Menu *menu_ui;
    Client *client;
    Server *server;

signals:
    void pause(bool);
    void saveGame(QVector<QVector<Inventory::Items> > items);

private slots:
    void on_pause();
    void on_bMainMenu_clicked();
    void setItemsConnections();
    void createServer();
    void connectServer();

private:
    Ui::MainWindow *ui;

    void exitGame();
    void startGame();
    void saveInventory();
    void loadInventory();
};

#endif // MAINWINDOW_H
