#include "dbcontroller.h"
#include <QDir>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DBController::DBController(QObject *parent) : QObject(parent)
{
    this->dbConnection = QSqlDatabase::addDatabase("QSQLITE");

    this->dbConnection.setDatabaseName(QDir::currentPath() + QString("/database/database.db"));
    bool ok = this->dbConnection.open();
    if (!ok){
        QSqlError error = this->dbConnection.lastError();
        qDebug() << error;
    }
}

DBController::~DBController()
{
    this->dbConnection.close();
    this->dbConnection.removeDatabase(QDir::currentPath() + QString("/database/database.db"));
}

void DBController::loadInventory()
{
    QVector<QVector<Inventory::Items> > result;

    // Определяем количество строк и столбцов, чтобы потом не париться с циклами
    QSqlQuery *query = new QSqlQuery(this->dbConnection);
    query->exec(QString("Select Max(Row) as Rows, Max(Column) as Columns From Inventory"));
    int countRows = 0;
    int countColumns = 0;
    while (query->next()){
        countRows = query->value(QString("Rows")).toInt() + 1;
        countColumns = query->value(QString("Columns")).toInt() + 1;
    }

    //если база пустая, вернем пустой список, чтоб не делать дальнейших обработок
    if (countRows + countColumns == 0) {
        return;
    }

    //инициализировали пустыми значениями чтоб можно было перемещаться по индексу
    for (int i = 0; i < countRows; i++) {
        QVector<Inventory::Items> tmp;
        for(int j = 0; j < countColumns; j++){
            Inventory::Items item;
            item.count = 0;
            item.name = QString("empty");
            tmp.push_back(item);
        }
        result.push_back(tmp);
    }

    query = new QSqlQuery(this->dbConnection);
    query->exec(QString("Select Items.Name, Items.Pixmap, Row, Column, Count From Inventory left join Items on Inventory.ItemId = Items.Id Order By Row, Column"));

    while (query->next()){
        int row = query->value(QString("Row")).toInt();
        int column = query->value(QString("Column")).toInt();
        QString name = query->value(QString("Name")).toString();
        if(name.size() == 0){
            name = QString("empty");
        }

        result[row][column].count = query->value(QString("Count")).toInt();
        result[row][column].name = name;
    }

    qobject_cast<Inventory*>(sender())->loadData(result);
}

void DBController::saveInventory(QVector<QVector<Inventory::Items> > inventory)
{
    //Собираем список имен всех предметов в инвентаре (без повторений)
    QVector<QString> names;

    for (int i = 0; i < inventory.size(); i++){
        for (int j = 0; j < inventory[0].size(); j++){
            QString item = QString("'") + inventory[i][j].name + QString("'");
            if (!names.contains(item)){
                names.push_back(item);
            }
        }
    }
    QString queryNames;
    if (names.size()>1)
    foreach (QString name, names) {
        queryNames += QString(",") + name ;
    }
    queryNames.replace(0,1, QString(""));

    //Получаем индексы этих предметов
    QSqlQuery *query = new QSqlQuery(this->dbConnection);
    query->exec(QString("SELECT Id, Name FROM Items WHERE Items.Name IN (%1)").arg(queryNames));

    QVector<ItemData> bindNamesId;
    while (query->next()){
        ItemData tmp;
        tmp.id= query->value(QString("Id")).toInt();
        tmp.name = query->value(QString("Name")).toString();

        bindNamesId.push_back(tmp);
    }

    //очищаем таблицу в инвентаре
    QSqlQuery *delquery = new QSqlQuery(this->dbConnection);
    delquery->exec(QString("DELETE FROM Inventory;"));

    //записываем инвентарь в базу
    QString sql;
    sql = QString("INSERT INTO Inventory (ItemId, Row, Column, Count) Values ");
    for (int i = 0; i < inventory.size(); i++){
        QString tmp;
        for (int j = 0; j < inventory[0].size(); j++){
            int row = i;
            int column = j;
            QString id = QString("Null");
            int count = inventory[i][j].count;
            for (int k = 0; k < bindNamesId.count(); k ++){
                if (inventory[i][j].name == bindNamesId[k].name){
                    id = QString::number(bindNamesId[k].id);
                }
            }
            tmp += QString("(") + id + QString(", ")
                    + QString::number(row) + QString(", ")
                    + QString::number(column) + QString(", ")
                    + QString::number(count) + QString("), ");
        }
        sql += tmp;
    }
    sql.replace(sql.size()-2, 2, QString(";"));

    QSqlQuery *insertquery = new QSqlQuery(this->dbConnection);
    insertquery->exec(sql);
}

void DBController::loadItemDataByName(QString name)
{
    QSqlQuery *query = new QSqlQuery(this->dbConnection);
    query->exec(QString("Select Name, Pixmap from Items where Items.Name = '%1'").arg(name));

    query->next();
    Item *item = qobject_cast<Item*>(sender());
    QWidget *itemParent = qobject_cast<QWidget*>(item->parent());

    item->setGeometry(0, 0, itemParent->width(), itemParent->height());
    QPixmap pixmap(query->value(QString("Pixmap")).toString());

    item->setPixmap(pixmap);
}
