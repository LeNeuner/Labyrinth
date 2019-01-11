#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QObject>
#include "globalModel_global.h"
#include "constlist.h"

class GLOBALMODELSHARED_EXPORT GameSettings : public QObject
{
    Q_OBJECT
public:
    explicit GameSettings(QObject *parent = nullptr);

    void setFieldWidth(int width);
    int  fieldWidth();
    int  fieldFullWidth();
    void setFieldHeight(int height);
    int  fieldHeight();
    int  fieldFullHeight();
    void setFieldExitNum(int exitNum);
    int  fieldExitNum();

    void setRealTreasureNum(int treasureNum);
    int  realTreasureNum();
    void setFakeTreasureNum(int treasureNum);
    int  fakeTreasureNum();
    void setArsenalNum(int arsenalNum);
    int  arsenalNum();
    void setHoleTypeNum(int holeTypeNum);
    int  holeTypeNum();
    void setPersonNum(int personNum);
    int  personNum();
    void setAmmunitionNum(int ammunitionNum);
    int  ammunitionNum();
    void setGrenadeNum(int grenadeNum);
    int  grenadeNum();

    void setDefaults();

private:
    const int defFieldWidth      = DEFAULT_FIELD_WIDTH;
    const int defFieldHeight     = DEFAULT_FIELD_HEIGHT;
    const int defFieldExitNum    = DEFAULT_FIELD_EXIT_NUM;
    const int defRealTreasureNum = DEFAULT_REAL_TREASURE_NUM;
    const int defFakeTreasureNum = DEFAULT_FAKE_TREASURE_NUM;
    const int defArsenalNum      = DEFAULT_ARSENAL_NUM;
    const int defHoleTypeNum     = DEFAULT_HOLE_TYPE_NUM;
    const int defPersonNum       = DEFAULT_PLAYER_NUM;
    const int defAmmunitionNum   = DEFAULT_AMMUNITION_NUM;
    const int defGrenadeNum      = DEFAULT_GRENADE_NUM;

    int m_fieldWidth;
    int m_fieldHeight;
    int m_fieldFullWidth;
    int m_fieldFullHeight;
    int m_fieldExitNum;
    int m_realTreasureNum;
    int m_fakeTreasureNum;
    int m_arsenalNum;
    int m_holeTypeNum;
    int m_personNum;
    int m_ammunitionNum;
    int m_grenadeNum;
};

#endif // GAMESETTINGS_H
