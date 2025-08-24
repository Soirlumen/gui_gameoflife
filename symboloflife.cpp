#include "symboloflife.h"
#include "ui_symboloflife.h"
#include <QChar>
#include <QMessageBox>
#include <QString>


symboloflife::symboloflife(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::symboloflife)
{
    ui->setupUi(this);
}

symboloflife::~symboloflife()
{
    delete ui;
}

void symboloflife::setSymbolofLife(char val)
{
    ui->editSymboloflife->setText(QString("%1").arg(val));
}

char symboloflife::getSymbolofLife() const
{
    return ui->editSymboloflife->text().at(0).toLatin1();
}

void symboloflife::accept()
{
    if(ui->editSymboloflife->text().isEmpty()){
        QMessageBox::warning(this, tr("eror"), tr("vyplnte znak zivota!!"));
        return;
    }

    QDialog::accept();
}

