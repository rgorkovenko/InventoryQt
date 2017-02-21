#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int i = 0; i < ui->tableWidget->columnCount(); i++){
        for (int j = 0; j < ui->tableWidget->rowCount(); j++){
            ui->tableWidget->setItem(i,j, new QTableWidgetItem());
        }
    }
    ui->label->setItemName(QString("Apple"));

    //инициализация базы данных
    dbcontroller = new DBController(this);

    connect(this, pause, ui->tableWidget, &Inventory::onPause);
    connect(this, pause, ui->label, &Item::onPause);
    connect(this, pause, ui->bMainMenu, [=](bool active){ui->bMainMenu->setEnabled(!active);});
    connect(this, saveGame, dbcontroller, &DBController::saveInventory);

    connect(ui->tableWidget, ui->tableWidget->loadDataFromDB, dbcontroller, &DBController::loadInventory);
    connect(ui->label, ui->label->loadItemByNameFromDB, dbcontroller, &DBController::loadItemDataByName);
    connect(ui->tableWidget, ui->tableWidget->setItemsConnetions, this, &MainWindow::setItemsConnections);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bExit_clicked()
{
    close();
}

void MainWindow::on_bStart_clicked()
{
    QPropertyAnimation* animation = new QPropertyAnimation(ui->mainMenu, "geometry");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setEndValue(QRect(0,0,this->width(),0));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    this->pause(false);
}

void MainWindow::on_bMainMenu_clicked()
{
    QPropertyAnimation* animation = new QPropertyAnimation(ui->mainMenu, "geometry");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setEndValue(QRect(0,0,this->width(),30));
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    pause(true);
}

void MainWindow::on_pause()
{

}

void MainWindow::on_saveInventory_clicked()
{
    saveGame(ui->tableWidget->getItems());
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setText("Сохранение завершено");
    msgBox->exec();
}

void MainWindow::on_loadInventory_clicked()
{
    ui->tableWidget->loadDataFromDB();
    ui->bStart->click();
}

void MainWindow::setItemsConnections()
{
    //обходим все элементы и ставим им нужные сигналы
    for (int i = 0; i < ui->tableWidget->getInvSize(); i++){
        for (int j = 0; j < ui->tableWidget->getInvSize(); j++){
            QWidget *widget = ui->tableWidget->cellWidget(i, j);
            if (widget->children().count()>0){
                Item *item = qobject_cast<Item*>(widget->children().at(0));
                connect(item, item->loadItemByNameFromDB, this->dbcontroller, &DBController::loadItemDataByName);

                item->loadItemByNameFromDB(item->getItemName());
            }
        }
    }
}
