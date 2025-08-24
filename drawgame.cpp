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

Drawgame::Drawgame(QWidget *parent, char ch, int h, int w)
    : QWidget(parent)
    , ui(new Ui::Drawgame),symbol(ch),x(h),y(w)
{
    ui->setupUi(this);
    init();
    setupMenu();

}

Drawgame::~Drawgame()
{
    delete ui;
}

void Drawgame::init()
{
    scene=new QGraphicsScene(this);
    view=new QGraphicsView(scene,this);
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
    mnuBar=new QMenuBar(this);
    mnuBar->autoFillBackground();
    mnuBar->addMenu(savemennu);

    QVBoxLayout* layout =new QVBoxLayout(this);
    layout->setMenuBar(mnuBar);
    layout->addWidget(view);
    this->setLayout(layout);
    scene->update();
    connect(actSaveGame,SIGNAL(triggered()),this,SLOT(writeFile()));
    this->setWindowTitle(tr("kresleni nove hry"));
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
                // Inform the user about the error
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
            return true; // říkáme: my jsme event zpracovali
        }
    }

    return QWidget::eventFilter(obj, event); // předáme dál
}
