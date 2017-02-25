#include "field.h"

#include <cstdlib>
#include <ctime>

#include <QDebug>
#include <iostream>
#include <windows.h>


Field::Field(QObject *parent) :
    QObject(parent),
    width(defaultWidth),
    height(defaultHeight),
    xNum(defaultWidth * 2 + 3),
    yNum(defaultHeight *2 + 3)
{
}

Field::~Field()
{
}

//--------------------------------------------------------------------------------
// установить поле в значения по умолчаниию
void Field::setDefaults()
{
    width   = defaultWidth;
    height  = defaultHeight;
    xNum    = width  * 2 + 3;
    yNum    = height * 2 + 3;

    // создание поля соответствующего размера
    cell = new Cell* [yNum];
    for (int y = 0; y < yNum; y++)
    {
        cell[y] = new Cell [xNum];
    }

    // square cells
    for (int y = 0; y < yNum; y+=2)
    {
        for (int x = 0; x < xNum; x+=2)
        {
            cell[y][x].setCellTypes(FormType::Square, MaterialType::None,
                                    ObjectType::None, ObjectState::None, HoleType::None);
        }
    }
    // vertical cells
    for (int y = 0; y < yNum; y+=2)
    {
        for (int x = 1; x < xNum-1; x+=2)
        {
            cell[y][x].setCellTypes(FormType::Vertical, MaterialType::None,
                                    ObjectType::None, ObjectState::None, HoleType::None);
        }
    }
    // gorizontal cells
    for (int y = 1; y < yNum-1; y+=2)
    {
        for (int x = 0; x < xNum; x+=2)
        {
            cell[y][x].setCellTypes(FormType::Gorizontal, MaterialType::None,
                                    ObjectType::None, ObjectState::None, HoleType::None);
        }
    }
    // pillar cells
    for (int y = 1; y < yNum-1; y+=2)
    {
        for (int x = 1; x < xNum-1; x+=2)
        {
            cell[y][x].setCellTypes(FormType::Pillar, MaterialType::None,
                                    ObjectType::None, ObjectState::None, HoleType::None);
        }
    }
}

// создание игрового поля
void Field::createField(GameSettings *settings)
{
    // получение значения настроек поля
    width   = settings->fieldWidth();
    height  = settings->fieldHeight();
    xNum    = width  * 2 + 3;
    yNum    = height * 2 + 3;

    // очистка предыдущего поля
    if (cell != nullptr)
    {
        delete cell;
        cell = nullptr;
    }
    usedPos.clear();

    // создание поля соответствующего размера
    cell = new Cell* [yNum];
    for (int y = 0; y < yNum; y++)
    {
        cell[y] = new Cell [xNum];
    }

    // обновление системы рандома
    srand(time(NULL));

    // установка стартового состояния полей (трава, бетон)
    setBasicFields();

    // определение положения реального клада
    int blockedCellsNum = 0;
    setRealTreasures(settings, blockedCellsNum);

    // определение положения ложного клада
    setFakeTreasures(settings, blockedCellsNum);

    // установка стен кладов
    setTreasuresWalls();

    // определение положений арсеналов
    setArsenals(settings, blockedCellsNum);

    // установка стен арсеналов
    setArsenalsWalls();

    // определение положения остальных стен
    for (int y = 2; y <= yNum-5; y+=2)
    {
        for (int x = 2; x <= xNum-5; x+=2)
        {
            Position pos;
            pos.y = y;
            pos.x = x;
            setWallsPositions(settings, pos, blockedCellsNum);
        }
    }

    //  определение положения выходов
    setExits(settings);

    // определение положения ям
    if (settings->holeTypeNum() != 0)
        setHoles(settings);
}
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
// ФУНКЦИИ ТЕСТИРОВАНИЯ ПРАВИЛЬНОЙ ГЕНЕРАЦИИ
//--------------------------------------------------------------------------------
// проверка достаточного количества проходов в лабиринте
bool Field::checkFreeAccess(GameSettings *settings, int blockedCellsNum)
{
    int visitedCellCount = 0;
    for (int y = 2; y <= yNum-3; y+=2)
    {
        for (int x = 2; x <= xNum-3; x+=2)
        {
            if (!cell[y][x].blocked())
            {
                checkCell(y, x, visitedCellCount);
                break;
            }
        }
        break;
    }

    int playCells = settings->fieldWidth() * settings->fieldHeight();
//    int xZone = settings->realTreasureNum() + settings->fakeTreasureNum();

//    qDebug() << "playCells:     " << playCells;
//    qDebug() << "xZone:         " << xZone;
//    qDebug() << "visCellCount:  " << visitedCellCount;

    for (int y = 2; y <= yNum-3; y+=2)
    {
        for (int x = 2; x <= xNum-3; x+=2)
        {
            cell[y][x].setVisited(false);
        }
    }

    if ((playCells - blockedCellsNum) != visitedCellCount)
        return false;

    return true;
}


// проверка клетки на посещенность
void Field::checkCell(int y, int x, int &visitedCellCount)
{
    visitedCellCount++;
    cell[y][x].setVisited(true);
    cell[y][x].testVisitedNum = visitedCellCount;


    if ((cell[y][x-1].materialType() != MaterialType::Wall) &&
        (!cell[y][x-2].blocked()) && (!cell[y][x-2].visited()))
        checkCell(y, x-2, visitedCellCount);

    if ((cell[y-1][x].materialType() != MaterialType::Wall) &&
        (!cell[y-2][x].blocked()) && (!cell[y-2][x].visited()))
        checkCell(y-2, x, visitedCellCount);

    if ((cell[y][x+1].materialType() != MaterialType::Wall) &&
        (!cell[y][x+2].blocked()) && (!cell[y][x+2].visited()))
        checkCell(y, x+2, visitedCellCount);

    if ((cell[y+1][x].materialType() != MaterialType::Wall) &&
        (!cell[y+2][x].blocked()) && (!cell[y+2][x].visited()))
        checkCell(y+2, x, visitedCellCount);

//    if ((cell[y][x-1].materialType() != MaterialType::Wall) &&
//        (cell[y][x-2].materialType() != MaterialType::Concrete) && (!cell[y][x-2].visited()))
//        checkCell(y, x-2, visitedCellCount);

//    if ((cell[y-1][x].materialType() != MaterialType::Wall) &&
//        (cell[y-2][x].materialType() != MaterialType::Concrete) && (!cell[y-2][x].visited()))
//        checkCell(y-2, x, visitedCellCount);

//    if ((cell[y][x+1].materialType() != MaterialType::Wall) &&
//        (cell[y][x+2].materialType() != MaterialType::Concrete) && (!cell[y][x+2].visited()))
//        checkCell(y, x+2, visitedCellCount);

//    if ((cell[y+1][x].materialType() != MaterialType::Wall) &&
//        (cell[y+2][x].materialType() != MaterialType::Concrete) && (!cell[y+2][x].visited()))
//        checkCell(y+2, x, visitedCellCount);
}
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
// ФУНКЦИИ РАНДОМА И РАССТАНОВКИ ЭЛЕМЕНТОВ
//--------------------------------------------------------------------------------
// установка стартового состояния полей (трава, бетон)
void Field::setBasicFields()
{
    //--------------------------------------------------------------------------------
    // out grass square (top & bottom)
    for (int x = 0; x < xNum; x+=2)
    {
        int y = 0;
        cell[y][x].setCellTypes(FormType::Square, MaterialType::Grass,
                                ObjectType::None, ObjectState::None, HoleType::None);

        y = yNum-1;
        cell[y][x].setCellTypes(FormType::Square, MaterialType::Grass,
                                ObjectType::None, ObjectState::None, HoleType::None);
    }
    // out grass square (left & right)
    for (int y = 2; y < yNum-2; y+=2)
    {
        int x = 0;
        cell[y][x].setCellTypes(FormType::Square, MaterialType::Grass,
                                ObjectType::None, ObjectState::None, HoleType::None);

        x = xNum-1;
        cell[y][x].setCellTypes(FormType::Square, MaterialType::Grass,
                                ObjectType::None, ObjectState::None, HoleType::None);
    }
    // out grass ver (top & bottom)
    for (int x = 1; x < xNum-1; x+=2)
    {
        int y = 0;
        cell[y][x].setCellTypes(FormType::Vertical, MaterialType::Grass,
                                ObjectType::None, ObjectState::None, HoleType::None);

        y = yNum-1;
        cell[y][x].setCellTypes(FormType::Vertical, MaterialType::Grass,
                                ObjectType::None, ObjectState::None, HoleType::None);
    }
    // out grass gor (left & right)
    for (int y = 1; y < yNum-1; y+=2)
    {
        int x = 0;
        cell[y][x].setCellTypes(FormType::Gorizontal, MaterialType::Grass,
                                ObjectType::None, ObjectState::None, HoleType::None);

        x = xNum-1;
        cell[y][x].setCellTypes(FormType::Gorizontal, MaterialType::Grass,
                                ObjectType::None, ObjectState::None, HoleType::None);
    }
    //--------------------------------------------------------------------------------
    // concrete (top & bottom)
    for (int x = 2; x < xNum-2; x+=2)
    {
        int y = 1;
        cell[y][x].setCellTypes(FormType::Gorizontal, MaterialType::Concrete,
                                ObjectType::None, ObjectState::None, HoleType::None);
        y = yNum-2;
        cell[y][x].setCellTypes(FormType::Gorizontal, MaterialType::Concrete,
                                ObjectType::None, ObjectState::None, HoleType::None);
    }
    // concrete (left & right)
    for (int y = 2; y < yNum-2; y+=2)
    {
        int x = 1;
        cell[y][x].setCellTypes(FormType::Vertical, MaterialType::Concrete,
                                ObjectType::None, ObjectState::None, HoleType::None);

        x = xNum-2;
        cell[y][x].setCellTypes(FormType::Vertical, MaterialType::Concrete,
                                ObjectType::None, ObjectState::None, HoleType::None);
    }
    // concrete pillar (top & bottom)
    for (int x = 1; x < xNum-1; x+=2)
    {
        int y = 1;
        cell[y][x].setCellTypes(FormType::Pillar, MaterialType::Concrete,
                                ObjectType::None, ObjectState::None, HoleType::None);

        y = yNum-2;
        cell[y][x].setCellTypes(FormType::Pillar, MaterialType::Concrete,
                                ObjectType::None, ObjectState::None, HoleType::None);
    }
    // concrete pillar (left & right)
    for (int y = 3; y < yNum-3; y+=2)
    {
        int x = 1;
        cell[y][x].setCellTypes(FormType::Pillar, MaterialType::Concrete,
                                ObjectType::None, ObjectState::None, HoleType::None);

        x = xNum-2;
        cell[y][x].setCellTypes(FormType::Pillar, MaterialType::Concrete,
                                ObjectType::None, ObjectState::None, HoleType::None);
    }
    // main field
    for (int y = 2; y <= yNum-3; y+=2)
    {
        for (int x = 2; x <= xNum-3; x+=2)
        {
            cell[y][x].setCellTypes(FormType::Square, MaterialType::Field,
                                    ObjectType::None, ObjectState::None, HoleType::None);

            cell[y][x].setBlocked(false);
        }
    }
    // start gorizontal wall
    for (int y = 3; y < yNum-3; y+=2)
    {
        for (int x = 2; x <= xNum-3; x+=2)
        {
            cell[y][x].setCellTypes(FormType::Gorizontal, MaterialType::Field,
                                    ObjectType::None, ObjectState::None, HoleType::None);
            cell[y][x].setBlocked(false);
        }
    }
    // start vertical wall
    for (int y = 2; y <= yNum-3; y+=2)
    {
        for (int x = 3; x < xNum-3; x+=2)
        {
            cell[y][x].setCellTypes(FormType::Vertical, MaterialType::Field,
                                    ObjectType::None, ObjectState::None, HoleType::None);
            cell[y][x].setBlocked(false);
        }
    }
    // start pillar
    for (int y = 3; y < yNum-3; y+=2)
    {
        for (int x = 3; x < xNum-3; x+=2)
        {
            cell[y][x].setCellTypes(FormType::Pillar, MaterialType::Wall,
                                    ObjectType::None, ObjectState::None, HoleType::None);
        }
    }
    //--------------------------------------------------------------------------------
}


// определение положения настоящих кладов
void Field::setRealTreasures(GameSettings *settings, int &blockedCellsNum)
{
    int realTreasureNum   = 0;

    Position currPos;
    currPos.y = (rand() % settings->fieldHeight() + 1) * 2;
    currPos.x = (rand() % settings->fieldWidth() + 1) * 2;
    cell[currPos.y][currPos.x].setBlocked(true);
    cell[currPos.y][currPos.x].setObjectType(ObjectType::RealTreasure);
    usedPos.push_back(currPos);
    realTreasureNum++;
    blockedCellsNum++;
//    qDebug() << "real:  y = " << currPos.y << "    x = " << currPos.x;

    while (realTreasureNum != settings->realTreasureNum())
    {
        Position pos;
        srand(time(NULL));
        pos.y = (rand() % settings->fieldHeight() + 1) * 2;
        pos.x = (rand() % settings->fieldWidth() + 1) * 2;

        for (int i = 0; i < (int)usedPos.size(); i++)
        {
            // новый рандом при совпадении с элеменами в списке
            if ((pos.y == usedPos[i].y) && (pos.x == usedPos[i].x))
            {
                break;
            }

            // если не совпало со всеми текущими элементами
            if (i == (int)usedPos.size()-1)
            {
                cell[pos.y][pos.x].setBlocked(true);
                blockedCellsNum++;
//                qDebug() << " real: y = " << pos.y << "    x = " << pos.x;

                // проверка доступности остальных ячеек полей
                if (checkFreeAccess(settings, blockedCellsNum))
                {
                    usedPos.push_back(pos);
                    cell[pos.y][pos.x].setObjectType(ObjectType::RealTreasure);
                    realTreasureNum++;
                }
                else
                {
                    cell[pos.y][pos.x].setBlocked(false);
                    blockedCellsNum--;
                }
            }
        }
    }   // end while
}


// определение положения ложных кладов
void Field::setFakeTreasures(GameSettings *settings, int &blockedCellsNum)
{
    int fakeTreasureNum = 0;
    while (fakeTreasureNum != settings->fakeTreasureNum())
    {
        Position pos;
        pos.y = (rand() % settings->fieldHeight() + 1) * 2;
        pos.x = (rand() % settings->fieldWidth() + 1) * 2;

        for (int i = 0; i < (int)usedPos.size(); i++)
        {
            // новый рандом при совпадении с элеменами в списке
            if ((pos.y == usedPos[i].y) && (pos.x == usedPos[i].x))
            {
                break;
            }

            // если не совпало со всеми текущими элементами
            if (i == (int)usedPos.size()-1)
            {
                cell[pos.y][pos.x].setBlocked(true);
                blockedCellsNum++;
//                qDebug() << "y = " << pos.y << "    x = " << pos.x;

                // проверка доступности остальных ячеек полей
                if (checkFreeAccess(settings, blockedCellsNum))
                {
                    usedPos.push_back(pos);
                    cell[pos.y][pos.x].setObjectType(ObjectType::FakeTreasure);
                    fakeTreasureNum++;
                }
                else
                {
                    cell[pos.y][pos.x].setBlocked(false);
                    blockedCellsNum--;
                }
            }
        }
    }   // end while
}


// установка стен кладов
void Field::setTreasuresWalls()
{
    for (int i = 0; i < (int)usedPos.size(); i++)
    {
        int y = usedPos[i].y;
        int x = usedPos[i].x;
        if ((cell[y][x].objectType() == ObjectType::RealTreasure) ||
            (cell[y][x].objectType() == ObjectType::FakeTreasure) )
        {
            if (!cell[y-1][x].blocked())
            {
                cell[y-1][x].setMaterialType(MaterialType::Wall);
                cell[y-1][x].setBlocked(true);
            }
            if (!cell[y][x+1].blocked())
            {
                cell[y][x+1].setMaterialType(MaterialType::Wall);
                cell[y][x+1].setBlocked(true);
            }
            if (!cell[y+1][x].blocked())
            {
                cell[y+1][x].setMaterialType(MaterialType::Wall);
                cell[y+1][x].setBlocked(true);
            }
            if (!cell[y][x-1].blocked())
            {
                cell[y][x-1].setMaterialType(MaterialType::Wall);
                cell[y][x-1].setBlocked(true);
            }
        }
    }
}


// определение положений арсеналов
void Field::setArsenals(GameSettings *settings, int &blockedCellsNum)
{
    int arsenalNum = 0;
    while (arsenalNum != settings->arsenalNum())
    {
        Position pos;
        pos.y = (rand() % settings->fieldHeight() + 1) * 2;
        pos.x = (rand() % settings->fieldWidth() + 1) * 2;
//        qDebug() << "Y = " << pos.y << "    X = " << pos.x;

        for (int i = 0; i < (int)usedPos.size(); i++)
        {
            // новый рандом при совпадении с элеменами в списке
            if ((pos.y == usedPos[i].y) && (pos.x == usedPos[i].x))
            {
                break;
            }

            // если не совпало со всеми текущими элементами
            if (i == (int)usedPos.size()-1)
            {
                cell[pos.y][pos.x].setBlocked(true);
                blockedCellsNum++;
//                qDebug() << "y = " << pos.y << "    x = " << pos.x;

                // проверка доступности остальных ячеек полей
                if (checkFreeAccess(settings, blockedCellsNum))
                {
                    usedPos.push_back(pos);
                    cell[pos.y][pos.x].setObjectType(ObjectType::Arsenal);
                    arsenalNum++;
                }
                else
                {
                    cell[pos.y][pos.x].setBlocked(false);
                    blockedCellsNum--;
                }
            }
        }
    }   // end while
}


// установка стен арсеналов
void Field::setArsenalsWalls()
{
    for (int i = 0; i < (int)usedPos.size(); i++)
    {
        int y = usedPos[i].y;
        int x = usedPos[i].x;
        if (cell[y][x].objectType() == ObjectType::Arsenal)
        {
            int rightRandom = false;
            while (!rightRandom)
            {
                // up = 0, right = 1, bottom = 2, left = 3
                int rndVal = rand() % 4;

                if ((rndVal == 0) && (cell[y-2][x].objectType() != ObjectType::Arsenal))
                {
                    if (!cell[y-1][x].blocked())
                    {
                        cell[y-1][x].setMaterialType(MaterialType::Field);
                        cell[y-1][x].setBlocked(true);

                        if (!cell[y][x+1].blocked())
                        {
                            cell[y][x+1].setMaterialType(MaterialType::Wall);
                            cell[y][x+1].setBlocked(true);
                        }
                        if (!cell[y+1][x].blocked())
                        {
                            cell[y+1][x].setMaterialType(MaterialType::Wall);
                            cell[y+1][x].setBlocked(true);
                        }
                        if (!cell[y][x-1].blocked())
                        {
                            cell[y][x-1].setMaterialType(MaterialType::Wall);
                            cell[y][x-1].setBlocked(true);
                        }
                        rightRandom = true;
                    }
                }
                else if ((rndVal == 1) && (cell[y][x+2].objectType() != ObjectType::Arsenal))
                {
                    if (!cell[y][x+1].blocked())
                    {
                        cell[y][x+1].setMaterialType(MaterialType::Field);
                        cell[y][x+1].setBlocked(true);

                        if (!cell[y-1][x].blocked())
                        {
                            cell[y-1][x].setMaterialType(MaterialType::Wall);
                            cell[y-1][x].setBlocked(true);
                        }
                        if (!cell[y+1][x].blocked())
                        {
                            cell[y+1][x].setMaterialType(MaterialType::Wall);
                            cell[y+1][x].setBlocked(true);
                        }
                        if (!cell[y][x-1].blocked())
                        {
                            cell[y][x-1].setMaterialType(MaterialType::Wall);
                            cell[y][x-1].setBlocked(true);
                        }
                        rightRandom = true;
                    }
                }
                else if ((rndVal == 2) && (cell[y+2][x].objectType() != ObjectType::Arsenal))
                {
                    if (!cell[y+1][x].blocked())
                    {
                        cell[y+1][x].setMaterialType(MaterialType::Field);
                        cell[y+1][x].setBlocked(true);

                        if (!cell[y][x+1].blocked())
                        {
                            cell[y][x+1].setMaterialType(MaterialType::Wall);
                            cell[y][x+1].setBlocked(true);
                        }
                        if (!cell[y-1][x].blocked())
                        {
                            cell[y-1][x].setMaterialType(MaterialType::Wall);
                            cell[y-1][x].setBlocked(true);
                        }
                        if (!cell[y][x-1].blocked())
                        {
                            cell[y][x-1].setMaterialType(MaterialType::Wall);
                            cell[y][x-1].setBlocked(true);
                        }
                        rightRandom = true;
                    }
                }
                else if ((rndVal == 3) && (cell[y][x-2].objectType() != ObjectType::Arsenal))
                {
                    if (!cell[y][x-1].blocked())
                    {
                        cell[y][x-1].setMaterialType(MaterialType::Field);
                        cell[y][x-1].setBlocked(true);

                        if (!cell[y][x+1].blocked())
                        {
                            cell[y][x+1].setMaterialType(MaterialType::Wall);
                            cell[y][x+1].setBlocked(true);
                        }
                        if (!cell[y+1][x].blocked())
                        {
                            cell[y+1][x].setMaterialType(MaterialType::Wall);
                            cell[y+1][x].setBlocked(true);
                        }
                        if (!cell[y-1][x].blocked())
                        {
                            cell[y-1][x].setMaterialType(MaterialType::Wall);
                            cell[y-1][x].setBlocked(true);
                        }
                        rightRandom = true;
                    }
                }
            }	// end while (!rightRandom)
        }   // end if cell == arsenal
    }
}


// определение положения остальных стен
void Field::setWallsPositions(GameSettings *settings, Position &pos, int &blockedCellsNum)
{
    int y = pos.y;
    int x = pos.x;

    int rightRandom = false;
    while (!rightRandom)
    {
        int currBlockWallNum = 0;

        //--------------------------------------------------
        // up wall
        //--------------------------------------------------
        if (!cell[y][x+1].blocked())
        {
            if ( (rand() % 2) == 1)
            {
                cell[y][x+1].setMaterialType(MaterialType::Wall);
                currBlockWallNum++;
            }
            else
            {
                cell[y][x+1].setMaterialType(MaterialType::Field);

                Position upBlockPos;
                upBlockPos.y = y - 2;
                upBlockPos.x = x;
                int wallNum = blockWallNumCalc(upBlockPos);

                // заблокировать оставшуюся стену
                if (wallNum == 1)
                    blockSingleWall(upBlockPos);
            }
        }
        else
        {
            if (cell[y][x+1].materialType() == MaterialType::Wall)
            {
                currBlockWallNum++;
            }
        }
        //--------------------------------------------------

        //--------------------------------------------------
        // right wall
        //--------------------------------------------------
        if (!cell[y+1][x+2].blocked())
        {
            if ( (rand() % 2) == 1)
            {
                cell[y+1][x+2].setMaterialType(MaterialType::Wall);
                currBlockWallNum++;
            }
            else
            {
                cell[y+1][x+2].setMaterialType(MaterialType::Field);
            }
        }
        else
        {
            if (cell[y+1][x+2].materialType() == MaterialType::Wall)
            {
                currBlockWallNum++;
            }
        }
        //--------------------------------------------------

        //--------------------------------------------------
        // bottom wall
        //--------------------------------------------------
        if (!cell[y+2][x+1].blocked())
        {
            if ( (rand() % 2) == 1)
            {
                cell[y+2][x+1].setMaterialType(MaterialType::Wall);    
                currBlockWallNum++;
            }
            else
            {
                cell[y+2][x+1].setMaterialType(MaterialType::Field);
            }
        }
        else
        {
            if (cell[y+2][x+1].materialType() == MaterialType::Wall)
            {
                currBlockWallNum++;
            }
        }
        //--------------------------------------------------

        //--------------------------------------------------
        // left wall
        //--------------------------------------------------
        if (!cell[y+1][x].blocked())
        {
            if ( (rand() % 2) == 1)
            {
                cell[y+1][x].setMaterialType(MaterialType::Wall);
                currBlockWallNum++;
            }
            else
            {
                cell[y+1][x].setMaterialType(MaterialType::Field);

                Position leftBlockPos;
                leftBlockPos.y = y;
                leftBlockPos.x = x - 2;
                int wallNum = blockWallNumCalc(leftBlockPos);

                // заблокировать оставшуюся стену
                if (wallNum == 1)
                    blockSingleWall(leftBlockPos);
            }
        }
        else
        {
            if (cell[y+1][x].materialType() == MaterialType::Wall)
            {
                currBlockWallNum++;
            }
        }
        //--------------------------------------------------

        //--------------------------------------------------
        // test enough space
        bool testLabyMin;
        if (currBlockWallNum < 1)
            testLabyMin = false;
        else
            testLabyMin = true;

        // test enough wall
        bool testLabyMax = checkFreeAccess(settings, blockedCellsNum);
        //--------------------------------------------------


        //--------------------------------------------------
        // save or cancel random results
        if (testLabyMin && testLabyMax)
        {
            // if (wallNum = 1) => need block it
            if (currBlockWallNum == 1)
            {
                Position currPos;
                currPos.y = y;
                currPos.x = x;

                blockSingleWall(currPos);
            }
            rightRandom = true;
        }
        else
        {
            if (!cell[y][x+1].blocked())
                cell[y][x+1].setMaterialType(MaterialType::Field);
            if (!cell[y+1][x+2].blocked())
                cell[y+1][x+2].setMaterialType(MaterialType::Field);
            if (!cell[y+2][x+1].blocked())
                cell[y+2][x+1].setMaterialType(MaterialType::Field);
            if (!cell[y+1][x].blocked())
                cell[y+1][x].setMaterialType(MaterialType::Field);
        }
        //--------------------------------------------------
    }	// end while (!rightRandom)
}


// расчет количества текущих стен в блоке
int Field::blockWallNumCalc(Position &pos)
{
    int y = pos.y;
    int x = pos.x;

    int wallNum = 0;
    if (cell[y][x+1].materialType() == MaterialType::Wall)
        wallNum++;
    if (cell[y+1][x+2].materialType() == MaterialType::Wall)
       wallNum++;
    if (cell[y+2][x+1].materialType() == MaterialType::Wall)
        wallNum++;
    if (cell[y+1][x].materialType() == MaterialType::Wall)
        wallNum++;

    return wallNum;
}


// блокировка единственной стены в блоке
void Field::blockSingleWall(Position &pos)
{
    int y = pos.y;
    int x = pos.x;

    if (cell[y][x+1].materialType() == MaterialType::Wall)
        cell[y][x+1].setBlocked(true);
    if (cell[y+1][x+2].materialType() == MaterialType::Wall)
        cell[y+1][x+2].setBlocked(true);
    if (cell[y+2][x+1].materialType() == MaterialType::Wall)
        cell[y+2][x+1].setBlocked(true);
    if (cell[y+1][x].materialType() == MaterialType::Wall)
        cell[y+1][x].setBlocked(true);
}


//  определение положения выходов
void Field::setExits(GameSettings *settings)
{
    // up exit
    int rightRandom = false;
    while (!rightRandom)
    {
        int y = 1;
        int x = (rand() % settings->fieldWidth() + 1) * 2;
        if ((cell[y+1][x].objectType() != ObjectType::RealTreasure) &&
            (cell[y+1][x].objectType() != ObjectType::FakeTreasure) &&
            (cell[y+1][x].objectType() != ObjectType::Arsenal))
        {
            cell[y][x].setMaterialType(MaterialType::Exit);
            rightRandom = true;
        }
    }
    // right exit
    rightRandom = false;
    while (!rightRandom)
    {
        int y = (rand() % settings->fieldHeight() + 1) * 2;
        int x = (settings->fieldWidth() * 2 + 3) - 2;
        if ((cell[y][x-1].objectType() != ObjectType::RealTreasure) &&
            (cell[y][x-1].objectType() != ObjectType::FakeTreasure) &&
            (cell[y][x-1].objectType() != ObjectType::Arsenal))
        {
            cell[y][x].setMaterialType(MaterialType::Exit);
            rightRandom = true;
        }
    }
    // bottom exit
    rightRandom = false;
    while (!rightRandom)
    {
        int y = (settings->fieldHeight() * 2 + 3) - 2;
        int x = (rand() % settings->fieldWidth() + 1) * 2;
        if ((cell[y-1][x].objectType() != ObjectType::RealTreasure) &&
            (cell[y-1][x].objectType() != ObjectType::FakeTreasure) &&
            (cell[y-1][x].objectType() != ObjectType::Arsenal))
        {
            cell[y][x].setMaterialType(MaterialType::Exit);
            rightRandom = true;
        }
    }
    // left exit
    rightRandom = false;
    while (!rightRandom)
    {
        int y = (rand() % settings->fieldHeight() + 1) * 2;
        int x = 1;
        if ((cell[y][x+1].objectType() != ObjectType::RealTreasure) &&
            (cell[y][x+1].objectType() != ObjectType::FakeTreasure) &&
            (cell[y][x+1].objectType() != ObjectType::Arsenal))
        {
            cell[y][x].setMaterialType(MaterialType::Exit);
            rightRandom = true;
        }
    }
}


// определение положения ям
void Field::setHoles(GameSettings *settings)
{
    int holeNum = 0;
    while (holeNum != 2)
    {
        int y = (rand() % settings->fieldHeight() + 1) * 2;
        int x = (rand() % settings->fieldWidth() + 1) * 2;

        if ((cell[y][x].objectType() != ObjectType::RealTreasure) &&
            (cell[y][x].objectType() != ObjectType::FakeTreasure) &&
            (cell[y][x].objectType() != ObjectType::Arsenal) &&
            (cell[y][x].objectType() != ObjectType::Hole))
        {
            cell[y][x].setObjectType(ObjectType::Hole);
            holeNum++;

            if (holeNum == 1)
                cell[y][x].setHoleType(HoleType::TypeI);
            else
                cell[y][x].setHoleType(HoleType::TypeII);
        }
    }

    if (settings->holeTypeNum() > 1)
    {
        holeNum = 0;
        while (holeNum != 3)
        {
            int y = (rand() % settings->fieldHeight() + 1) * 2;
            int x = (rand() % settings->fieldWidth() + 1) * 2;

            if ((cell[y][x].objectType() != ObjectType::RealTreasure) &&
                (cell[y][x].objectType() != ObjectType::FakeTreasure) &&
                (cell[y][x].objectType() != ObjectType::Arsenal) &&
                (cell[y][x].objectType() != ObjectType::Hole))
            {
                cell[y][x].setObjectType(ObjectType::Hole);
                holeNum++;

                if (holeNum == 1)
                    cell[y][x].setHoleType(HoleType::TypeA);
                else if (holeNum == 2)
                    cell[y][x].setHoleType(HoleType::TypeB);
                else
                    cell[y][x].setHoleType(HoleType::TypeC);
            }
        }
    }
}
//--------------------------------------------------------------------------------
