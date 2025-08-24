/********************************************************************************
** Form generated from reading UI file 'drawgame.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWGAME_H
#define UI_DRAWGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_drawgame
{
public:

    void setupUi(QWidget *drawgame)
    {
        if (drawgame->objectName().isEmpty())
            drawgame->setObjectName("drawgame");
        drawgame->resize(400, 300);

        retranslateUi(drawgame);

        QMetaObject::connectSlotsByName(drawgame);
    } // setupUi

    void retranslateUi(QWidget *drawgame)
    {
        drawgame->setWindowTitle(QCoreApplication::translate("drawgame", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Drawgame: public Ui_drawgame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWGAME_H
