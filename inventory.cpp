#include "inventory.h"
#include "mainwindow.h"
#include <QMediaPlayer>
#include <QDir>

Inventory::Inventory(QWidget *parent) : QTableWidget(parent)
{
    //инициализация таблицы
    this->initData();

    //заполнение таблицы пустыми виджетами, чтобы не вылетало при обращении к пустой ячейке
    this->initWidgets();

    setDragDropMode(DragDropMode::InternalMove);
}

void Inventory::initData()
{
    for (int i = 0; i < this->sizeItems; i++) {
        QVector<Inventory::Items> tmp;
        for(int j = 0; j < this->sizeItems; j++){
            Inventory::Items item;
            item.count = 0;
            item.name = QString("empty");
            tmp.push_back(item);
        }
        this->items.push_back(tmp);
    }
}

void Inventory::initWidgets()
{
    this->setColumnCount(this->sizeItems);
    this->setRowCount(this->sizeItems);

    for (int i = 0; i < this->rowCount(); i++){
        for (int j = 0; j < this->columnCount(); j++){
            QLabel *lab = new QLabel(this);
            this->setCellWidget(i, j, lab);
        }
    }
}

int Inventory::getInvSize()
{
    return this->sizeItems;
}

void Inventory::onPause(bool active)
{
    this->setEnabled(!active);
}

void Inventory::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Inventory::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Inventory::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if(event->source()!=this){
            QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
            QDataStream dataStream(&itemData, QIODevice::ReadOnly);

            this->addItem(event->pos(), &dataStream);
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Inventory::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton){
        QPoint coord = QPoint(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
        if (this->items[coord.x()][coord.y()].count > 1){
            this->items[coord.x()][coord.y()].count -= 1;

            QWidget *item = this->cellWidget(coord.x(), coord.y());
            QLabel *tmp = qobject_cast<QLabel*>(item->children().at(1));
            tmp->setText(QString::number(this->items[coord.x()][coord.y()].count));

            this->eatApple();
        } else {
            if (this->cellWidget(coord.x(), coord.y())->children().count() == 2){
                this->eatApple();
            }
            this->items[coord.x()][coord.y()].count = 0;
            this->items[coord.x()][coord.y()].name = QString("empty");
            QWidget *empty = new QWidget(this);
            this->setCellWidget(coord.x(), coord.y(), empty);
        }
    }
}

void Inventory::eatApple()
{
    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl("qrc:/default/apple/sound/eatapple.mp3"));
    player->setVolume(50);
    player->play();
}

void Inventory::addItem(QPoint locate, QDataStream *dataStream)
{
    QPixmap pixmap;
    QPoint offset;
    QString name;
    *dataStream >> pixmap >> offset >> name;

    QPoint from = QPoint(this->rowAt((offset).y()), this->columnAt((offset).x()));
    QPoint to = QPoint(this->rowAt((locate).y()), this->columnAt((locate).x()));

    QWidget *cell = new QWidget(this);
    cell->setObjectName("MyCell");
    Item *newItem = new Item(cell);

    newItem->setItemName(name);
    newItem->setObjectName("label");
    newItem->setPixmap(pixmap);

    QLabel *count = new QLabel(cell);
    count->setAlignment(Qt::AlignRight);
    count->setGeometry(this->columnWidth(0)-cell->width()-1,this->rowHeight(0)-cell->height()/2,count->width(),count->height());

    this->setCellWidget(this->rowAt(locate.y()), this->columnAt(locate.x()), cell);
    this->moveItems(from, to);
}

void Inventory::moveItems(QPoint from, QPoint to)
{
    if (from.x()<0 || from.y()<0){
        QWidget *item = this->cellWidget(to.x(), to.y());
        Item *tmpItem = qobject_cast<Item*>(item->children().at(0));
        QLabel *tmp = qobject_cast<QLabel*>(item->children().at(1));

        this->items[to.x()][to.y()].count += 1;
        this->items[to.x()][to.y()].name = tmpItem->getItemName();
        tmp->setText(QString::number(this->items[to.x()][to.y()].count));
    } else {
        if (from == to){
            QWidget *toItem = this->cellWidget(to.x(), to.y());
            QLabel *toTmp = qobject_cast<QLabel*>(toItem->children().at(1));
            toTmp->setText(QString::number(this->items[to.x()][to.y()].count));

            return;
        }
        this->items[to.x()][to.y()].count += this->items[from.x()][from.y()].count;

        this->items[from.x()][from.y()].count = 0;
        this->items[from.x()][from.y()].name = QString("empty");

        QWidget *toItem = this->cellWidget(to.x(), to.y());
        Item *tmpItem = qobject_cast<Item*>(toItem->children().at(0));
        QLabel *toTmp = qobject_cast<QLabel*>(toItem->children().at(1));

        this->items[to.x()][to.y()].name = tmpItem->getItemName();
        toTmp->setText(QString::number(this->items[to.x()][to.y()].count));

        QWidget *fromItem = this->cellWidget(from.x(), from.y());
        QLabel *fromTmp = qobject_cast<QLabel*>(fromItem->children().at(1));
        delete fromTmp;
    }
}

QVector<QVector<Inventory::Items> > Inventory::getItems()
{
    return this->items;
}

void Inventory::loadData(QVector<QVector<Inventory::Items> > items)
{
    this->items = items;

    //сбрасываем все виджеты
    this->initWidgets();

    for (int i = 0; i < items.count(); i++){
        for (int j = 0; j < items[0].count(); j++){
            if (this->items[i][j].count > 0){
                //заполняем главные итемы и создаем предмет в ячейке инвентаря
                this->items[i][j].count = items[i][j].count;
                this->items[i][j].name = items[i][j].name;

                QWidget *cell = new QWidget(this);
                cell->setObjectName("MyCell");
                Item *newItem = new Item(cell);

                newItem->setItemName(items[i][j].name);
                newItem->setObjectName("label");

                QLabel *count = new QLabel(cell);
                count->setAlignment(Qt::AlignRight);
                count->setGeometry(this->columnWidth(0)-cell->width()-1,this->rowHeight(0)-cell->height()/2,count->width(),count->height());
                count->setText(QString::number(items[i][j].count));
                this->setCellWidget(i, j, cell);
            }
        }
    }
    this->setItemsConnetions();
}

void Inventory::printInv()
{
    for (int i = 0; i < this->items.size(); i++) {
        QString str;
        for(int j = 0; j < this->items[0].size(); j++){
            str += this->items[i][j].name + QString(":") + QString::number(this->items[i][j].count) + QString(" ");
        }
        qDebug() << str;
    }
    qDebug() << QString("Size y: ") << this->items.size();
    qDebug() << QString("Size x: ") << this->items[0].size();
    qDebug() << QString("--------------");
}
