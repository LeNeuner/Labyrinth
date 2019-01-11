#include "players.h"

#include "constlist.h"

Players::Players(QObject *parent) : QObject(parent)
{
}

void Players::setDefaults()
{
    players.clear();
}

void Players::createPlayers(GameSettings *settings)
{
    for (int i = 0; i < settings->personNum()+1; ++i)           // delete +1 person after all test
    {       
        // set players info about field
        Player currPlayer(i);
        int yNum = settings->fieldFullHeight();
        int xNum = settings->fieldFullWidth();

        // close all cells
        for (int y = 0; y < yNum; ++y)
        {
            for (int x = 0; x < xNum; ++x)
            {
                currPlayer.pcell[y][x].setVisibilityState(false);
                currPlayer.pcell[y][x].setClickabilityState(false);
            }
        }

        // NEED ADD VECTOR PUSH_BACK
        // то что ниже допилить

        // открытие всех колон
        for (int y = 1; y < yNum-1; y+=2)
        {
            for (int x = 1; x < xNum-1; x+=2)
            {
                cell[y][x].setVisibilityState(true);
            }
        }

        // открытие клеток доступных для клика игрока
         for (int y = 2; y < yNum-2; y += 2)
         {
             for (int x = 2; x < xNum-2; x += 2)
             {
                 cell[y][x].setClickabilityState(true);
             }
         }


        //...
        //fieldInfo.push_back();
    }
}
