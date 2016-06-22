/********************************************************************************
** Form generated from reading UI file 'Loader.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADER_H
#define UI_LOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Loader
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *loader;
    QLabel *text;

    void setupUi(QDialog *Loader)
    {
        if (Loader->objectName().isEmpty())
            Loader->setObjectName(QStringLiteral("Loader"));
        Loader->resize(400, 130);
        verticalLayout = new QVBoxLayout(Loader);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        loader = new QLabel(Loader);
        loader->setObjectName(QStringLiteral("loader"));
        loader->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(loader);

        text = new QLabel(Loader);
        text->setObjectName(QStringLiteral("text"));
        text->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(text);


        retranslateUi(Loader);

        QMetaObject::connectSlotsByName(Loader);
    } // setupUi

    void retranslateUi(QDialog *Loader)
    {
        Loader->setWindowTitle(QApplication::translate("Loader", "Dialog", 0));
        loader->setText(QApplication::translate("Loader", "TextLabel", 0));
        text->setText(QApplication::translate("Loader", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class Loader: public Ui_Loader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADER_H
