/********************************************************************************
** Form generated from reading UI file 'paramofnewgame.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMOFNEWGAME_H
#define UI_PARAMOFNEWGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParamOfNewGame
{
public:
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEditSymbol;
    QSpinBox *spinHeight;
    QSpinBox *spinWidth;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ParamOfNewGame)
    {
        if (ParamOfNewGame->objectName().isEmpty())
            ParamOfNewGame->setObjectName("ParamOfNewGame");
        ParamOfNewGame->resize(337, 222);
        verticalLayoutWidget_3 = new QWidget(ParamOfNewGame);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(20, 20, 291, 181));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(verticalLayoutWidget_3);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        label_3 = new QLabel(verticalLayoutWidget_3);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        label_2 = new QLabel(verticalLayoutWidget_3);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        lineEditSymbol = new QLineEdit(verticalLayoutWidget_3);
        lineEditSymbol->setObjectName("lineEditSymbol");
        lineEditSymbol->setMaxLength(1);

        verticalLayout_2->addWidget(lineEditSymbol);

        spinHeight = new QSpinBox(verticalLayoutWidget_3);
        spinHeight->setObjectName("spinHeight");
        spinHeight->setMinimum(3);
        spinHeight->setMaximum(1000);

        verticalLayout_2->addWidget(spinHeight);

        spinWidth = new QSpinBox(verticalLayoutWidget_3);
        spinWidth->setObjectName("spinWidth");
        spinWidth->setMinimum(3);
        spinWidth->setMaximum(1000);

        verticalLayout_2->addWidget(spinWidth);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget_3);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(ParamOfNewGame);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ParamOfNewGame, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ParamOfNewGame, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ParamOfNewGame);
    } // setupUi

    void retranslateUi(QDialog *ParamOfNewGame)
    {
        ParamOfNewGame->setWindowTitle(QCoreApplication::translate("ParamOfNewGame", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ParamOfNewGame", "symbol of life cell", nullptr));
        label_3->setText(QCoreApplication::translate("ParamOfNewGame", "height", nullptr));
        label_2->setText(QCoreApplication::translate("ParamOfNewGame", "width", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParamOfNewGame: public Ui_ParamOfNewGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMOFNEWGAME_H
