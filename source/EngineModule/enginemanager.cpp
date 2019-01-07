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
    glModel->fieldModel->createField(glModel->gameSettModel);

    // FIELD INFO FOR PLAYERS
    glModel->fieldModel->createStartFieldInfo(glModel->gameSettModel);

//    glModel->playerFieldModel->createField(glModel->gameSettModel);
//    glModel->playerFieldModel->createPlayerField(glModel->gameSettModel);


    // PLAYER CREATION

    // WAIT START PLAYER POSITION
    // создание информации о поле для игроков

//    glModel->playerFieldModel->createStartFieldInfo();

    emit needSceneUpdate();

//    while (true)
//    {

//    }

    // START GAME
//    while (true)
//    {
//        // game circle
//    }

    return true;
}

// prepare game for the next step
void EngineManager::prepareNextStep(int x, int y)
{
    // check for win
    qDebug() << "EM: " << x << y;

    glModel->playerFieldModel->cell[y-2][x].setClickabilityState(true);
    glModel->playerFieldModel->cell[y+2][x].setClickabilityState(true);
    glModel->playerFieldModel->cell[y][x-2].setClickabilityState(true);
    glModel->playerFieldModel->cell[y][x+2].setClickabilityState(true);


    // update current graphic scene
    emit needSceneUpdate();
}





