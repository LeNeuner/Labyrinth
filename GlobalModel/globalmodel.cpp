#include "globalmodel.h"

GlobalModel::GlobalModel(QObject *parent) :
    QObject(parent),
    fieldModel(new Field(this)),
    gameSettModel(new GameSettings(this))
//    messageModel(new ComMessageKeeper(this)),
//    hotkeysModel(new HotkeyKeeper(this))
{
}

void GlobalModel::setDefaults()
{
    fieldModel->setDefaults();
    gameSettModel->setDefaults();
//    commandModel->setDefaults();
//    messageModel->setDefaults();
//    hotkeysModel->setDefaults();
}
