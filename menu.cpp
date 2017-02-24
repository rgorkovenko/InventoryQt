#include "menu.h"
#include "ui_menu.h"
#include <QDebug>

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_bExit_clicked()
{
    bExitClicked();
    this->close();
}

void Menu::on_bStart_clicked()
{
    bStartClicked();
    this->close();
}

void Menu::on_bSave_clicked()
{
    bSaveClicked();
    this->close();
}

void Menu::on_bLoad_clicked()
{
    bLoadClicked();
    this->close();
}

void Menu::on_connectServer_clicked()
{
    bConnectServerClicked();
}

void Menu::on_createServer_clicked()
{
    bCreateServerClicked();
    this->close();
}
