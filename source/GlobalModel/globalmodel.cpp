#include "globalmodel.h"

GlobalModel::GlobalModel(QObject *parent) :
    QObject(parent),
    gameSettModel(new GameSettings(this)),
    fieldModel(new Field(this))
{
}

void GlobalModel::setDefaults()
{
    gameSettModel->setDefaults();
    fieldModel->setDefaults();
}
