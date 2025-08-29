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
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include <QCloseEvent>

QString Drawgame::vec_to_QStr(char ch)
{
    QString result;
    for (int i = 0; i < cellRects.size(); i++)
    {
        for (int j = 0; j < cellRects[0].size(); j++)
        {
            if (cellRects[i][j]->data(0).toBool())
            {
                result.append(ch);
            }
            else
            {
                result.append("0");
            }
        }
        result.append("\n");
    }
    qDebug() << result;
    return result;
}

Drawgame::Drawgame(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f), ui(new Ui::Drawgame), symbol('#'), x(480), y(640)
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
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->viewport()->installEventFilter(this);

    scene->update();
}
void Drawgame::setupMenu()
{
    actSaveGame = new QAction(tr("&Save as..."));
    actSaveGame->setToolTip(tr("save your current gameboard"));
    actSaveGame->setStatusTip(tr("save your current game into text file"));

    actNewGame = new QAction(tr("&New gameboard..."));
    actNewGame->setToolTip(tr("Create a new gameboard"));
    actNewGame->setStatusTip(tr("Create and draw new gameboard"));

    actOpenGame = new QAction(tr("&Open existing gameboard..."));
    actOpenGame->setToolTip(tr("load an existing gameboard"));
    actOpenGame->setStatusTip(tr("load an existing gameboard in this window and edit it"));

    actRunGame = new QAction(tr("&Run this game..."));
    actRunGame->setToolTip(tr("Start a simulation from a current gameboard"));
    actRunGame->setStatusTip(tr("Start a simulation from a current gameboard"));

    actOpenPattern = new QAction(tr("&Open pattern..."));
    actOpenPattern->setToolTip(tr("Load a pattern and insert it into a game"));
    actOpenPattern->setStatusTip(tr("Load a pattern and insert it into a game"));

    actRunGame->setEnabled(false);
    actSaveGame->setEnabled(false);
    actOpenPattern->setEnabled(false);

    filemenu = new QMenu(tr("&File"));
    filemenu->addAction(actNewGame);
    filemenu->addAction(actOpenGame);
    filemenu->addAction(actSaveGame);

    editmenu = new QMenu(tr("&Tools"));
    editmenu->addAction(actOpenPattern);

    gamemenu = new QMenu(tr("&Game"));
    gamemenu->addAction(actRunGame);

    mnuBar = new QMenuBar(this);
    mnuBar->addMenu(filemenu);
    mnuBar->addMenu(editmenu);
    mnuBar->addMenu(gamemenu);

    statusLabel = new QLabel(tr("ready"), this);
    statusLabel->setStyleSheet("QLabel {background-color : darkgray;}");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMenuBar(mnuBar);
    layout->addWidget(view);
    layout->addWidget(statusLabel);
    this->setLayout(layout);

    scene->update();
    this->setWindowTitle(tr("kresleni nove hry"));
}

void Drawgame::updateGameboard(char newsym, int newh, int neww)
{
    symbol = newsym;
    x = newh;
    y = neww;
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
        "Text Files (*.txt)");
    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << vec_to_QStr(symbol);
            file.close();
            statusLabel->setText(tr("Gameboard saved successfully"));
            QTimer::singleShot(3000, this, [this]()
                               { statusLabel->setText(tr("Ready")); });
        }
        else
        {
            qDebug() << "Error opening file for writing:" << file.errorString();
        }
    }
}

void Drawgame::drawGrid()
{
    cellRects.resize(x);
    for (int i = 0; i < x; ++i)
    {
        cellRects[i].resize(y);
        for (int j = 0; j < y; ++j)
        {
            QGraphicsRectItem *rect = scene->addRect(
                j * SIZE_OF_SQUARE, i * SIZE_OF_SQUARE, SIZE_OF_SQUARE, SIZE_OF_SQUARE,
                QPen(Qt::black), QBrush(Qt::gray));
            rect->setAcceptedMouseButtons(Qt::LeftButton);
            cellRects[i][j] = rect;
            rect->setData(0, false);
        }
    }
}

void Drawgame::setupConnects()
{
    connect(actSaveGame, &QAction::triggered, this, &Drawgame::writeFile);
    connect(actNewGame, &QAction::triggered, this, &Drawgame::openNewGameboard);
    connect(actOpenGame, &QAction::triggered, this, &Drawgame::openExistingGameboard);
    connect(actOpenPattern, &QAction::triggered, this, &Drawgame::insertPattern);
    connect(actRunGame, &QAction::triggered, this, &Drawgame::runThisInSecondTabheheh);
}

void Drawgame::openNewGameboard()
{
    ParamOfNewGame PoNG(symbol);
    if (PoNG.exec() == QDialog::Accepted)
    {
        updateGameboard(PoNG.getSymbol(), PoNG.getHeight(), PoNG.getWidth());
        actOpenPattern->setEnabled(true);
        actRunGame->setEnabled(true);
        actSaveGame->setEnabled(true);
        statusLabel->setText(tr("Gameboard created successfully"));
        QTimer::singleShot(3000, this, [this]()
                           { statusLabel->setText(tr("Ready")); });
    }
    else
    {
    }
}

void Drawgame::openExistingGameboard()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    workdir,
                                                    tr("Plain text (*.txt)"));
    if (!fileName.isEmpty())
    {
        QFileInfo info(fileName);
        workdir = info.absoluteDir().absolutePath();
        symboloflife SoF(symbol);
        if (SoF.exec() == QDialog::Accepted)
        {
            qDebug() << "tady to zacina";
            char pom = SoF.getSymbolofLife();
            // TODO: opravit aby to kontrolovalo že se nepassne prázdný qstring
            qDebug() << pom;
            if (pom == '\0')
            {
                qDebug() << "dojde to az sem?";
                QMessageBox::warning(this, tr("eror"), tr("vlozil jsi prazdny znak to se nepocita, nic nebylo nahrato"));
                return;
            }
            qDebug() << "anebo sem?";
            symbol = pom;
        }
        else
        {
            QMessageBox::warning(this, tr("eror"), tr("cancelnul jsi to, nic nebylo nahrato"));
            return;
        }
        CMatrix field = convert_SQ_toC(read_file2(fileName), symbol);
        x = field.size();
        // field[0].pop_back(); //protože z nějakého důvodu se při uložení txt souboru uloží prázdný řádek navíc achjo
        y = field[0].size();
        if (test_matrix_consistency(field))
        {
            scene->clear();
            cellRects.clear();
            // vykreslit plochu a tam kde je živá buňka, tam nastavit živou buňku
            cellRects.resize(x);
            for (int i = 0; i < x; ++i)
            {
                cellRects[i].resize(y);
                for (int j = 0; j < y; ++j)
                {
                    bool isLive = (i < field.size() && j < field[i].size() && field[i][j] == ALIVE);
                    QGraphicsRectItem *rect = scene->addRect(
                        j * SIZE_OF_SQUARE, i * SIZE_OF_SQUARE, SIZE_OF_SQUARE, SIZE_OF_SQUARE,
                        QPen(Qt::black), QBrush(isLive ? Qt::white : Qt::gray));
                    rect->setAcceptedMouseButtons(Qt::LeftButton);
                    cellRects[i][j] = rect;
                    rect->setData(0, isLive);
                }
            }

            // Aktualizace scény a zobrazení
            scene->update();
            view->setSceneRect(scene->itemsBoundingRect());
            // view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
            actRunGame->setEnabled(true);
            actSaveGame->setEnabled(true);
            actOpenPattern->setEnabled(true);
            statusLabel->setText(tr("Gameboard loaded successfully"));
            QTimer::singleShot(3000, this, [this]()
                               { statusLabel->setText(tr("Ready")); });
        }
        else
        {
            qDebug() << "ten obrazek zase neni konzistentni a jsme v pytli";
            QMessageBox::warning(this, tr("eror"), tr("myslim ze tvuj textak není obdelnik, ted nevim co se stane lol"));
        }
    }
}

void Drawgame::insertPattern()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open pattern"),
                                                    workdir,
                                                    tr("Plain text (*.txt)"));
    if (fileName.isEmpty())
        return;

    QFileInfo info(fileName);
    workdir = info.absoluteDir().absolutePath();

    symboloflife SoF(symbol);
    if (SoF.exec() != QDialog::Accepted)
    {
        QMessageBox::warning(this, tr("eror"), tr("Cancelnuto, nic nebylo vloženo"));
        return;
    }
    char sym = SoF.getSymbolofLife();
    if (sym == '\0')
    {
        QMessageBox::warning(this, tr("eror"), tr("Znak nesmí být prázdný"));
        return;
    }

    CMatrix field = convert_SQ_toC(read_file2(fileName), sym);

    CMatrix cropped = cut(field);

    if (cropped.empty())
    {
        QMessageBox::warning(this, tr("prazden"), tr("Pattern je prázdný (jen mrtvé buňky)"));
        return;
    }
    statusLabel->setText(tr("Pattern in mouse!"));
    currentPattern = cropped;
    insertingPattern = true;
}

void Drawgame::runThisInSecondTabheheh()
{
    emit sendMatrix(vec_to_QStr(symbol), symbol);
    statusLabel->setText(tr("Gameboard emited into game"));
    QTimer::singleShot(3000, this, [this]()
                       { statusLabel->setText(tr("Ready")); });
}

bool Drawgame::eventFilter(QObject *obj, QEvent *event)
{
    // vložíme pattern
    if (insertingPattern && obj == view->viewport() && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QPointF scenePos = view->mapToScene(mouseEvent->pos());

        int gridX = scenePos.y() / SIZE_OF_SQUARE;
        int gridY = scenePos.x() / SIZE_OF_SQUARE;

        for (int i = 0; i < (int)currentPattern.size(); ++i)
        {
            for (int j = 0; j < (int)currentPattern[i].size(); ++j)
            {
                int xx = gridX + i;
                int yy = gridY + j;
                if (xx < x && yy < y)
                {
                    bool alive = (currentPattern[i][j] == ALIVE);
                    cellRects[xx][yy]->setBrush(alive ? QBrush(Qt::white) : QBrush(Qt::gray));
                    cellRects[xx][yy]->setData(0, alive);
                }
            }
        }
        scene->update();
        insertingPattern = false;
        statusLabel->setText(tr("Pattern inserted"));
        QTimer::singleShot(3000, this, [this]()
                           { statusLabel->setText(tr("Ready")); });
        return true;
    }

    if (obj == view->viewport() && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QPointF scenePos = view->mapToScene(mouseEvent->pos());
        QGraphicsItem *item = scene->itemAt(scenePos, QTransform());

        if (item && item->type() == QGraphicsRectItem::Type)
        {
            QGraphicsRectItem *rect = static_cast<QGraphicsRectItem *>(item);
            bool isWhite = rect->data(0).toBool();

            if (isWhite)
            {
                rect->setBrush(QBrush(Qt::gray));
                rect->setData(0, false);
            }
            else
            {
                rect->setBrush(QBrush(Qt::white));
                rect->setData(0, true);
            }
            scene->update();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void Drawgame::closeEvent(QCloseEvent *event)
{

    // pro případ že se zavře hlavní okno, zavře se i widget
    if (parentWidget() && !parentWidget()->isVisible())
    {
        event->accept();
        return;
    }
    if (QMessageBox::question(this, tr("Sure to close??"), tr("Unsaved gameboard will be discarded...")) == QMessageBox::StandardButton::No)
    {
        event->ignore();
        return;
    }
    event->accept();
}
