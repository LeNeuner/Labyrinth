#include "globalmodel.h"

GlobalModel::GlobalModel(QObject *parent) :
    QObject(parent),
    fieldModel(new Field(this)),
//    playerFieldModel(new PlayerFieldInfo(this)),
    playerFieldModel(new Field(this)),
    gameSettModel(new GameSettings(this))
{
}

void GlobalModel::setDefaults()
{
    fieldModel->setDefaults();
    gameSettModel->setDefaults();
//    playerFieldModel->createPlayerField(gameSettModel);
    playerFieldModel->setDefaults();
}
