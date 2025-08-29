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
#include <QApplication>
#include <QDateTime>
#include <QLabel>

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

    actopengamefromtxt = new QAction(tr("&Open..."));
    actopengamefromtxt->setToolTip(tr("open .txt file with game"));
    actopengamefromtxt->setStatusTip(tr("open from file manager a .txt file with game"));

    actOpenSettings = new QAction(tr("&Settings..."));
    actOpenSettings->setToolTip(tr("settings of a game board"));
    actOpenSettings->setStatusTip(tr("settings of a game board"));

    actSaveGameboard = new QAction(tr("&New..."));
    actSaveGameboard->setToolTip(tr("draw your own game"));
    actSaveGameboard->setStatusTip(tr("draw your own game and save it and so on"));

    toolbar = new QToolBar(tr("Main toolbar"));
    toolbar->addAction(actNextGeneration);
    toolbar->addAction(actQuit);
    toolbar->addAction(actLetTheLifeGo);
    toolbar->addAction(actLetTheLifeStop);
    this->addToolBar(toolbar);

    openmennu = new QMenu(tr("&Game"));
    openmennu->addAction(actSaveGameboard);
    openmennu->addAction(actopengamefromtxt);
    openmennu->addAction(actOpenSettings);
    this->menuBar()->addMenu(openmennu);

    actLetTheLifeGo->setEnabled(false);
    actNextGeneration->setEnabled(false);
    actLetTheLifeStop->setEnabled(false);
    actOpenSettings->setEnabled(false);
    setWindowIcon(QIcon(":/icn.png"));
    timer = new QTimer;
}

void game::setupGame()
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    this->setCentralWidget(view);
    isAlive = false;
    this->setWindowTitle(tr("Game of life"));
    thatGame = nullptr;
    this->resize(SIZEOFWINDOWX, SIZEOFWINDOWY);
}

void game::closeEvent(QCloseEvent *evt)
{
    if (QMessageBox::question(this, tr("odeYEET?"), tr("chcete fakt ukoncit appku!? : (")) == QMessageBox::StandardButton::No)
    {
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
    if (!fileName.isEmpty())
    {
        QFileInfo info(fileName);
        workdir = info.absoluteDir().absolutePath();
        symboloflife SoF(symbolforlivecell);
        if (SoF.exec() == QDialog::Accepted)
        {
            qDebug() << "tady to zacina";
            char pom = SoF.getSymbolofLife();
            qDebug() << pom;
            symbolforlivecell = pom;
            actLetTheLifeGo->setEnabled(true);
            actNextGeneration->setEnabled(true);
        }
        else
        {
            return;
        }
        loadGame(read_file2(fileName), symbolforlivecell);
    }
}

void game::openSetting()
{
    Setiings sdialog;
    sdialog.preSetColor(clrlivingcell);
    sdialog.preSetNF(nextFrameTime);
    sdialog.preSetSC(sizeofsq);
    if (sdialog.exec() == QDialog::Accepted)
    {
        clrlivingcell = sdialog.getColorCell();
        sizeofsq = sdialog.getSizeCell();
        nextFrameTime = sdialog.getNextFrame();
        paint(thatGame->get_actual_board());
        resizeWindow();
    }
    else
    {
        return;
    }
}

void game::newGameboard()
{
    if (dwidget != nullptr)
    {
        dwidget->activateWindow();
        return;
    }
    dwidget = new Drawgame(this, Qt::Window);
    dwidget->setAttribute(Qt::WA_DeleteOnClose);
    dwidget->show();
    connect(dwidget, &Drawgame::sendMatrix, this, &game::receiveMatrix); // přijme signál z dwidget, který pošle gameboard v qstringu a symbol života
    connect(dwidget, &QWidget::destroyed, this, [this]()
            { dwidget = nullptr; });
}

void game::loadGame(const SQMatrix &m, char symbol)
{
    {
        CMatrix field = convert_SQ_toC(m, symbol);
        sizeX = field.size();
        sizeY = field[0].size();

        if (test_matrix_consistency(field))
        {
            if (thatGame == nullptr)
            {
                thatGame = new Game(field);
            }
            else
            {
                thatGame->setGame(field);
            }
            paint(thatGame->get_actual_board());
            resizeWindow();
            actOpenSettings->setEnabled(true);
        }
        else
        {
            qDebug() << "ten obrazek neni konzistentni a jsme v pytli";
            QMessageBox::warning(this, tr("eror"), tr("Your loaded data is not valid, nothing happened..."));
        }
    }
}

void game::receiveMatrix(const QString &m, char symbol)
{
    qDebug() << "Received matrix with symbol:" << symbol << "and content:\n"
             << m;
    SQMatrix lines;
    for (const QString &line : m.split('\n', Qt::SkipEmptyParts))
    {
        if (!line.isEmpty())
        {
            lines.push_back(line);
        }
    }
    if (lines.empty())
    {
        qDebug() << "přenesená matice je prázdná";
        QMessageBox::warning(this, tr("Chyba"), tr("Přenesená matice je prázdná"));
        return;
    }
    loadGame(lines, symbol);
    actLetTheLifeGo->setEnabled(true);
    actNextGeneration->setEnabled(true);
}

void game::updateTimer()
{
    QString actualtime = QDateTime::currentDateTime().toString("HH:mm:ss");
    statusLabel->setText(actualtime);
}
void game::setupConnections()
{
    connect(actQuit, &QAction::triggered, this, &QWidget::close);
    connect(actNextGeneration, &QAction::triggered, this, &game::nextGeneration);
    connect(actLetTheLifeGo, &QAction::triggered, this, &game::letTheLifeGo);
    connect(timer, &QTimer::timeout, this, &game::nextGeneration);
    connect(actLetTheLifeStop, &QAction::triggered, this, &game::letTheLifeStop);
    connect(actopengamefromtxt, &QAction::triggered, this, &game::openGame);
    connect(actOpenSettings, &QAction::triggered, this, &game::openSetting);
    connect(actSaveGameboard, &QAction::triggered, this, &game::newGameboard);
}

void game::paint(CMatrix mat)
{
    scene->clear();
    scene->setSceneRect(0, 0, sizeY * sizeofsq, sizeX * sizeofsq);
    for (int i = 0; i < sizeX; i++)
    {
        for (int j = 0; j < sizeY; j++)
        {
            if (mat[i][j] == DEAD)
            {
                scene->addRect(j * sizeofsq, i * sizeofsq, sizeofsq, sizeofsq, QPen(Qt::black), QBrush(Qt::gray));
            }
            else
            {
                scene->addRect(j * sizeofsq, i * sizeofsq, sizeofsq, sizeofsq, QPen(Qt::black), QBrush(clrlivingcell));
            }
        }
    }
    scene->update();
}

void game::resizeWindow()
{
    if ((sizeY * sizeofsq < SIZEOFWINDOWX) || (sizeX * sizeofsq < SIZEOFWINDOWY))
    {
        this->resize(sizeY * sizeofsq + 100, sizeX * sizeofsq + 100);
    }

    else if ((sizeY * sizeofsq > SIZEOFWINDOWX) && (sizeX * sizeofsq < SIZEOFWINDOWY))
    {
        this->resize(SIZEOFWINDOWX, sizeX * sizeofsq + 100);
    }
    else if ((sizeY * sizeofsq < SIZEOFWINDOWX) && (sizeX * sizeofsq > SIZEOFWINDOWY))
    {
        this->resize(sizeY * sizeofsq + 100, SIZEOFWINDOWY);
    }
    else
    {
        this->resize(SIZEOFWINDOWX, SIZEOFWINDOWY);
    }
    scene->update();
}

game::game(QWidget *parent)
    : QMainWindow(parent)
{
    setupGame();
    setupwindow();
    setupConnections();
    statusLabel = new QLabel(this);
    statusBar()->addPermanentWidget(statusLabel);
    actualTime = new QTimer();
    connect(actualTime, &QTimer::timeout, this, &game::updateTimer);
    actualTime->start(1000);
    updateTimer();
}
game::~game() {}
