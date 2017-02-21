#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QVector>
#include "inventory.h"
#include "item.h"

class DBController : public QObject
{
    Q_OBJECT
public:
    explicit DBController(QObject *parent = 0);
    ~DBController();

    struct ItemData {
        int id;
        QString name;
        QString pixmap;
    };

signals:

public slots:
    void loadInventory();
    void saveInventory(QVector<QVector<Inventory::Items> > inventory);
    void loadItemDataByName(QString name);

private:
    QSqlDatabase dbConnection;
};

#endif // DBCONTROLLER_H
