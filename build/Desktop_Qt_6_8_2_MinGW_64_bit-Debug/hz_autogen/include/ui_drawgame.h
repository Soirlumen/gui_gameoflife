/********************************************************************************
** Form generated from reading UI file 'drawgame.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWGAME_H
#define UI_DRAWGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Drawgame
{
public:

    void setupUi(QWidget *Drawgame)
    {
        if (Drawgame->objectName().isEmpty())
            Drawgame->setObjectName("Drawgame");
        Drawgame->resize(400, 300);

        retranslateUi(Drawgame);

        QMetaObject::connectSlotsByName(Drawgame);
    } // setupUi

    void retranslateUi(QWidget *Drawgame)
    {
        Drawgame->setWindowTitle(QCoreApplication::translate("Drawgame", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Drawgame: public Ui_Drawgame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWGAME_H
