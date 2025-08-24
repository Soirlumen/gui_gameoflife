#ifndef SYMBOLOFLIFE_H
#define SYMBOLOFLIFE_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class symboloflife;
}

class symboloflife : public QDialog
{
    Q_OBJECT
    QLineEdit *editSymboloflife;

public:
    explicit symboloflife(QWidget *parent = nullptr);
    ~symboloflife();
    void setSymbolofLife(char val);
    char getSymbolofLife() const;

private slots:
    void accept();
private:
    Ui::symboloflife *ui;
};

#endif // SYMBOLOFLIFE_H
