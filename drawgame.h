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
    const int SIZE_OF_SQUARE=20;

    QString workdir;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QString vec_to_QStr(char ch);

    QMenu *savemennu;
    QAction *actSaveGame;
    QAction *actNewGame;
    QAction *actOpenGame;
    QAction *actOpenPattern;
    QAction *actRunGame;
    QMenuBar *mnuBar;

public:
    explicit Drawgame(QWidget *parent = nullptr,Qt::WindowFlags f = Qt::Window);//,char ch='#', int x=10, int y=10);
    ~Drawgame();
    void setupScene();
    void setupMenu();
    void updateGameboard(char newsym, int newh, int neww);
signals:
    void sendMatrix(const QString &matrix, char symbol);
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    Ui::Drawgame *ui;
    CMatrix currentPattern;
    bool insertingPattern = false;
    bool boardExisting=false;
    bool anyLivingCell=false;
private slots:
    void writeFile();
    void drawGrid();
    void setupConnects();
    public slots:
    void openNewGameboard();
    void openExistingGameboard();
    void insertPattern();
    void runThisInSecondTabheheh();
};


#endif // DRAWGAME_H
