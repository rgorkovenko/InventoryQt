#ifndef INVENTORY_H
#define INVENTORY_H

#include <QTableWidget>
#include <QVector>
#include <QPoint>
#include <QDebug>
#include <QDropEvent>
#include <QMimeData>
#include <item.h>
#include <QPixmap>
#include <QDrag>
#include <QVBoxLayout>
#include <QLabel>
#include <QMediaPlayer>

class Inventory : public QTableWidget
{
    Q_OBJECT
public:
    explicit Inventory(QWidget *parent = 0);

    struct Items{
        int count;
        QString name;
    };

    int getInvSize();

signals:
    void saveInventory(QVector<QVector<Items> >);
    void loadDataFromDB();
    void setItemsConnetions();

public slots:
    void onPause(bool active);
    void addItem(QPoint locate, QDataStream *dataStream);
    void moveItems(QPoint from, QPoint to);
    QVector<QVector<Items> > getItems();
    void loadData(QVector<QVector<Items> > items);
    void printInv();
    void eatApple();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QVector<QVector<Items> > items;
    int sizeItems = 3;
    QMediaPlayer *player;

    void initData();
    void initWidgets();
};

#endif // INVENTORY_H
