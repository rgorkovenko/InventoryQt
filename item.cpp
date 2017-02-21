#include "item.h"
#include <QObject>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QMimeData>
#include <QDebug>
#include <QDrag>
#include <QPainter>
#include <QMainWindow>

Item::Item(QWidget *parent) : QLabel(parent)
{
    this->setScaledContents(true);
}

void Item::onPause(bool active)
{
    this->setEnabled(!active);
}


QString Item::getItemName()
{
    return this->Name;
}

void Item::setItemName(QString name){
    this->Name = name;
}

void Item::setItemByName(QString name)
{
    this->loadItemByNameFromDB(name);
}

void Item::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();

        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Item::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug()<<QString("dragMoveEvent");
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Item::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton){
        return;
    }

    QPixmap pixmap = this->pixmap()->scaled(QSize(this->width(), this->height()));

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    if (this->parent()->objectName() != QString("centralWidget")){
        dataStream << pixmap << qobject_cast<QWidget*>(this->parent())->geometry().center() << this->Name;
    } else {
        dataStream << pixmap << this->pos() << this->Name;
    }
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);


    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos());


    this->setPixmap(tempPixmap);
    if (this->parent()->objectName() == QString("centralWidget")){
        drag->exec(Qt::CopyAction);
        this->show();
        this->setPixmap(pixmap);
    } else {
        drag->exec(Qt::MoveAction);
        this->close();
    }
}
