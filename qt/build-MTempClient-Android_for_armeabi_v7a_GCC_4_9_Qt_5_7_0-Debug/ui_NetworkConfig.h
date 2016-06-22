/********************************************************************************
** Form generated from reading UI file 'NetworkConfig.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKCONFIG_H
#define UI_NETWORKCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NetworkConfig
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QCheckBox *netKeyShowChecbox;
    QLineEdit *netKeyLineEdit;
    QLineEdit *usernameLineEdit;
    QLabel *netKeylabel;
    QLineEdit *boardPortLineEdit;
    QLineEdit *boardIPLineEdit;
    QLabel *boardPortLabel;
    QLabel *netNameLabel;
    QLabel *password2Label;
    QLabel *boardIPLabel;
    QLabel *usernameLabel;
    QLineEdit *netNameLineEdit;
    QLineEdit *password1LineEdit;
    QLabel *password1Label;
    QLineEdit *password2LineEdit;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *configureButton;
    QPushButton *clearButton;
    QPushButton *abortButton;

    void setupUi(QDialog *NetworkConfig)
    {
        if (NetworkConfig->objectName().isEmpty())
            NetworkConfig->setObjectName(QStringLiteral("NetworkConfig"));
        NetworkConfig->resize(378, 321);
        verticalLayout_2 = new QVBoxLayout(NetworkConfig);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(NetworkConfig);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        netKeyShowChecbox = new QCheckBox(frame_2);
        netKeyShowChecbox->setObjectName(QStringLiteral("netKeyShowChecbox"));

        gridLayout->addWidget(netKeyShowChecbox, 2, 1, 1, 1);

        netKeyLineEdit = new QLineEdit(frame_2);
        netKeyLineEdit->setObjectName(QStringLiteral("netKeyLineEdit"));
        netKeyLineEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(netKeyLineEdit, 1, 1, 1, 1);

        usernameLineEdit = new QLineEdit(frame_2);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));

        gridLayout->addWidget(usernameLineEdit, 5, 1, 1, 1);

        netKeylabel = new QLabel(frame_2);
        netKeylabel->setObjectName(QStringLiteral("netKeylabel"));

        gridLayout->addWidget(netKeylabel, 1, 0, 1, 1);

        boardPortLineEdit = new QLineEdit(frame_2);
        boardPortLineEdit->setObjectName(QStringLiteral("boardPortLineEdit"));

        gridLayout->addWidget(boardPortLineEdit, 4, 1, 1, 1);

        boardIPLineEdit = new QLineEdit(frame_2);
        boardIPLineEdit->setObjectName(QStringLiteral("boardIPLineEdit"));

        gridLayout->addWidget(boardIPLineEdit, 3, 1, 1, 1);

        boardPortLabel = new QLabel(frame_2);
        boardPortLabel->setObjectName(QStringLiteral("boardPortLabel"));

        gridLayout->addWidget(boardPortLabel, 4, 0, 1, 1);

        netNameLabel = new QLabel(frame_2);
        netNameLabel->setObjectName(QStringLiteral("netNameLabel"));

        gridLayout->addWidget(netNameLabel, 0, 0, 1, 1);

        password2Label = new QLabel(frame_2);
        password2Label->setObjectName(QStringLiteral("password2Label"));

        gridLayout->addWidget(password2Label, 7, 0, 1, 1);

        boardIPLabel = new QLabel(frame_2);
        boardIPLabel->setObjectName(QStringLiteral("boardIPLabel"));

        gridLayout->addWidget(boardIPLabel, 3, 0, 1, 1);

        usernameLabel = new QLabel(frame_2);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));

        gridLayout->addWidget(usernameLabel, 5, 0, 1, 1);

        netNameLineEdit = new QLineEdit(frame_2);
        netNameLineEdit->setObjectName(QStringLiteral("netNameLineEdit"));

        gridLayout->addWidget(netNameLineEdit, 0, 1, 1, 1);

        password1LineEdit = new QLineEdit(frame_2);
        password1LineEdit->setObjectName(QStringLiteral("password1LineEdit"));
        password1LineEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(password1LineEdit, 6, 1, 1, 1);

        password1Label = new QLabel(frame_2);
        password1Label->setObjectName(QStringLiteral("password1Label"));

        gridLayout->addWidget(password1Label, 6, 0, 1, 1);

        password2LineEdit = new QLineEdit(frame_2);
        password2LineEdit->setObjectName(QStringLiteral("password2LineEdit"));
        password2LineEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(password2LineEdit, 7, 1, 1, 1);


        verticalLayout->addWidget(frame_2);


        verticalLayout_2->addWidget(groupBox);

        frame = new QFrame(NetworkConfig);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        configureButton = new QPushButton(frame);
        configureButton->setObjectName(QStringLiteral("configureButton"));
        configureButton->setEnabled(false);

        horizontalLayout->addWidget(configureButton);

        clearButton = new QPushButton(frame);
        clearButton->setObjectName(QStringLiteral("clearButton"));

        horizontalLayout->addWidget(clearButton);

        abortButton = new QPushButton(frame);
        abortButton->setObjectName(QStringLiteral("abortButton"));

        horizontalLayout->addWidget(abortButton);


        verticalLayout_2->addWidget(frame);

        QWidget::setTabOrder(netNameLineEdit, netKeyLineEdit);
        QWidget::setTabOrder(netKeyLineEdit, boardIPLineEdit);
        QWidget::setTabOrder(boardIPLineEdit, boardPortLineEdit);
        QWidget::setTabOrder(boardPortLineEdit, usernameLineEdit);
        QWidget::setTabOrder(usernameLineEdit, password1LineEdit);
        QWidget::setTabOrder(password1LineEdit, password2LineEdit);
        QWidget::setTabOrder(password2LineEdit, configureButton);
        QWidget::setTabOrder(configureButton, clearButton);
        QWidget::setTabOrder(clearButton, abortButton);
        QWidget::setTabOrder(abortButton, netKeyShowChecbox);

        retranslateUi(NetworkConfig);

        QMetaObject::connectSlotsByName(NetworkConfig);
    } // setupUi

    void retranslateUi(QDialog *NetworkConfig)
    {
        NetworkConfig->setWindowTitle(QApplication::translate("NetworkConfig", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("NetworkConfig", "Configura Rete", 0));
        netKeyShowChecbox->setText(QApplication::translate("NetworkConfig", "Mostra", 0));
        netKeylabel->setText(QApplication::translate("NetworkConfig", "Chiave Rete", 0));
        boardPortLabel->setText(QApplication::translate("NetworkConfig", "Porta", 0));
        netNameLabel->setText(QApplication::translate("NetworkConfig", "Nome Rete", 0));
        password2Label->setText(QApplication::translate("NetworkConfig", "Conferma Password", 0));
        boardIPLabel->setText(QApplication::translate("NetworkConfig", "IP Centralina", 0));
        usernameLabel->setText(QApplication::translate("NetworkConfig", "Nome Utente", 0));
        password1Label->setText(QApplication::translate("NetworkConfig", "Password", 0));
        configureButton->setText(QApplication::translate("NetworkConfig", "Configura", 0));
        clearButton->setText(QApplication::translate("NetworkConfig", "Azzera", 0));
        abortButton->setText(QApplication::translate("NetworkConfig", "Annulla", 0));
    } // retranslateUi

};

namespace Ui {
    class NetworkConfig: public Ui_NetworkConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKCONFIG_H
