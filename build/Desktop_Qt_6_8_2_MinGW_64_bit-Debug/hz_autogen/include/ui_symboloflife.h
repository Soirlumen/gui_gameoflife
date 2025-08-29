/********************************************************************************
** Form generated from reading UI file 'symboloflife.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYMBOLOFLIFE_H
#define UI_SYMBOLOFLIFE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_symboloflife
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lbldialogsol;
    QLineEdit *editSymboloflife;
    QDialogButtonBox *btnSOL;

    void setupUi(QDialog *symboloflife)
    {
        if (symboloflife->objectName().isEmpty())
            symboloflife->setObjectName("symboloflife");
        symboloflife->resize(277, 134);
        verticalLayoutWidget = new QWidget(symboloflife);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 20, 246, 93));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lbldialogsol = new QLabel(verticalLayoutWidget);
        lbldialogsol->setObjectName("lbldialogsol");

        verticalLayout->addWidget(lbldialogsol);

        editSymboloflife = new QLineEdit(verticalLayoutWidget);
        editSymboloflife->setObjectName("editSymboloflife");
        editSymboloflife->setMaxLength(1);

        verticalLayout->addWidget(editSymboloflife);

        btnSOL = new QDialogButtonBox(verticalLayoutWidget);
        btnSOL->setObjectName("btnSOL");
        btnSOL->setOrientation(Qt::Orientation::Horizontal);
        btnSOL->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(btnSOL);

#if QT_CONFIG(shortcut)
        lbldialogsol->setBuddy(editSymboloflife);
#endif // QT_CONFIG(shortcut)

        retranslateUi(symboloflife);
        QObject::connect(btnSOL, &QDialogButtonBox::accepted, symboloflife, qOverload<>(&QDialog::accept));
        QObject::connect(btnSOL, &QDialogButtonBox::rejected, symboloflife, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(symboloflife);
    } // setupUi

    void retranslateUi(QDialog *symboloflife)
    {
        symboloflife->setWindowTitle(QCoreApplication::translate("symboloflife", "Dialog", nullptr));
        lbldialogsol->setText(QCoreApplication::translate("symboloflife", "Which symbol represents live cells? :)", nullptr));
#if QT_CONFIG(tooltip)
        editSymboloflife->setToolTip(QCoreApplication::translate("symboloflife", "only one character", nullptr));
#endif // QT_CONFIG(tooltip)
        editSymboloflife->setPlaceholderText(QString());
    } // retranslateUi

};

namespace Ui {
    class symboloflife: public Ui_symboloflife {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYMBOLOFLIFE_H
