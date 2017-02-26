/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *bSave;
    QPushButton *bStart;
    QPushButton *bLoad;
    QPushButton *bExit;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *createServer;
    QLabel *label_2;
    QPushButton *connectServer;
    QLineEdit *connectedIp;
    QLabel *label;

    void setupUi(QDialog *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName(QStringLiteral("Menu"));
        Menu->resize(296, 190);
        gridLayout_2 = new QGridLayout(Menu);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        bSave = new QPushButton(Menu);
        bSave->setObjectName(QStringLiteral("bSave"));

        gridLayout_2->addWidget(bSave, 0, 0, 1, 1);

        bStart = new QPushButton(Menu);
        bStart->setObjectName(QStringLiteral("bStart"));

        gridLayout_2->addWidget(bStart, 0, 1, 1, 1);

        bLoad = new QPushButton(Menu);
        bLoad->setObjectName(QStringLiteral("bLoad"));

        gridLayout_2->addWidget(bLoad, 1, 0, 1, 1);

        bExit = new QPushButton(Menu);
        bExit->setObjectName(QStringLiteral("bExit"));

        gridLayout_2->addWidget(bExit, 1, 1, 1, 1);

        groupBox = new QGroupBox(Menu);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        createServer = new QPushButton(groupBox);
        createServer->setObjectName(QStringLiteral("createServer"));

        gridLayout->addWidget(createServer, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        connectServer = new QPushButton(groupBox);
        connectServer->setObjectName(QStringLiteral("connectServer"));

        gridLayout->addWidget(connectServer, 1, 0, 1, 1);

        connectedIp = new QLineEdit(groupBox);
        connectedIp->setObjectName(QStringLiteral("connectedIp"));

        gridLayout->addWidget(connectedIp, 1, 2, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 2);


        gridLayout_2->addWidget(groupBox, 2, 0, 1, 2);


        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QDialog *Menu)
    {
        Menu->setWindowTitle(QApplication::translate("Menu", "\320\223\320\273\320\260\320\262\320\275\320\276\320\265 \320\274\320\265\320\275\321\216", Q_NULLPTR));
        bSave->setText(QApplication::translate("Menu", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", Q_NULLPTR));
        bStart->setText(QApplication::translate("Menu", "\320\230\320\263\321\200\320\260\321\202\321\214", Q_NULLPTR));
        bLoad->setText(QApplication::translate("Menu", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", Q_NULLPTR));
        bExit->setText(QApplication::translate("Menu", "\320\222\321\213\321\205\320\276\320\264", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Menu", "LAN", Q_NULLPTR));
        createServer->setText(QApplication::translate("Menu", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\201\320\265\321\200\320\262\320\265\321\200", Q_NULLPTR));
        label_2->setText(QApplication::translate("Menu", "Ip:", Q_NULLPTR));
        connectServer->setText(QApplication::translate("Menu", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217 \320\272 \321\201\320\265\321\200\320\262\320\265\321\200\321\203", Q_NULLPTR));
        connectedIp->setText(QApplication::translate("Menu", "localhost", Q_NULLPTR));
        label->setText(QApplication::translate("Menu", "\320\237\320\276\321\200\321\202 \321\201\320\265\321\200\320\262\320\265\321\200\320\260: 6666", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
