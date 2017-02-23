#ifndef MENU_H
#define MENU_H

#include <QDialog>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

signals:
    void bExitClicked();
    void bStartClicked();
    void bSaveClicked();
    void bLoadClicked();

private slots:
    void on_bExit_clicked();

    void on_bStart_clicked();

    void on_bSave_clicked();

    void on_bLoad_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
