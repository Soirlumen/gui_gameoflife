#include "game.h"
#include <QScrollArea>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QCloseEvent>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QVBoxLayout>
#include <QTimer>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>

void game::setupwindow()
{
    QIcon iconNextGeneration = QIcon::fromTheme("go-next");
    actNextGeneration = new QAction(tr("&Next generation"));
    actNextGeneration->setStatusTip(tr("nakresli dalsi generaci", "status tip"));
    actNextGeneration->setToolTip(tr("nakresli dalsi generaci", "tool tip"));
    actNextGeneration->setShortcut(tr("Ctrl+N", "Shortcut for the Next generation action"));
    actNextGeneration->setIcon(iconNextGeneration);

    QIcon iconPlay = QIcon::fromTheme("media-playback-start");
    actLetTheLifeGo = new QAction(tr("&Playyyiing"));
    actLetTheLifeGo->setToolTip(tr("the life is out of your hands"));
    actLetTheLifeGo->setStatusTip(tr("let the life be"));
    actLetTheLifeGo->setIcon(iconPlay);

    QIcon iconStop = QIcon::fromTheme("media-playback-stop");
    actLetTheLifeStop = new QAction(tr("&Stop life"));
    actLetTheLifeStop->setToolTip(tr("FREEZE em all"));
    actLetTheLifeStop->setStatusTip(tr("they will do nothing yea"));
    actLetTheLifeStop->setIcon(iconStop);

    QIcon iconQuit = QIcon::fromTheme("application-exit");
    actQuit = new QAction(tr("&Quit"));
    actQuit->setShortcut(QKeySequence::Quit);
    actQuit->setToolTip(tr("Exits the application"));
    actQuit->setStatusTip(tr("Exits the application"));
    actQuit->setIcon(iconQuit);

    actopengamefromtxt=new QAction(tr("&Open..."));
    actopengamefromtxt->setToolTip(tr("open .txt file with game"));
    actopengamefromtxt->setStatusTip(tr("open from file manager a .txt file with game"));

    actOpenSettings=new QAction(tr("&Settings..."));
    actOpenSettings->setToolTip(tr("settings of a game board"));
    actOpenSettings->setStatusTip(tr("settings of a game board"));

    actSaveGameboard=new QAction(tr("&New..."));
    actSaveGameboard->setToolTip(tr("draw your own game"));
    actSaveGameboard->setStatusTip(tr("draw your own game and save it and so on"));

    toolbar = new QToolBar(tr("Main toolbar"));
    toolbar->addAction(actNextGeneration);
    toolbar->addAction(actQuit);
    toolbar->addAction(actLetTheLifeGo);
    toolbar->addAction(actLetTheLifeStop);
    this->addToolBar(toolbar);

    openmennu=new QMenu(tr("&Game"));
    openmennu->addAction(actSaveGameboard);
    openmennu->addAction(actopengamefromtxt);
    openmennu->addAction(actOpenSettings);
    this->menuBar()->addMenu(openmennu);

    actLetTheLifeGo->setEnabled(false);
    actNextGeneration->setEnabled(false);
    actLetTheLifeStop->setEnabled(false);
    actOpenSettings->setEnabled(false);
    setWindowIcon(QIcon(":/icn.png"));
    timer=new QTimer;
}

void game::setupGame()
{
    scene=new QGraphicsScene(this);
    view=new QGraphicsView(scene,this);
    this->setCentralWidget(view);
    isAlive=false;
    this->setWindowTitle(tr("Game of life"));
    thatGame = nullptr;
    /*
    CMatrix field=convert_S_toC2(read_file2(filename),symbolforlivecell);
    sizeX=field.size();
    field[0].pop_back(); //protože z nějakého důvodu se při uložení txt souboru uloží prázdný řádek navíc achjo
    sizeY=field[0].size();
    thatGame = nullptr;
    if(test_wymiary_consistency(field)){
        thatGame = new Game(field);
        paint(thatGame->getAktualny());
        resizeWindow();

    }
    else{
        QMessageBox::warning(this,tr("typico"),tr("myslim ze tvuj textak není obdelnik, ted nevim co se stane lol"));
    }*/
    this->resize(SIZEOFWINDOWX,SIZEOFWINDOWY);
    //scrollArea->resize(SIZEOFWINDOWX, SIZEOFWINDOWY);
}

void game::closeEvent(QCloseEvent *evt)
{
    if(QMessageBox::question(this, tr("odeYEET?"), tr("chcete fakt ukoncit appku!? : ("))
        == QMessageBox::StandardButton::No){
        evt->ignore();
        return;
    }
    evt->accept();
}

void game::nextGeneration()
{
    thatGame->new_generation();
    paint(thatGame->get_actual_board());
    view->update();
}

void game::letTheLifeGo()
{
    isAlive = true;
    actLetTheLifeGo->setEnabled(false);
    actLetTheLifeStop->setEnabled(true);
    timer->start(nextFrameTime);
}

void game::letTheLifeStop()
{
    isAlive = false;
    actLetTheLifeGo->setEnabled(true);
    actLetTheLifeStop->setEnabled(false);
    timer->stop();
}

void game::openGame()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    workdir,
                                                    tr("Plain text (*.txt)"));
    if(!fileName.isEmpty()){
        QFileInfo info(fileName);
        workdir=info.absoluteDir().absolutePath();
        symboloflife SoF;
        if(SoF.exec()==QDialog::Accepted){
            qDebug()<<"tady to zacina";
            char pom=SoF.getSymbolofLife();
            //TODO: opravit aby to kontrolovalo že se nepassne prázdný qstring
            qDebug()<<pom;
            if(pom=='\0'){
                qDebug()<<"dojde to az sem?";
                QMessageBox::warning(this,tr("eror"),tr("vlozil jsi prazdny znak to se nepocita, nic nebylo nahrato"));
                return;
            }
            qDebug()<<"anebo sem?";
            symbolforlivecell=pom;
            actLetTheLifeGo->setEnabled(true);
            actNextGeneration->setEnabled(true);
        }
        else{
            QMessageBox::warning(this,tr("eror"),tr("cancelnul jsi to, nic nebylo nahrato"));
            return;
        }
        CMatrix field=convert_SQ_toC(read_file2(fileName),symbolforlivecell);
        sizeX=field.size();
        //field[0].pop_back(); //protože z nějakého důvodu se při uložení txt souboru uloží prázdný řádek navíc achjo
        sizeY=field[0].size();
        if(test_matrix_consistency(field)){
            if(thatGame==nullptr){
                thatGame = new Game(field);
            }
            else{
                thatGame->setGame(field);
            }
            paint(thatGame->get_actual_board());
            resizeWindow();
            actOpenSettings->setEnabled(true);
        }else{
            qDebug()<<"ten obrazek zase neni konzistentni a jsme v pytli";
            QMessageBox::warning(this,tr("eror"),tr("myslim ze tvuj textak není obdelnik, ted nevim co se stane lol"));
        }
    }
}

void game::openSetting()
{
    Setiings sdialog;
    sdialog.preSetColor(clrlivingcell);
    sdialog.preSetNF(nextFrameTime);
    sdialog.preSetSC(sizeofsq);
    if(sdialog.exec()==QDialog::Accepted){
        clrlivingcell=sdialog.getColorCell();
        sizeofsq=sdialog.getSizeCell();
        nextFrameTime=sdialog.getNextFrame();
        paint(thatGame->get_actual_board());
        resizeWindow();
    }
    else{
        QMessageBox::warning(this,tr("eror"),tr("cancelnul jsi to, nic nebylo nahrato"));
        return;
    }
}

void game::newGameboard()
{
    dwidget=new Drawgame(this,Qt::Window);
    dwidget->setAttribute(Qt::WA_DeleteOnClose);
    dwidget->show();
    connect(dwidget, &QWidget::destroyed, this, [this]() {dwidget = nullptr; //this->setCentralWidget(view);
    });
 /*   ParamOfNewGame PoNG;
    if(PoNG.exec()==QDialog::Accepted){

        dwidget=new Drawgame(nullptr,PoNG.getSymbol(),PoNG.getHeight(),PoNG.getWidth());
        dwidget->show();
        //this->setCentralWidget(dwidget);
        connect(dwidget, &QWidget::destroyed, this, [this]() {dwidget = nullptr; //this->setCentralWidget(view);
        });
        }
    else{
        qDebug()<<"ten obrazek zase neni konzistentni a jsme v pytli";
        QMessageBox::warning(this,tr("eror"),tr("nevlozil jsi udaje, nic se nestalo"));
    }
*/
}

void game::setupConnections()
{
    connect(actQuit,SIGNAL(triggered()),this, SLOT(close()));
    connect(actNextGeneration,SIGNAL(triggered()),this,SLOT(nextGeneration()));
    connect(actLetTheLifeGo,SIGNAL(triggered()),this,SLOT(letTheLifeGo()));
    connect(timer, &QTimer::timeout, this, &game::nextGeneration);
    connect(actLetTheLifeStop,SIGNAL(triggered()),this,SLOT(letTheLifeStop()));
    connect(actopengamefromtxt,SIGNAL(triggered()),this,SLOT(openGame()));
    connect(actOpenSettings,SIGNAL(triggered()),this,SLOT(openSetting()));
    connect(actSaveGameboard,SIGNAL(triggered()),this,SLOT(newGameboard()));
}

void game::paint(CMatrix mat)
{
    scene->clear();
    scene->setSceneRect(0, 0, sizeY * sizeofsq, sizeX * sizeofsq);
    for(int i=0;i<sizeX;i++){
        for(int j=0;j<sizeY;j++){
            if(mat[i][j]==DEAD){
                 scene->addRect(j*sizeofsq,i*sizeofsq,sizeofsq,sizeofsq, QPen(Qt::black),QBrush(Qt::gray));

            }else{
                scene->addRect(j*sizeofsq,i*sizeofsq,sizeofsq,sizeofsq,QPen(Qt::black),QBrush(clrlivingcell));
            }
        }
    }
    scene->update();
}

void game::resizeWindow()
{
    if((sizeY*sizeofsq<SIZEOFWINDOWX) || (sizeX*sizeofsq<SIZEOFWINDOWY)){
        this->resize(sizeY * sizeofsq + 100, sizeX * sizeofsq + 100);

    }

    else if((sizeY*sizeofsq>SIZEOFWINDOWX) && (sizeX*sizeofsq<SIZEOFWINDOWY)){
        this->resize(SIZEOFWINDOWX, sizeX * sizeofsq + 100);

    }
    else if((sizeY*sizeofsq<SIZEOFWINDOWX) && (sizeX*sizeofsq>SIZEOFWINDOWY)){
        this->resize(sizeY * sizeofsq + 100,SIZEOFWINDOWY);

    }else{
        this->resize(SIZEOFWINDOWX,SIZEOFWINDOWY);
    }
    scene->update();
}

game::game(QWidget *parent)
    : QMainWindow(parent)
{
    setupGame();
    setupwindow();
    setupConnections();
}
game::~game() {}


