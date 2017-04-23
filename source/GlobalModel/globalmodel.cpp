#include "globalmodel.h"

GlobalModel::GlobalModel(QObject *parent) :
    QObject(parent),
    fieldModel(new Field(this)),
    gameSettModel(new GameSettings(this))
{
}

void GlobalModel::setDefaults()
{
    fieldModel->setDefaults();
    gameSettModel->setDefaults();
}
