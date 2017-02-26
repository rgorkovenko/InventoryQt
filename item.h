#ifndef ITEM_H
#define ITEM_H

#include <QLabel>

class Item : public QLabel
{
    Q_OBJECT
public:
    explicit Item(QWidget *parent = 0);


signals:
    void loadItemByNameFromDB(QString);
    void debugLog(QString data);

public slots:
    void onPause(bool active);
    QString getItemName();
    void setItemByName(QString name);
    void setItemName(QString name);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QString Name;
};

#endif // ITEM_H
