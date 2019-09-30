/********************************************************************************
** Form generated from reading UI file 'gamewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWIDGET_H
#define UI_GAMEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gameWidget
{
public:

    void setupUi(QWidget *gameWidget)
    {
        if (gameWidget->objectName().isEmpty())
            gameWidget->setObjectName(QString::fromUtf8("gameWidget"));
        gameWidget->resize(400, 300);
        gameWidget->setMinimumSize(QSize(150, 200));
        gameWidget->setAutoFillBackground(true);

        retranslateUi(gameWidget);

        QMetaObject::connectSlotsByName(gameWidget);
    } // setupUi

    void retranslateUi(QWidget *gameWidget)
    {
        gameWidget->setWindowTitle(QCoreApplication::translate("gameWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gameWidget: public Ui_gameWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWIDGET_H
