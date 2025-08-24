#include "setiings.h"
#include "ui_setiings.h"
#include <QColorDialog>
#include <QMessageBox>

Setiings::Setiings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Setiings)
{
    ui->setupUi(this);
    connect(ui->toolButton,&QToolButton::clicked,this,&Setiings::pickColor);
}

Setiings::~Setiings()
{
    delete ui;
}

QColor Setiings::getColorCell()
{
    return pom;
}

int Setiings::getSizeCell() const
{
    return ui->spinBoxSizeofCell->value();
}

int Setiings::getNextFrame() const
{
    return ui->spinBoxFrameDelay->value();
}

void Setiings::preSetColor(QColor col)
{
    ui->lineEditColorCell->setText(col.toRgb().name());
    pom=col;
}

void Setiings::preSetSC(int i)
{
ui->spinBoxSizeofCell->setValue(i);
}

void Setiings::preSetNF(int i)
{
ui->spinBoxFrameDelay->setValue(i);
}

void Setiings::pickColor()
{
    QColor color=QColorDialog::getColor(Qt::white,this,"Choose color");
    if(color.isValid()){
        ui->lineEditColorCell->setText(color.toRgb().name());
        pom=color;
    }
}

void Setiings::accept()
{
    if(ui->lineEditColorCell->text().isEmpty()){
        QMessageBox::warning(this, tr("eror"), tr("vyberte barvicku!!"));
        return;
    }
    QDialog::accept();
}
