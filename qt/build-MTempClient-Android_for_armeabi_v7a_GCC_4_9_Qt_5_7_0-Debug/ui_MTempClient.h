/********************************************************************************
** Form generated from reading UI file 'MTempClient.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MTEMPCLIENT_H
#define UI_MTEMPCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MTempClient
{
public:
    QAction *actionConfigura;
    QAction *actionLogin;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QMenu *menuOpzioni;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MTempClient)
    {
        if (MTempClient->objectName().isEmpty())
            MTempClient->setObjectName(QStringLiteral("MTempClient"));
        MTempClient->resize(967, 654);
        actionConfigura = new QAction(MTempClient);
        actionConfigura->setObjectName(QStringLiteral("actionConfigura"));
        actionLogin = new QAction(MTempClient);
        actionLogin->setObjectName(QStringLiteral("actionLogin"));
        centralWidget = new QWidget(MTempClient);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);

        MTempClient->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MTempClient);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 967, 21));
        menuOpzioni = new QMenu(menuBar);
        menuOpzioni->setObjectName(QStringLiteral("menuOpzioni"));
        MTempClient->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MTempClient);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MTempClient->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MTempClient);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MTempClient->setStatusBar(statusBar);

        menuBar->addAction(menuOpzioni->menuAction());
        menuOpzioni->addAction(actionConfigura);
        menuOpzioni->addAction(actionLogin);

        retranslateUi(MTempClient);

        QMetaObject::connectSlotsByName(MTempClient);
    } // setupUi

    void retranslateUi(QMainWindow *MTempClient)
    {
        MTempClient->setWindowTitle(QApplication::translate("MTempClient", "MTempClient", 0));
        actionConfigura->setText(QApplication::translate("MTempClient", "Configura Rete", 0));
        actionConfigura->setShortcut(QApplication::translate("MTempClient", "Ctrl+S", 0));
        actionLogin->setText(QApplication::translate("MTempClient", "Login", 0));
        actionLogin->setShortcut(QApplication::translate("MTempClient", "Ctrl+L", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MTempClient", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MTempClient", "Tab 2", 0));
        menuOpzioni->setTitle(QApplication::translate("MTempClient", "Opzioni", 0));
    } // retranslateUi

};

namespace Ui {
    class MTempClient: public Ui_MTempClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MTEMPCLIENT_H
