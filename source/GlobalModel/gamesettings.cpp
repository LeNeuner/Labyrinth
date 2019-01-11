#include "gamesettings.h"

GameSettings::GameSettings(QObject *parent) :
    QObject(parent),
    m_fieldWidth(defFieldWidth),
    m_fieldHeight(defFieldHeight),
    m_fieldExitNum(defFieldExitNum),
    m_realTreasureNum(defRealTreasureNum),
    m_fakeTreasureNum(defFakeTreasureNum),
    m_arsenalNum(defArsenalNum),
    m_holeTypeNum(defHoleTypeNum),
    m_personNum(defPersonNum),
    m_ammunitionNum(defAmmunitionNum),
    m_grenadeNum(defGrenadeNum)
{
}

void GameSettings::setFieldWidth(int width)
{
    m_fieldWidth = width;
    m_fieldFullWidth = width * 2 + 3;
}

int GameSettings::fieldWidth()
{
    return m_fieldWidth;
}

int GameSettings::fieldFullWidth()
{
    return m_fieldFullWidth;
}

void GameSettings::setFieldHeight(int height)
{
    m_fieldHeight = height;
    m_fieldFullHeight = height * 2 + 3;
}

int GameSettings::fieldHeight()
{
    return m_fieldHeight;
}

int GameSettings::fieldFullHeight()
{
    return m_fieldFullHeight;
}

void GameSettings::setFieldExitNum(int exitNum)
{
    m_fieldExitNum = exitNum;
}

int GameSettings::fieldExitNum()
{
    return m_fieldExitNum;
}


void GameSettings::setRealTreasureNum(int treasureNum)
{
    m_realTreasureNum = treasureNum;
}

int GameSettings::realTreasureNum()
{
    return m_realTreasureNum;
}

void GameSettings::setFakeTreasureNum(int treasureNum)
{
    m_fakeTreasureNum = treasureNum;
}

int GameSettings::fakeTreasureNum()
{
    return m_fakeTreasureNum;
}

void GameSettings::setArsenalNum(int arsenalNum)
{
    m_arsenalNum = arsenalNum;
}

int GameSettings::arsenalNum()
{
    return m_arsenalNum;
}

void GameSettings::setHoleTypeNum(int holeTypeNum)
{
    m_holeTypeNum = holeTypeNum;
}

int GameSettings::holeTypeNum()
{
    return m_holeTypeNum;
}

void GameSettings::setPersonNum(int personNum)
{
    m_personNum = personNum;
}

int GameSettings::personNum()
{
    return m_personNum;
}

void GameSettings::setAmmunitionNum(int ammunitionNum)
{
    m_ammunitionNum = ammunitionNum;
}

int GameSettings::ammunitionNum()
{
    return m_ammunitionNum;
}

void GameSettings::setGrenadeNum(int grenadeNum)
{
    m_grenadeNum = grenadeNum;
}

int GameSettings::grenadeNum()
{
    return m_grenadeNum;
}


void GameSettings::setDefaults()
{
    m_fieldWidth      = defFieldWidth;
    m_fieldHeight     = defFieldHeight;
    m_fieldFullWidth  = defFieldWidth * 2 + 3;
    m_fieldFullHeight = defFieldHeight * 2 + 3;
    m_fieldExitNum    = defFieldExitNum;
    m_realTreasureNum = defRealTreasureNum;
    m_fakeTreasureNum = defFakeTreasureNum;
    m_arsenalNum      = defArsenalNum;
    m_holeTypeNum     = defHoleTypeNum;
    m_personNum       = defPersonNum;
    m_ammunitionNum   = defAmmunitionNum;
    m_grenadeNum      = defGrenadeNum;
}

