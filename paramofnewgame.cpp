#include "paramofnewgame.h"
#include "ui_paramofnewgame.h"
#include <QDialog>
#include <QString>
#include <QMessageBox>

ParamOfNewGame::ParamOfNewGame(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ParamOfNewGame)
{
    ui->setupUi(this);
}

ParamOfNewGame::~ParamOfNewGame()
{
    delete ui;
}

int ParamOfNewGame::getHeight() const
{
    return ui->spinHeight->value();
}

int ParamOfNewGame::getWidth() const
{
    return ui->spinWidth->value();
}

char ParamOfNewGame::getSymbol() const
{
    return ui->lineEditSymbol->text().at(0).toLatin1();
}

void ParamOfNewGame::setHeight(int i)
{
//ui->spinBoxFrameDelay->setValue(i);
    ui->spinHeight->setValue(i);
}

void ParamOfNewGame::setWidth(int i)
{
ui->spinWidth->setValue(i);
}

void ParamOfNewGame::setSymbol(char val)
{
ui->lineEditSymbol->setText(QString("%1").arg(val));
}

void ParamOfNewGame::accept()
{
    if(ui->lineEditSymbol->text().isEmpty()){
        QMessageBox::warning(this, tr("eror"), tr("type a symbol!!!"));
        return;
    }
    QDialog::accept();
}
