#include "drawgame.h"
#include "ui_drawgame.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QMenuBar>
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QVBoxLayout>
#include <QMessageBox>


QString Drawgame::vec_to_QStr(char ch)
{
    QString result;
    for(int i=0;i<cellRects.size();i++){
        for(int j=0;j<cellRects[0].size();j++){
            if(cellRects[i][j]->data(0).toBool()){
                result.append(ch);
            }
            else{
                result.append("0");
            }
        }
        result.append("\n");
    }
    qDebug()<<result;
    return result;
}

Drawgame::Drawgame(QWidget *parent,Qt::WindowFlags f): QWidget(parent,f), ui(new Ui::Drawgame),symbol('#'),x(480),y(640)
{
    ui->setupUi(this);
    setupScene();
    setupMenu();
    setupConnects();
}

Drawgame::~Drawgame()
{
    delete ui;
}

void Drawgame::setupScene()
{
    scene=new QGraphicsScene(this);
    view=new QGraphicsView(scene,this);
    /*
    cellRects.resize(x);
    for (int i = 0; i < x; ++i) {
        cellRects[i].resize(y);
        for (int j = 0; j < y; ++j) {
            QGraphicsRectItem* rect = scene->addRect(
                j*size_of_square,i*size_of_square,size_of_square,size_of_square,QPen(Qt::black),QBrush(Qt::gray));
            rect->setAcceptedMouseButtons(Qt::LeftButton);
            cellRects[i][j]=rect;
            rect->setData(0,false);
        }
    }
*/
    //cellRects[2][3]->setBrush(QBrush(Qt::darkCyan));
    //connect(scene, &QGraphicsScene::mousePressEvent, this, &Drawgame::handleClick);
    view->viewport()->installEventFilter(this);

scene->update();    
}

void Drawgame::setupMenu()
{
    actSaveGame=new QAction(tr("&Save as..."));
    actSaveGame->setToolTip(tr("save your own game"));
    actSaveGame->setStatusTip(tr("save your own game somewhere idk"));

    actNewGame=new QAction(tr("&New gameboard..."));
    actNewGame->setToolTip(tr("Draw new gameboard"));
    actNewGame->setStatusTip(tr("open and draw new gameboard"));

    actOpenGame=new QAction(tr("&open existing gameboard..."));
    actOpenGame->setToolTip(tr("edit existing gameboard"));
    actOpenGame->setStatusTip(tr("open existing wgameboard in this window and draw"));

    actRunGame=new QAction(tr("&Run this game..."));
    actRunGame->setToolTip(tr("open Game from this gameboard"));
    actRunGame->setStatusTip(tr("open Game from this gameboard"));

    savemennu=new QMenu(tr("&Game"));
    savemennu->addAction(actSaveGame);
    savemennu->addAction(actNewGame);
    savemennu->addAction(actOpenGame);
    savemennu->addAction(actRunGame);
    mnuBar=new QMenuBar(this);
    mnuBar->autoFillBackground();
    mnuBar->addMenu(savemennu);

    QVBoxLayout* layout =new QVBoxLayout(this);
    layout->setMenuBar(mnuBar);
    layout->addWidget(view);
    this->setLayout(layout);
    scene->update();
    //connect(actSaveGame,SIGNAL(triggered()),this,SLOT(writeFile()));
    this->setWindowTitle(tr("kresleni nove hry"));
}

void Drawgame::updateGameboard(char newsym, int newh, int neww)
{
    symbol=newsym;
    x=newh;
    y=neww;
    scene->clear();
    cellRects.clear();
    drawGrid();
    scene->update();
    view->setSceneRect(scene->itemsBoundingRect());
}

void Drawgame::writeFile()
{
    QString filePath = QFileDialog::getSaveFileName(
            this,
            "Save As",
            QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
            "Text Files (*.txt)"
            );
        if (!filePath.isEmpty()) {
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream stream(&file);
                stream << vec_to_QStr(symbol);
                file.close();
            }
            else
            {qDebug() << "Error opening file for writing:" << file.errorString();
            }
        }
}

void Drawgame::drawGrid()
{
    cellRects.resize(x);
    for (int i = 0; i < x; ++i) {
        cellRects[i].resize(y);
        for (int j = 0; j < y; ++j) {
            QGraphicsRectItem* rect = scene->addRect(
                j * size_of_square, i * size_of_square, size_of_square, size_of_square,
                QPen(Qt::black), QBrush(Qt::gray));
            rect->setAcceptedMouseButtons(Qt::LeftButton);
            cellRects[i][j] = rect;
            rect->setData(0, false);
        }
    }
}

void Drawgame::setupConnects()
{
 connect(actSaveGame,SIGNAL(triggered()),this,SLOT(writeFile()));
 connect(actNewGame,SIGNAL(triggered()),this, SLOT(openNewGameboard()));
 connect(actOpenGame,SIGNAL(triggered()),this,SLOT(openExistingGameboard()));
}

void Drawgame::openNewGameboard()
{
    ParamOfNewGame PoNG;
    if(PoNG.exec()==QDialog::Accepted){
    updateGameboard(PoNG.getSymbol(),PoNG.getHeight(),PoNG.getWidth());
    }
    else{
        qDebug()<<"ten obrazek zase neni konzistentni a jsme v pytli";
        QMessageBox::warning(this,tr("eror"),tr("nevlozil jsi udaje, nic se nestalo"));
    }
}

void Drawgame::openExistingGameboard()
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
            symbol=pom;}
            else{
                QMessageBox::warning(this,tr("eror"),tr("cancelnul jsi to, nic nebylo nahrato"));
                return;
            }
            CMatrix field=convert_SQ_toC(read_file2(fileName),symbol);
            x=field.size();

            //field[0].pop_back(); //protože z nějakého důvodu se při uložení txt souboru uloží prázdný řádek navíc achjo
            y=field[0].size();
            if(test_matrix_consistency(field)){
                scene->clear();
                cellRects.clear();
                //vykreslit plochu a tam kde je živá buňka, tam nastavit živou buňku
                cellRects.resize(x);
                for (int i = 0; i < x; ++i) {
                    cellRects[i].resize(y);
                    for (int j = 0; j < y; ++j) {
                        bool isLive = (i < field.size() && j < field[i].size()&&field[i][j]==ALIVE);
                        QGraphicsRectItem* rect = scene->addRect(
                            j * size_of_square, i * size_of_square, size_of_square, size_of_square,
                            QPen(Qt::black), QBrush(isLive ? Qt::white : Qt::gray));
                        rect->setAcceptedMouseButtons(Qt::LeftButton);
                        cellRects[i][j] = rect;
                        rect->setData(0, isLive);
                    }
                }

                // Aktualizace scény a zobrazení
                scene->update();
                view->setSceneRect(scene->itemsBoundingRect());
                view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
            }else{
                qDebug()<<"ten obrazek zase neni konzistentni a jsme v pytli";
                QMessageBox::warning(this,tr("eror"),tr("myslim ze tvuj textak není obdelnik, ted nevim co se stane lol"));
            }
        }
}

bool Drawgame::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == view->viewport() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF scenePos = view->mapToScene(mouseEvent->pos());
        QGraphicsItem* item = scene->itemAt(scenePos, QTransform());

        if (item && item->type() == QGraphicsRectItem::Type) {
            QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(item);
            bool isWhite = rect->data(0).toBool();

            if (isWhite) {
                rect->setBrush(QBrush(Qt::gray));
                rect->setData(0, false);
            } else {
                rect->setBrush(QBrush(Qt::white));
                rect->setData(0, true);
            }
            scene->update();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}
