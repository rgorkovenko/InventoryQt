#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    menu_ui = new Menu();
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


    connect(menu_ui, menu_ui->bStartClicked, this, startGame);
    connect(menu_ui, menu_ui->bExitClicked, this, exitGame);
    connect(menu_ui, menu_ui->bSaveClicked, this, saveInventory);
    connect(menu_ui, menu_ui->bLoadClicked, this, loadInventory);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exitGame()
{
    close();
}

void MainWindow::startGame()
{
    this->pause(false);
}

void MainWindow::on_bMainMenu_clicked()
{
    pause(true);
    menu_ui->exec();
}

void MainWindow::on_pause()
{

}

void MainWindow::saveInventory()
{
    saveGame(ui->tableWidget->getItems());
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setText("Сохранение завершено");
    msgBox->exec();
    pause(false);
}

void MainWindow::loadInventory()
{
    ui->tableWidget->loadDataFromDB();
    startGame();
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
