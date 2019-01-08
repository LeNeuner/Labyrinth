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
    for (int i = 0; i < settings->personNum(); ++i)
    {
        Player currPlayer;
        //...
        //fieldInfo.push_back();
    }
}
