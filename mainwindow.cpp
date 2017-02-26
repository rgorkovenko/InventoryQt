#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    server = new Server();
    client = new Client();

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

    //коннекты основной логики
    connect(this, pause, ui->tableWidget, &Inventory::onPause);
    connect(this, pause, ui->label, &Item::onPause);
    connect(this, pause, ui->bMainMenu, [=](bool active){ui->bMainMenu->setEnabled(!active);});

    connect(client, client->loadInventoryFromServer, ui->tableWidget, ui->tableWidget->loadData);

    connect(this, saveGame, dbcontroller, &DBController::saveInventory);
    connect(ui->tableWidget, ui->tableWidget->loadDataFromDB, dbcontroller, &DBController::loadInventory);
    connect(ui->label, ui->label->loadItemByNameFromDB, dbcontroller, &DBController::loadItemDataByName);
    connect(ui->tableWidget, ui->tableWidget->setItemsConnetions, this, &MainWindow::setItemsConnections);

    //коннекты для отладочной информации
    connect(client, client->debugLog, this, showDebugLog);
    connect(server, server->debugLog, this, showDebugLog);
    connect(ui->tableWidget, ui->tableWidget->debugLog, this, showDebugLog);
    connect(ui->label, ui->label->debugLog, this, showDebugLog);

    pause(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exitGame()
{
    this->close();
}

void MainWindow::startGame()
{
    this->pause(false);
}

void MainWindow::on_bMainMenu_clicked()
{
    pause(true);
    menu_ui = new Menu();
    connect(menu_ui, menu_ui->bStartClicked, this, startGame);
    connect(menu_ui, menu_ui->bExitClicked, this, exitGame);
    connect(menu_ui, menu_ui->bSaveClicked, this, saveInventory);
    connect(menu_ui, menu_ui->bLoadClicked, this, loadInventory);
    connect(menu_ui, menu_ui->bCreateServerClicked, this, createServer);
    connect(menu_ui, menu_ui->bConnectServerClicked, this, connectServer);
    connect(menu_ui, menu_ui->destroyed, this, [=](){pause(false);});

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
                connect(item, item->debugLog, this, showDebugLog);

                item->loadItemByNameFromDB(item->getItemName());
            }
        }
    }
}

void MainWindow::createServer()
{
    if (!server->getHasCreated()){
        server->createServer();
        server->startListen(6666);

        if(!client->getHasCreated()){
            client->createConnection(QString("localhost"));
            connect(ui->tableWidget, ui->tableWidget->inventoryChanged, this, sendDataToServer);
        }
    }

    pause(false);
}

void MainWindow::connectServer(QString ip)
{
    if (!client->getHasCreated()){
        client->createConnection(ip);
        connect(ui->tableWidget, ui->tableWidget->inventoryChanged, this, sendDataToServer);
    } else {
        showDebugLog(QString("Клиент уже подключен!"));
    }


}

void MainWindow::sendDataToServer(){
    QVector<QVector<Inventory::Items> > items = ui->tableWidget->getItems();

    //сериализуем данные таблицы в json строку и отправим на сервер
    QJsonArray array;
    for (int i = 0; i < items.length(); i++){
        QJsonArray tmp;
        for (int j = 0; j < items[0].length(); j++){
            QJsonObject item;
            item["Name"] = items[i][j].name;
            item["Count"] = items[i][j].count;
            QJsonValue value(item);
            tmp.append(value);
        }
        array.append(tmp);
    }

    QJsonDocument doc(array);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    client->sendData(strJson);
}

void MainWindow::showDebugLog(QString data){
    this->ui->debugLog->setText(ui->debugLog->toPlainText() + QString("\n") + data);

    //скроллим вниз
    QTextCursor c = ui->debugLog->textCursor();
    c.movePosition(QTextCursor::End);
    ui->debugLog->setTextCursor(c);
}
