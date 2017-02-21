#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QDebug>
#include <QMessageBox>

#include <inventory.h>
#include <dbcontroller.h>

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

signals:
    void pause(bool);
    void saveGame(QVector<QVector<Inventory::Items> > items);

private slots:
    void on_bExit_clicked();

    void on_bStart_clicked();

    void on_bMainMenu_clicked();

    void on_pause();

    void on_saveInventory_clicked();

    void on_loadInventory_clicked();

    void setItemsConnections();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
