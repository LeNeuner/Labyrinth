#include "playerfieldinfo.h"

#include <cstdlib>
#include <ctime>

#include <QDebug>
#include <iostream>
#include <windows.h>


PlayerFieldInfo::PlayerFieldInfo(QObject *parent) :
    QObject(parent),
    width(defaultWidth),
    height(defaultHeight),
    xNum(defaultWidth * 2 + 3),
    yNum(defaultHeight *2 + 3)
{
}

PlayerFieldInfo::~PlayerFieldInfo()
{
    // очистка предыдущего поля
    if (playerCell != nullptr)
    {
        delete playerCell;
        playerCell = nullptr;
    }
}

//--------------------------------------------------------------------------------
// создание игрового поля
void PlayerFieldInfo::createPlayerField(GameSettings *settings)
{
     // получение значения настроек поля
     width   = settings->fieldWidth();
     height  = settings->fieldHeight();
     xNum    = width  * 2 + 3;
     yNum    = height * 2 + 3;

     // очистка предыдущего поля
     if (playerCell != nullptr)
     {
         delete playerCell;
         playerCell = nullptr;
     }

     // создание поля соответствующего размера
     playerCell = new PlayerCellInfo* [yNum];
     for (int y = 0; y < yNum; y++)
     {
         playerCell[y] = new PlayerCellInfo [xNum];
     }

     // закрытие всех ячеек
     for (int y = 0; y < yNum; y+=1)
     {
         for (int x = 0; x < xNum; x+=1)
         {
             playerCell[y][x].setCellState(CellState::Closed);
         }
     }

     // открытие колон
     for (int y = 3; y < yNum-3; y+=2)
     {
         for (int x = 3; x < xNum-3; x+=2)
         {
             playerCell[y][x].setCellState(CellState::Opened);
         }
     }

     // установка стартового состояния полей (трава, бетон) (полупрозрачно)
//     setBasicFields();
}
//--------------------------------------------------------------------------------


// //--------------------------------------------------------------------------------
// // ФУНКЦИИ РАНДОМА И РАССТАНОВКИ ЭЛЕМЕНТОВ
// //--------------------------------------------------------------------------------
// // установка стартового состояния полей (трава, бетон)
// void Field::setBasicFields()
// {
//     //--------------------------------------------------------------------------------
//     // out grass square (top & bottom)
//     for (int x = 0; x < xNum; x+=2)
//     {
//         int y = 0;
//         cell[y][x].setCellTypes(FormType::Square, MaterialType::Grass,
//                                 ObjectType::None, ObjectState::None);
//
//         y = yNum-1;
//         cell[y][x].setCellTypes(FormType::Square, MaterialType::Grass,
//                                 ObjectType::None, ObjectState::None);
//     }
//     // out grass square (left & right)
//     for (int y = 2; y < yNum-2; y+=2)
//     {
//         int x = 0;
//         cell[y][x].setCellTypes(FormType::Square, MaterialType::Grass,
//                                 ObjectType::None, ObjectState::None);
//
//         x = xNum-1;
//         cell[y][x].setCellTypes(FormType::Square, MaterialType::Grass,
//                                 ObjectType::None, ObjectState::None);
//     }
//     // out grass ver (top & bottom)
//     for (int x = 1; x < xNum-1; x+=2)
//     {
//         int y = 0;
//         cell[y][x].setCellTypes(FormType::Vertical, MaterialType::Grass,
//                                 ObjectType::None, ObjectState::None);
//
//         y = yNum-1;
//         cell[y][x].setCellTypes(FormType::Vertical, MaterialType::Grass,
//                                 ObjectType::None, ObjectState::None);
//     }
//     // out grass gor (left & right)
//     for (int y = 1; y < yNum-1; y+=2)
//     {
//         int x = 0;
//         cell[y][x].setCellTypes(FormType::Gorizontal, MaterialType::Grass,
//                                 ObjectType::None, ObjectState::None);
//
//         x = xNum-1;
//         cell[y][x].setCellTypes(FormType::Gorizontal, MaterialType::Grass,
//                                 ObjectType::None, ObjectState::None);
//     }
//     //--------------------------------------------------------------------------------
//     // concrete (top & bottom)
//     for (int x = 2; x < xNum-2; x+=2)
//     {
//         int y = 1;
//         cell[y][x].setCellTypes(FormType::Gorizontal, MaterialType::Concrete,
//                                 ObjectType::None, ObjectState::None);
//         y = yNum-2;
//         cell[y][x].setCellTypes(FormType::Gorizontal, MaterialType::Concrete,
//                                 ObjectType::None, ObjectState::None);
//     }
//     // concrete (left & right)
//     for (int y = 2; y < yNum-2; y+=2)
//     {
//         int x = 1;
//         cell[y][x].setCellTypes(FormType::Vertical, MaterialType::Concrete,
//                                 ObjectType::None, ObjectState::None);
//
//         x = xNum-2;
//         cell[y][x].setCellTypes(FormType::Vertical, MaterialType::Concrete,
//                                 ObjectType::None, ObjectState::None);
//     }
//     // concrete pillar (top & bottom)
//     for (int x = 1; x < xNum-1; x+=2)
//     {
//         int y = 1;
//         cell[y][x].setCellTypes(FormType::Pillar, MaterialType::Concrete,
//                                 ObjectType::None, ObjectState::None);
//
//         y = yNum-2;
//         cell[y][x].setCellTypes(FormType::Pillar, MaterialType::Concrete,
//                                 ObjectType::None, ObjectState::None);
//     }
//     // concrete pillar (left & right)
//     for (int y = 3; y < yNum-3; y+=2)
//     {
//         int x = 1;
//         cell[y][x].setCellTypes(FormType::Pillar, MaterialType::Concrete,
//                                 ObjectType::None, ObjectState::None);
//
//         x = xNum-2;
//         cell[y][x].setCellTypes(FormType::Pillar, MaterialType::Concrete,
//                                 ObjectType::None, ObjectState::None);
//     }
//     // main field
//     for (int y = 2; y <= yNum-3; y+=2)
//     {
//         for (int x = 2; x <= xNum-3; x+=2)
//         {
//             cell[y][x].setCellTypes(FormType::Square, MaterialType::Field,
//                                     ObjectType::None, ObjectState::None);
//
//             cell[y][x].setBlocked(false);
//         }
//     }
//     // start gorizontal wall
//     for (int y = 3; y < yNum-3; y+=2)
//     {
//         for (int x = 2; x <= xNum-3; x+=2)
//         {
//             cell[y][x].setCellTypes(FormType::Gorizontal, MaterialType::Field,
//                                     ObjectType::None, ObjectState::None);
//             cell[y][x].setBlocked(false);
//         }
//     }
//     // start vertical wall
//     for (int y = 2; y <= yNum-3; y+=2)
//     {
//         for (int x = 3; x < xNum-3; x+=2)
//         {
//             cell[y][x].setCellTypes(FormType::Vertical, MaterialType::Field,
//                                     ObjectType::None, ObjectState::None);
//             cell[y][x].setBlocked(false);
//         }
//     }
//     // start pillar
//     for (int y = 3; y < yNum-3; y+=2)
//     {
//         for (int x = 3; x < xNum-3; x+=2)
//         {
//             cell[y][x].setCellTypes(FormType::Pillar, MaterialType::Wall,
//                                     ObjectType::None, ObjectState::None);
//         }
//     }
//     //--------------------------------------------------------------------------------
// }
//
//
// // определение положения настоящих кладов
// void Field::setRealTreasures(GameSettings *settings, int &blockedCellsNum)
// {
//     int realTreasureNum   = 0;
//
//     Position currPos;
//     currPos.y = (rand() % settings->fieldHeight() + 1) * 2;
//     currPos.x = (rand() % settings->fieldWidth() + 1) * 2;
//     cell[currPos.y][currPos.x].setBlocked(true);
//     cell[currPos.y][currPos.x].setObjectType(ObjectType::RealTreasure);
//     usedPos.push_back(currPos);
//     realTreasureNum++;
//     blockedCellsNum++;
//
//     while (realTreasureNum != settings->realTreasureNum())
//     {
//         Position pos;
//         srand(time(NULL));
//         pos.y = (rand() % settings->fieldHeight() + 1) * 2;
//         pos.x = (rand() % settings->fieldWidth() + 1) * 2;
//
//         for (int i = 0; i < (int)usedPos.size(); i++)
//         {
//             // новый рандом при совпадении с элеменами в списке
//             if ((pos.y == usedPos[i].y) && (pos.x == usedPos[i].x))
//             {
//                 break;
//             }
//
//             // если не совпало со всеми текущими элементами
//             if (i == (int)usedPos.size()-1)
//             {
//                 cell[pos.y][pos.x].setBlocked(true);
//                 blockedCellsNum++;
//
//                 // проверка доступности остальных ячеек полей
//                 if (checkFreeAccess(settings, blockedCellsNum))
//                 {
//                     usedPos.push_back(pos);
//                     cell[pos.y][pos.x].setObjectType(ObjectType::RealTreasure);
//                     realTreasureNum++;
//                 }
//                 else
//                 {
//                     cell[pos.y][pos.x].setBlocked(false);
//                     blockedCellsNum--;
//                 }
//             }
//         }
//     }   // end while
// }
//
//
// // определение положения ложных кладов
// void Field::setFakeTreasures(GameSettings *settings, int &blockedCellsNum)
// {
//     int fakeTreasureNum = 0;
//     while (fakeTreasureNum != settings->fakeTreasureNum())
//     {
//         Position pos;
//         pos.y = (rand() % settings->fieldHeight() + 1) * 2;
//         pos.x = (rand() % settings->fieldWidth() + 1) * 2;
//
//         for (int i = 0; i < (int)usedPos.size(); i++)
//         {
//             // новый рандом при совпадении с элеменами в списке
//             if ((pos.y == usedPos[i].y) && (pos.x == usedPos[i].x))
//             {
//                 break;
//             }
//
//             // если не совпало со всеми текущими элементами
//             if (i == (int)usedPos.size()-1)
//             {
//                 cell[pos.y][pos.x].setBlocked(true);
//                 blockedCellsNum++;
//
//                 // проверка доступности остальных ячеек полей
//                 if (checkFreeAccess(settings, blockedCellsNum))
//                 {
//                     usedPos.push_back(pos);
//                     cell[pos.y][pos.x].setObjectType(ObjectType::FakeTreasure);
//                     fakeTreasureNum++;
//                 }
//                 else
//                 {
//                     cell[pos.y][pos.x].setBlocked(false);
//                     blockedCellsNum--;
//                 }
//             }
//         }
//     }   // end while
// }
//
//
// // установка стен кладов
// void Field::setTreasuresWalls()
// {
//     for (int i = 0; i < (int)usedPos.size(); i++)
//     {
//         int y = usedPos[i].y;
//         int x = usedPos[i].x;
//         if ((cell[y][x].objectType() == ObjectType::RealTreasure) ||
//             (cell[y][x].objectType() == ObjectType::FakeTreasure) )
//         {
//             if (!cell[y-1][x].blocked())
//             {
//                 cell[y-1][x].setMaterialType(MaterialType::Wall);
//                 cell[y-1][x].setBlocked(true);
//             }
//             if (!cell[y][x+1].blocked())
//             {
//                 cell[y][x+1].setMaterialType(MaterialType::Wall);
//                 cell[y][x+1].setBlocked(true);
//             }
//             if (!cell[y+1][x].blocked())
//             {
//                 cell[y+1][x].setMaterialType(MaterialType::Wall);
//                 cell[y+1][x].setBlocked(true);
//             }
//             if (!cell[y][x-1].blocked())
//             {
//                 cell[y][x-1].setMaterialType(MaterialType::Wall);
//                 cell[y][x-1].setBlocked(true);
//             }
//         }
//     }
// }
//
//
// // определение положений арсеналов
// void Field::setArsenals(GameSettings *settings, int &blockedCellsNum)
// {
//     int arsenalNum = 0;
//     while (arsenalNum != settings->arsenalNum())
//     {
//         Position pos;
//         pos.y = (rand() % settings->fieldHeight() + 1) * 2;
//         pos.x = (rand() % settings->fieldWidth() + 1) * 2;
//
//         for (int i = 0; i < (int)usedPos.size(); i++)
//         {
//             // новый рандом при совпадении с элеменами в списке
//             if ((pos.y == usedPos[i].y) && (pos.x == usedPos[i].x))
//             {
//                 break;
//             }
//
//             // если не совпало со всеми текущими элементами
//             if (i == (int)usedPos.size()-1)
//             {
//                 cell[pos.y][pos.x].setBlocked(true);
//                 blockedCellsNum++;
//
//                 // проверка доступности остальных ячеек полей
//                 if (checkFreeAccess(settings, blockedCellsNum))
//                 {
//                     usedPos.push_back(pos);
//                     cell[pos.y][pos.x].setObjectType(ObjectType::Arsenal);
//                     arsenalNum++;
//                 }
//                 else
//                 {
//                     cell[pos.y][pos.x].setBlocked(false);
//                     blockedCellsNum--;
//                 }
//             }
//         }
//     }   // end while
// }
//
//
// // установка стен арсеналов
// void Field::setArsenalsWalls()
// {
//     for (int i = 0; i < (int)usedPos.size(); i++)
//     {
//         int y = usedPos[i].y;
//         int x = usedPos[i].x;
//         if (cell[y][x].objectType() == ObjectType::Arsenal)
//         {
//             int rightRandom = false;
//             while (!rightRandom)
//             {
//                 // up = 0, right = 1, bottom = 2, left = 3
//                 int rndVal = rand() % 4;
//
//                 if ((rndVal == 0) && (cell[y-2][x].objectType() != ObjectType::Arsenal))
//                 {
//                     if (!cell[y-1][x].blocked())
//                     {
//                         cell[y-1][x].setMaterialType(MaterialType::Field);
//                         cell[y-1][x].setBlocked(true);
//
//                         if (!cell[y][x+1].blocked())
//                         {
//                             cell[y][x+1].setMaterialType(MaterialType::Wall);
//                             cell[y][x+1].setBlocked(true);
//                         }
//                         if (!cell[y+1][x].blocked())
//                         {
//                             cell[y+1][x].setMaterialType(MaterialType::Wall);
//                             cell[y+1][x].setBlocked(true);
//                         }
//                         if (!cell[y][x-1].blocked())
//                         {
//                             cell[y][x-1].setMaterialType(MaterialType::Wall);
//                             cell[y][x-1].setBlocked(true);
//                         }
//                         rightRandom = true;
//                     }
//                 }
//                 else if ((rndVal == 1) && (cell[y][x+2].objectType() != ObjectType::Arsenal))
//                 {
//                     if (!cell[y][x+1].blocked())
//                     {
//                         cell[y][x+1].setMaterialType(MaterialType::Field);
//                         cell[y][x+1].setBlocked(true);
//
//                         if (!cell[y-1][x].blocked())
//                         {
//                             cell[y-1][x].setMaterialType(MaterialType::Wall);
//                             cell[y-1][x].setBlocked(true);
//                         }
//                         if (!cell[y+1][x].blocked())
//                         {
//                             cell[y+1][x].setMaterialType(MaterialType::Wall);
//                             cell[y+1][x].setBlocked(true);
//                         }
//                         if (!cell[y][x-1].blocked())
//                         {
//                             cell[y][x-1].setMaterialType(MaterialType::Wall);
//                             cell[y][x-1].setBlocked(true);
//                         }
//                         rightRandom = true;
//                     }
//                 }
//                 else if ((rndVal == 2) && (cell[y+2][x].objectType() != ObjectType::Arsenal))
//                 {
//                     if (!cell[y+1][x].blocked())
//                     {
//                         cell[y+1][x].setMaterialType(MaterialType::Field);
//                         cell[y+1][x].setBlocked(true);
//
//                         if (!cell[y][x+1].blocked())
//                         {
//                             cell[y][x+1].setMaterialType(MaterialType::Wall);
//                             cell[y][x+1].setBlocked(true);
//                         }
//                         if (!cell[y-1][x].blocked())
//                         {
//                             cell[y-1][x].setMaterialType(MaterialType::Wall);
//                             cell[y-1][x].setBlocked(true);
//                         }
//                         if (!cell[y][x-1].blocked())
//                         {
//                             cell[y][x-1].setMaterialType(MaterialType::Wall);
//                             cell[y][x-1].setBlocked(true);
//                         }
//                         rightRandom = true;
//                     }
//                 }
//                 else if ((rndVal == 3) && (cell[y][x-2].objectType() != ObjectType::Arsenal))
//                 {
//                     if (!cell[y][x-1].blocked())
//                     {
//                         cell[y][x-1].setMaterialType(MaterialType::Field);
//                         cell[y][x-1].setBlocked(true);
//
//                         if (!cell[y][x+1].blocked())
//                         {
//                             cell[y][x+1].setMaterialType(MaterialType::Wall);
//                             cell[y][x+1].setBlocked(true);
//                         }
//                         if (!cell[y+1][x].blocked())
//                         {
//                             cell[y+1][x].setMaterialType(MaterialType::Wall);
//                             cell[y+1][x].setBlocked(true);
//                         }
//                         if (!cell[y-1][x].blocked())
//                         {
//                             cell[y-1][x].setMaterialType(MaterialType::Wall);
//                             cell[y-1][x].setBlocked(true);
//                         }
//                         rightRandom = true;
//                     }
//                 }
//             }	// end while (!rightRandom)
//         }   // end if cell == arsenal
//     }
// }
//
//
// // определение положения остальных стен
// void Field::setWallsPositions(GameSettings *settings, Position &pos, int &blockedCellsNum)
// {
//     int y = pos.y;
//     int x = pos.x;
//
//     int rightRandom = false;
//     while (!rightRandom)
//     {
//         int currBlockWallNum = 0;
//
//         //--------------------------------------------------
//         // up wall
//         //--------------------------------------------------
//         if (!cell[y][x+1].blocked())
//         {
//             if ( (rand() % 2) == 1)
//             {
//                 cell[y][x+1].setMaterialType(MaterialType::Wall);
//                 currBlockWallNum++;
//             }
//             else
//             {
//                 cell[y][x+1].setMaterialType(MaterialType::Field);
//
//                 Position upBlockPos;
//                 upBlockPos.y = y - 2;
//                 upBlockPos.x = x;
//                 int wallNum = blockWallNumCalc(upBlockPos);
//
//                 // заблокировать оставшуюся стену
//                 if (wallNum == 1)
//                     blockSingleWall(upBlockPos);
//             }
//         }
//         else
//         {
//             if (cell[y][x+1].materialType() == MaterialType::Wall)
//             {
//                 currBlockWallNum++;
//             }
//         }
//         //--------------------------------------------------
//
//         //--------------------------------------------------
//         // right wall
//         //--------------------------------------------------
//         if (!cell[y+1][x+2].blocked())
//         {
//             if ( (rand() % 2) == 1)
//             {
//                 cell[y+1][x+2].setMaterialType(MaterialType::Wall);
//                 currBlockWallNum++;
//             }
//             else
//             {
//                 cell[y+1][x+2].setMaterialType(MaterialType::Field);
//             }
//         }
//         else
//         {
//             if (cell[y+1][x+2].materialType() == MaterialType::Wall)
//             {
//                 currBlockWallNum++;
//             }
//         }
//         //--------------------------------------------------
//
//         //--------------------------------------------------
//         // bottom wall
//         //--------------------------------------------------
//         if (!cell[y+2][x+1].blocked())
//         {
//             if ( (rand() % 2) == 1)
//             {
//                 cell[y+2][x+1].setMaterialType(MaterialType::Wall);
//                 currBlockWallNum++;
//             }
//             else
//             {
//                 cell[y+2][x+1].setMaterialType(MaterialType::Field);
//             }
//         }
//         else
//         {
//             if (cell[y+2][x+1].materialType() == MaterialType::Wall)
//             {
//                 currBlockWallNum++;
//             }
//         }
//         //--------------------------------------------------
//
//         //--------------------------------------------------
//         // left wall
//         //--------------------------------------------------
//         if (!cell[y+1][x].blocked())
//         {
//             if ( (rand() % 2) == 1)
//             {
//                 cell[y+1][x].setMaterialType(MaterialType::Wall);
//                 currBlockWallNum++;
//             }
//             else
//             {
//                 cell[y+1][x].setMaterialType(MaterialType::Field);
//
//                 Position leftBlockPos;
//                 leftBlockPos.y = y;
//                 leftBlockPos.x = x - 2;
//                 int wallNum = blockWallNumCalc(leftBlockPos);
//
//                 // заблокировать оставшуюся стену
//                 if (wallNum == 1)
//                     blockSingleWall(leftBlockPos);
//             }
//         }
//         else
//         {
//             if (cell[y+1][x].materialType() == MaterialType::Wall)
//             {
//                 currBlockWallNum++;
//             }
//         }
//         //--------------------------------------------------
//
//         //--------------------------------------------------
//         // test enough space
//         bool testLabyMin;
//         if (currBlockWallNum < 1)
//             testLabyMin = false;
//         else
//             testLabyMin = true;
//
//         // test enough wall
//         bool testLabyMax = checkFreeAccess(settings, blockedCellsNum);
//         //--------------------------------------------------
//
//
//         //--------------------------------------------------
//         // save or cancel random results
//         if (testLabyMin && testLabyMax)
//         {
//             // if (wallNum = 1) => need block it
//             if (currBlockWallNum == 1)
//             {
//                 Position currPos;
//                 currPos.y = y;
//                 currPos.x = x;
//
//                 blockSingleWall(currPos);
//             }
//             rightRandom = true;
//         }
//         else
//         {
//             if (!cell[y][x+1].blocked())
//                 cell[y][x+1].setMaterialType(MaterialType::Field);
//             if (!cell[y+1][x+2].blocked())
//                 cell[y+1][x+2].setMaterialType(MaterialType::Field);
//             if (!cell[y+2][x+1].blocked())
//                 cell[y+2][x+1].setMaterialType(MaterialType::Field);
//             if (!cell[y+1][x].blocked())
//                 cell[y+1][x].setMaterialType(MaterialType::Field);
//         }
//         //--------------------------------------------------
//     }	// end while (!rightRandom)
// }
//
//
// // расчет количества текущих стен в блоке
// int Field::blockWallNumCalc(Position &pos)
// {
//     int y = pos.y;
//     int x = pos.x;
//
//     int wallNum = 0;
//     if (cell[y][x+1].materialType() == MaterialType::Wall)
//         wallNum++;
//     if (cell[y+1][x+2].materialType() == MaterialType::Wall)
//        wallNum++;
//     if (cell[y+2][x+1].materialType() == MaterialType::Wall)
//         wallNum++;
//     if (cell[y+1][x].materialType() == MaterialType::Wall)
//         wallNum++;
//
//     return wallNum;
// }
//
//
// // блокировка единственной стены в блоке
// void Field::blockSingleWall(Position &pos)
// {
//     int y = pos.y;
//     int x = pos.x;
//
//     if (cell[y][x+1].materialType() == MaterialType::Wall)
//         cell[y][x+1].setBlocked(true);
//     if (cell[y+1][x+2].materialType() == MaterialType::Wall)
//         cell[y+1][x+2].setBlocked(true);
//     if (cell[y+2][x+1].materialType() == MaterialType::Wall)
//         cell[y+2][x+1].setBlocked(true);
//     if (cell[y+1][x].materialType() == MaterialType::Wall)
//         cell[y+1][x].setBlocked(true);
// }
//
//
// //  определение положения выходов
// void Field::setExits(GameSettings *settings)
// {
//     // up exit
//     int rightRandom = false;
//     while (!rightRandom)
//     {
//         int y = 1;
//         int x = (rand() % settings->fieldWidth() + 1) * 2;
//         if ((cell[y+1][x].objectType() != ObjectType::RealTreasure) &&
//             (cell[y+1][x].objectType() != ObjectType::FakeTreasure) &&
//             (cell[y+1][x].objectType() != ObjectType::Arsenal))
//         {
//             cell[y][x].setMaterialType(MaterialType::Exit);
//             rightRandom = true;
//         }
//     }
//     // right exit
//     rightRandom = false;
//     while (!rightRandom)
//     {
//         int y = (rand() % settings->fieldHeight() + 1) * 2;
//         int x = (settings->fieldWidth() * 2 + 3) - 2;
//         if ((cell[y][x-1].objectType() != ObjectType::RealTreasure) &&
//             (cell[y][x-1].objectType() != ObjectType::FakeTreasure) &&
//             (cell[y][x-1].objectType() != ObjectType::Arsenal))
//         {
//             cell[y][x].setMaterialType(MaterialType::Exit);
//             rightRandom = true;
//         }
//     }
//     // bottom exit
//     rightRandom = false;
//     while (!rightRandom)
//     {
//         int y = (settings->fieldHeight() * 2 + 3) - 2;
//         int x = (rand() % settings->fieldWidth() + 1) * 2;
//         if ((cell[y-1][x].objectType() != ObjectType::RealTreasure) &&
//             (cell[y-1][x].objectType() != ObjectType::FakeTreasure) &&
//             (cell[y-1][x].objectType() != ObjectType::Arsenal))
//         {
//             cell[y][x].setMaterialType(MaterialType::Exit);
//             rightRandom = true;
//         }
//     }
//     // left exit
//     rightRandom = false;
//     while (!rightRandom)
//     {
//         int y = (rand() % settings->fieldHeight() + 1) * 2;
//         int x = 1;
//         if ((cell[y][x+1].objectType() != ObjectType::RealTreasure) &&
//             (cell[y][x+1].objectType() != ObjectType::FakeTreasure) &&
//             (cell[y][x+1].objectType() != ObjectType::Arsenal))
//         {
//             cell[y][x].setMaterialType(MaterialType::Exit);
//             rightRandom = true;
//         }
//     }
// }
//
//
// // определение положения ям
// void Field::setHoles(GameSettings *settings)
// {
//     int holeNum = 0;
//     while (holeNum != 2)
//     {
//         int y = (rand() % settings->fieldHeight() + 1) * 2;
//         int x = (rand() % settings->fieldWidth() + 1) * 2;
//
//         if ((cell[y][x].objectType() != ObjectType::RealTreasure) &&
//             (cell[y][x].objectType() != ObjectType::FakeTreasure) &&
//             (cell[y][x].objectType() != ObjectType::Arsenal) &&
//             (cell[y][x].objectType() != ObjectType::HoleTypeI) &&
//             (cell[y][x].objectType() != ObjectType::HoleTypeII))
//         {
//             holeNum++;
//
//             if (holeNum == 1)
//                 cell[y][x].setObjectType(ObjectType::HoleTypeI);
//             else
//                 cell[y][x].setObjectType(ObjectType::HoleTypeII);
//         }
//     }
//
//     if (settings->holeTypeNum() > 1)
//     {
//         holeNum = 0;
//         while (holeNum != 3)
//         {
//             int y = (rand() % settings->fieldHeight() + 1) * 2;
//             int x = (rand() % settings->fieldWidth() + 1) * 2;
//
//             if ((cell[y][x].objectType() != ObjectType::RealTreasure) &&
//                 (cell[y][x].objectType() != ObjectType::FakeTreasure) &&
//                 (cell[y][x].objectType() != ObjectType::Arsenal) &&
//                 (cell[y][x].objectType() != ObjectType::HoleTypeI) &&
//                 (cell[y][x].objectType() != ObjectType::HoleTypeII) &&
//                 (cell[y][x].objectType() != ObjectType::HoleTypeA) &&
//                 (cell[y][x].objectType() != ObjectType::HoleTypeB) &&
//                 (cell[y][x].objectType() != ObjectType::HoleTypeC))
//             {
//                 holeNum++;
//
//                 if (holeNum == 1)
//                     cell[y][x].setObjectType(ObjectType::HoleTypeA);
//                 else if (holeNum == 2)
//                     cell[y][x].setObjectType(ObjectType::HoleTypeB);
//                 else
//                     cell[y][x].setObjectType(ObjectType::HoleTypeC);
//             }
//         }
//     }
// }
//--------------------------------------------------------------------------------
