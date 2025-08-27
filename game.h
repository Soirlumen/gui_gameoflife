#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <vector>
#include "logic.h"
#include "symboloflife.h"
#include "setiings.h"
#include "drawgame.h"
//#include "paramofnewgame.h"

class QAction;
class QToolBar;
class QCloseEvent;
class QPainter;
class QGraphicsScene;
class QGraphicsView;
class QTimer;
class QMenu;
class QColor;

class game : public QMainWindow
{
    Q_OBJECT
    //herni promenne
    const int SIZEOFWINDOWX=1200;
    const int SIZEOFWINDOWY=650;
    int sizeofsq=20;
    char symbolforlivecell='#';
    int nextFrameTime=600;
    QColor clrlivingcell=Qt::darkMagenta;

    int sizeX;
    int sizeY;
    Game *thatGame;
    bool isAlive;
    QTimer *timer;

    //menickove veci
    QMenu *openmennu;
    QToolBar *toolbar;
    Drawgame *dwidget=nullptr;

    //prochazeni souboru
    QString workdir;
    QAction *actopengamefromtxt;

    //akce hry
    QAction *actNextGeneration;
    QAction *actQuit;
    QAction *actLetTheLifeGo;
    QAction *actLetTheLifeStop;
    QAction *actOpenSettings;
    QAction *actSaveGameboard;

    //zobrazovani okenka
    QGraphicsScene *scene;
    QGraphicsView *view;
    std::vector<std::vector<Cell>> field;
    void setupwindow();
    void setupGame();
    void closeEvent(QCloseEvent *event);
    void setupConnections();
    void paint(CMatrix mat);
    void resizeWindow();

public:
    game(QWidget *parent = nullptr);
    ~game();
public slots:
    void nextGeneration();
    void letTheLifeGo();
    void letTheLifeStop();
    void openGame();
    void openSetting();
    void newGameboard();
    void loadGame(const SQMatrix &m, char symbol);
private slots:
     void receiveMatrix(const QString &m, char symbol);
};
#endif // GAME_H
