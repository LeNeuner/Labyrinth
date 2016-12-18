#ifndef FIELD_H
#define FIELD_H

#include <QObject>

#include "globalModel_global.h"
#include "gamesettings.h"
#include "cell.h"
#include "settingslimits.h"

typedef struct
{
    int y;
    int x;
} Position;

class GLOBALMODELSHARED_EXPORT Field : public QObject
{
    Q_OBJECT
public:
    explicit Field(QObject *parent = 0);
    ~Field();

    // установить поле в значения по умолчаниию
    void setDefaults();

    // создание игрового поля
    void createField(GameSettings *settings);


    int getFullWidth(){
        return xNum;
    }
    int getFullHeight(){
        return yNum;
    }

    // массив ячеек игрового поля
    Cell **cell;

private:

    const int defaultWidth  = DEFAULT_FIELD_WIDTH;
    const int defaultHeight = DEFAULT_FIELD_HEIGHT;

    // play area field
    int width;
    int height;
    // all cell field
    int xNum;
    int yNum;

    std::vector<Position> usedPos;

    // тестирование достаточного количества проходов в лабиринте
    bool checkFreeAccess(GameSettings *settings, int blockedCellsNum);
    // проверка клетки на посещенность
    void checkCell(int y, int x, int &visitedCellCount);

    // установка стартового состояния полей (трава, бетон)
    void setBasicFields();
    // определение положения настоящих кладов
    void setRealTreasures(GameSettings *settings, int &blockedCellsNum);
    // определение положения ложных кладов
    void setFakeTreasures(GameSettings *settings, int &blockedCellsNum);
    // установка стен кладов
    void setTreasuresWalls();
    // определение положений арсеналов
    void setArsenals(GameSettings *settings, int &blockedCellsNum);
    // установка стен арсеналов
    void setArsenalsWalls();
    // определение положения остальных стен
    void setWallsPositions(GameSettings *settings, Position &pos, int &blockedCellsNum);
    // расчет количества текущих стен в блоке
    int blockWallNumCalc(Position &pos);
    // блокировка единственной стены в блоке
    void blockSingleWall(Position &pos);
    // определение положения выходов
    void setExits(GameSettings *settings);
    // определение положения ям
    void setHoles(GameSettings *settings);
};

#endif // FIELD_H
