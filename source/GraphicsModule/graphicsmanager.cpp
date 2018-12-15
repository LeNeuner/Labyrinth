#include "graphicsmanager.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <QTime>

GraphicsManager::GraphicsManager(QObject *parent) :
    QObject(parent)
//    mreader(new TcpIO::ModbusIO()),
{
    connect(lGraphicsPlayerScene, SIGNAL(cellClicked(Position)),
            this, SIGNAL(cellClicked(Position)));
}

GraphicsManager::~GraphicsManager()
{
    if (lGraphicsScene != nullptr)
        delete lGraphicsScene;

    if (lGraphicsPlayerScene != nullptr)
        delete lGraphicsPlayerScene;
}

//--------------------------------------------------------------------------------
// построение графической сцены
QGraphicsScene* GraphicsManager::createGraphicsScene()
{
    // графическое построение поля
    lGraphicsScene = new LabyGraphicsScene(glModel);
    return lGraphicsScene->graphScene();
}

// обновление сцены
QGraphicsScene *GraphicsManager::updateGraphicsScene()
{
    lGraphicsScene->updateScene(glModel);
    return lGraphicsScene->graphScene();
}

// построение и обновление графической сцены поля игрока
QGraphicsScene *GraphicsManager::createPlayerGraphicsScene()
{
    // графическое построение поля
    lGraphicsPlayerScene = new LabyGraphicsScene(glModel);
    return lGraphicsPlayerScene->graphScene();
}
QGraphicsScene *GraphicsManager::updatePlayerGraphicsScene()
{
    lGraphicsPlayerScene->updatePlayerScene(glModel);
    return lGraphicsPlayerScene->graphScene();
}


