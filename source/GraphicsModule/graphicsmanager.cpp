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
}

GraphicsManager::~GraphicsManager()
{
//    if (lGraphicsScene != nullptr)
//        delete lGraphicsScene;
}


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

