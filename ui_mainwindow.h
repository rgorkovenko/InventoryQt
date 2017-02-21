/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <inventory.h>
#include <item.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *bMainMenu;
    Item *label;
    Inventory *tableWidget;
    QFrame *mainMenu;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *saveInventory;
    QPushButton *loadInventory;
    QPushButton *bStart;
    QPushButton *bExit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(694, 453);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        bMainMenu = new QPushButton(centralWidget);
        bMainMenu->setObjectName(QStringLiteral("bMainMenu"));
        bMainMenu->setEnabled(false);
        bMainMenu->setGeometry(QRect(500, 350, 80, 23));
        label = new Item(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);
        label->setGeometry(QRect(470, 60, 131, 131));
        label->setStyleSheet(QStringLiteral("border-image: url(:/default/apple/images/apple.jpg) 0 0 stretch stretch;"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/default/apple/images/apple.jpg")));
        label->setScaledContents(true);
        tableWidget = new Inventory(centralWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEnabled(false);
        tableWidget->setGeometry(QRect(10, 40, 400, 400));
        tableWidget->setMouseTracking(true);
        tableWidget->setAcceptDrops(true);
        tableWidget->setStyleSheet(QLatin1String("Inventory::item:hover\n"
"{\n"
"   background-color: yellow;\n"
"}"));
        tableWidget->setTabKeyNavigation(false);
        tableWidget->setDragEnabled(true);
        tableWidget->setDragDropMode(QAbstractItemView::DragDrop);
        tableWidget->setDefaultDropAction(Qt::MoveAction);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setVisible(false);
        mainMenu = new QFrame(centralWidget);
        mainMenu->setObjectName(QStringLiteral("mainMenu"));
        mainMenu->setGeometry(QRect(0, 0, 701, 30));
        mainMenu->setLayoutDirection(Qt::LeftToRight);
        mainMenu->setStyleSheet(QStringLiteral("background-color: rgb(153, 189, 255);"));
        mainMenu->setFrameShape(QFrame::StyledPanel);
        mainMenu->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(mainMenu);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        saveInventory = new QPushButton(mainMenu);
        saveInventory->setObjectName(QStringLiteral("saveInventory"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(saveInventory->sizePolicy().hasHeightForWidth());
        saveInventory->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(saveInventory);

        loadInventory = new QPushButton(mainMenu);
        loadInventory->setObjectName(QStringLiteral("loadInventory"));
        sizePolicy.setHeightForWidth(loadInventory->sizePolicy().hasHeightForWidth());
        loadInventory->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(loadInventory);

        bStart = new QPushButton(mainMenu);
        bStart->setObjectName(QStringLiteral("bStart"));
        sizePolicy.setHeightForWidth(bStart->sizePolicy().hasHeightForWidth());
        bStart->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(bStart);

        bExit = new QPushButton(mainMenu);
        bExit->setObjectName(QStringLiteral("bExit"));
        sizePolicy.setHeightForWidth(bExit->sizePolicy().hasHeightForWidth());
        bExit->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(bExit);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        bMainMenu->setText(QApplication::translate("MainWindow", "\320\223\320\273\320\260\320\262\320\275\320\276\320\265 \320\274\320\265\320\275\321\216", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "3", Q_NULLPTR));
        saveInventory->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", Q_NULLPTR));
        loadInventory->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", Q_NULLPTR));
        bStart->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214", Q_NULLPTR));
        bExit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
