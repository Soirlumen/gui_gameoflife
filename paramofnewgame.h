#ifndef PARAMOFNEWGAME_H
#define PARAMOFNEWGAME_H

#include <QDialog>

namespace Ui
{
    class ParamOfNewGame;
}

class ParamOfNewGame : public QDialog
{
    Q_OBJECT

public:
    explicit ParamOfNewGame(QWidget *parent = nullptr);
    ~ParamOfNewGame();
    int getHeight() const;
    int getWidth() const;
    char getSymbol() const;
    void setHeight(int i);
    void setWidth(int i);
    void setSymbol(char val);

private:
    Ui::ParamOfNewGame *ui;
private slots:
    void accept();
};

#endif // PARAMOFNEWGAME_H
