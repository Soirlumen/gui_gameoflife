#ifndef DRAWGAME_H
#define DRAWGAME_H

#include <QWidget>
#include "helper.h"
#include "paramofnewgame.h"
#include "symboloflife.h"

class QGraphicsRectItem;
class QGraphicsScene;
class QGraphicsView;
class QMenu;
class QAction;
class QMenuBar;

namespace Ui {
class Drawgame;
}

class Drawgame : public QWidget
{
    Q_OBJECT
    std::vector<std::vector<QGraphicsRectItem*>> cellRects;
    int x;
    int y;
    char symbol;
    int size_of_square=20;
    QString workdir;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QString vec_to_QStr(char ch);
    QMenu *savemennu;
    QAction *actSaveGame;
    QAction *actNewGame;
    QAction *actOpenGame;
    QAction *actRunGame;
    QMenuBar *mnuBar;

public:
    explicit Drawgame(QWidget *parent = nullptr);//,char ch='#', int x=10, int y=10);
    ~Drawgame();
    void setupScene();
    void setupMenu();
    void updateGameboard(char newsym, int newh, int neww);
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    Ui::Drawgame *ui;
private slots:
    void writeFile();
    void drawGrid();
    void setupConnects();
public slots:
    void openNewGameboard();
    void openExistingGameboard();
};


#endif // DRAWGAME_H
