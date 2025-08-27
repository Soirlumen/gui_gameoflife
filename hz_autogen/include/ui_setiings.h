/********************************************************************************
** Form generated from reading UI file 'setiings.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETIINGS_H
#define UI_SETIINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setiings
{
public:
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *lblColorCell;
    QLabel *lblSizeCell;
    QLabel *lblFrameDelay;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditColorCell;
    QToolButton *toolButton;
    QSpinBox *spinBoxSizeofCell;
    QSpinBox *spinBoxFrameDelay;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Setiings)
    {
        if (Setiings->objectName().isEmpty())
            Setiings->setObjectName("Setiings");
        Setiings->resize(296, 189);
        Setiings->setModal(false);
        verticalLayoutWidget_3 = new QWidget(Setiings);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(20, 20, 252, 152));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lblColorCell = new QLabel(verticalLayoutWidget_3);
        lblColorCell->setObjectName("lblColorCell");

        verticalLayout->addWidget(lblColorCell);

        lblSizeCell = new QLabel(verticalLayoutWidget_3);
        lblSizeCell->setObjectName("lblSizeCell");

        verticalLayout->addWidget(lblSizeCell);

        lblFrameDelay = new QLabel(verticalLayoutWidget_3);
        lblFrameDelay->setObjectName("lblFrameDelay");

        verticalLayout->addWidget(lblFrameDelay);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lineEditColorCell = new QLineEdit(verticalLayoutWidget_3);
        lineEditColorCell->setObjectName("lineEditColorCell");
        lineEditColorCell->setEnabled(false);

        horizontalLayout->addWidget(lineEditColorCell);

        toolButton = new QToolButton(verticalLayoutWidget_3);
        toolButton->setObjectName("toolButton");

        horizontalLayout->addWidget(toolButton);


        verticalLayout_4->addLayout(horizontalLayout);

        spinBoxSizeofCell = new QSpinBox(verticalLayoutWidget_3);
        spinBoxSizeofCell->setObjectName("spinBoxSizeofCell");
        spinBoxSizeofCell->setMinimum(1);
        spinBoxSizeofCell->setMaximum(100);
        spinBoxSizeofCell->setValue(20);

        verticalLayout_4->addWidget(spinBoxSizeofCell);

        spinBoxFrameDelay = new QSpinBox(verticalLayoutWidget_3);
        spinBoxFrameDelay->setObjectName("spinBoxFrameDelay");
        spinBoxFrameDelay->setMinimum(100);
        spinBoxFrameDelay->setMaximum(10000);
        spinBoxFrameDelay->setSingleStep(100);
        spinBoxFrameDelay->setValue(500);

        verticalLayout_4->addWidget(spinBoxFrameDelay);


        horizontalLayout_2->addLayout(verticalLayout_4);


        verticalLayout_5->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget_3);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout_5->addWidget(buttonBox);

#if QT_CONFIG(shortcut)
        lblColorCell->setBuddy(toolButton);
        lblSizeCell->setBuddy(spinBoxSizeofCell);
        lblFrameDelay->setBuddy(spinBoxFrameDelay);
#endif // QT_CONFIG(shortcut)

        retranslateUi(Setiings);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Setiings, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Setiings, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Setiings);
    } // setupUi

    void retranslateUi(QDialog *Setiings)
    {
        Setiings->setWindowTitle(QCoreApplication::translate("Setiings", "Dialog", nullptr));
        lblColorCell->setText(QCoreApplication::translate("Setiings", "Color of living cells", nullptr));
        lblSizeCell->setText(QCoreApplication::translate("Setiings", "Size of one cell (px)", nullptr));
        lblFrameDelay->setText(QCoreApplication::translate("Setiings", "Frame delay (ms)", nullptr));
        toolButton->setText(QCoreApplication::translate("Setiings", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Setiings: public Ui_Setiings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETIINGS_H
