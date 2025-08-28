#ifndef SETIINGS_H
#define SETIINGS_H

#include <QDialog>

namespace Ui
{
    class Setiings;
    class QColor;
}

class Setiings : public QDialog
{
    Q_OBJECT
    QColor pom = Qt::white;

public:
    explicit Setiings(QWidget *parent = nullptr);
    ~Setiings();
    QColor getColorCell();
    int getSizeCell() const;
    int getNextFrame() const;
    void preSetColor(QColor col);
    void preSetSC(int i);
    void preSetNF(int i);

public slots:
    void pickColor();
    void accept();

private:
    Ui::Setiings *ui;
};

#endif // SETIINGS_H
