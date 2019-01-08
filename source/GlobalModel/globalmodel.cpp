#include "globalmodel.h"

GlobalModel::GlobalModel(QObject *parent) :
    QObject(parent),
    gameSettModel(new GameSettings(this)),
    fieldModel(new Field(this)),
    playersModel(new Players(this))
{
}

void GlobalModel::setDefaults()
{
    gameSettModel->setDefaults();
    fieldModel->setDefaults();
    playersModel->setDefaults();
}
