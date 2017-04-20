#include "enginemanager.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <QTime>

EngineManager::EngineManager(QObject *parent) :
    QObject(parent)
{
}

EngineManager::~EngineManager()
{
}
