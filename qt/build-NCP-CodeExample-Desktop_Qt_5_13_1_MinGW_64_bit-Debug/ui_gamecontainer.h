/********************************************************************************
** Form generated from reading UI file 'gamecontainer.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMECONTAINER_H
#define UI_GAMECONTAINER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gameContainer
{
public:

    void setupUi(QWidget *gameContainer)
    {
        if (gameContainer->objectName().isEmpty())
            gameContainer->setObjectName(QString::fromUtf8("gameContainer"));
        gameContainer->resize(371, 166);

        retranslateUi(gameContainer);

        QMetaObject::connectSlotsByName(gameContainer);
    } // setupUi

    void retranslateUi(QWidget *gameContainer)
    {
        gameContainer->setWindowTitle(QCoreApplication::translate("gameContainer", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gameContainer: public Ui_gameContainer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMECONTAINER_H
