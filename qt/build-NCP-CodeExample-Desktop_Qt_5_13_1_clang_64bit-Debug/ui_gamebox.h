/********************************************************************************
** Form generated from reading UI file 'gamebox.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEBOX_H
#define UI_GAMEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gameBox
{
public:

    void setupUi(QWidget *gameBox)
    {
        if (gameBox->objectName().isEmpty())
            gameBox->setObjectName(QString::fromUtf8("gameBox"));
        gameBox->resize(805, 590);
        gameBox->setMinimumSize(QSize(0, 0));
        gameBox->setAutoFillBackground(true);
        gameBox->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(gameBox);

        QMetaObject::connectSlotsByName(gameBox);
    } // setupUi

    void retranslateUi(QWidget *gameBox)
    {
        gameBox->setWindowTitle(QCoreApplication::translate("gameBox", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gameBox: public Ui_gameBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEBOX_H
