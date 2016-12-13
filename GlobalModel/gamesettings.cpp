#include "gamesettings.h"

GameSettings::GameSettings(QObject *parent) :
    QObject(parent),
    _fieldWidth(defFieldWidth),
    _fieldHeight(defFieldHeight),
    _fieldExitNum(defFieldExitNum),
    _realTreasureNum(defRealTreasureNum),
    _fakeTreasureNum(defFakeTreasureNum),
    _arsenalNum(defArsenalNum),
    _holeTypeNum(defHoleTypeNum),
    _personNum(defPersonNum),
    _ammunitionNum(defAmmunitionNum),
    _grenadeNum(defGrenadeNum)
{
}

void GameSettings::setFieldWidth(int width)
{
    _fieldWidth = width;
}

int GameSettings::fieldWidth()
{
    return _fieldWidth;
}

void GameSettings::setFieldHeight(int height)
{
    _fieldHeight = height;
}

int GameSettings::fieldHeight()
{
    return _fieldHeight;
}

void GameSettings::setFieldExitNum(int exitNum)
{
    _fieldExitNum = exitNum;
}

int GameSettings::fieldExitNum()
{
    return _fieldExitNum;
}


void GameSettings::setRealTreasureNum(int treasureNum)
{
    _realTreasureNum = treasureNum;
}

int GameSettings::realTreasureNum()
{
    return _realTreasureNum;
}

void GameSettings::setFakeTreasureNum(int treasureNum)
{
    _fakeTreasureNum = treasureNum;
}

int GameSettings::fakeTreasureNum()
{
    return _fakeTreasureNum;
}

void GameSettings::setArsenalNum(int arsenalNum)
{
    _arsenalNum = arsenalNum;
}

int GameSettings::arsenalNum()
{
    return _arsenalNum;
}

void GameSettings::setHoleTypeNum(int holeTypeNum)
{
    _holeTypeNum = holeTypeNum;
}

int GameSettings::holeTypeNum()
{
    return _holeTypeNum;
}

void GameSettings::setPersonNum(int personNum)
{
    _personNum = personNum;
}

int GameSettings::personNum()
{
    return _personNum;
}

void GameSettings::setAmmunitionNum(int ammunitionNum)
{
    _ammunitionNum = ammunitionNum;
}

int GameSettings::ammunitionNum()
{
    return _ammunitionNum;
}

void GameSettings::setGrenadeNum(int grenadeNum)
{
    _grenadeNum = grenadeNum;
}

int GameSettings::grenadeNum()
{
    return _grenadeNum;
}


void GameSettings::setDefaults()
{
    _fieldWidth      = defFieldWidth;
    _fieldHeight     = defFieldHeight;
    _fieldExitNum    = defFieldExitNum;
    _realTreasureNum = defRealTreasureNum;
    _fakeTreasureNum = defFakeTreasureNum;
    _arsenalNum      = defArsenalNum;
    _holeTypeNum     = defHoleTypeNum;
    _personNum       = defPersonNum;
    _ammunitionNum   = defAmmunitionNum;
    _grenadeNum      = defGrenadeNum;
}

