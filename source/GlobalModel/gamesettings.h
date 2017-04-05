#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QObject>
#include "globalModel_global.h"
#include "constlist.h"

class GLOBALMODELSHARED_EXPORT GameSettings : public QObject
{
    Q_OBJECT
public:
    explicit GameSettings(QObject *parent = 0);

    void setFieldWidth(int width);
    int  fieldWidth();
    void setFieldHeight(int height);
    int  fieldHeight();
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

    int _fieldWidth;
    int _fieldHeight;
    int _fieldExitNum;
    int _realTreasureNum;
    int _fakeTreasureNum;
    int _arsenalNum;
    int _holeTypeNum;
    int _personNum;
    int _ammunitionNum;
    int _grenadeNum;
};

#endif // GAMESETTINGS_H
