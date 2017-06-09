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

//--------------------------------------------------
// инициализация новой игры
bool EngineManager::newGameInitialization()
{
    // FIELD GENERATION

    // PLAYERS CREATION

    // CHOICE START PLAYER POSITION

    // START GAME MODE
    return true;
}

//--------------------------------------------------
// игровой процесс
int EngineManager::gameProcess()
{
    // Для каждого игрока по кругу

    // 1. Выбор хода (добавить действия (стрельба))
    // 2. Проверка возможности (ответ системы)
    // Выполнение хода или итерация 1
}





