/*!
\file
\brief Заголовочный файл, содержащий класс Player -
класс игрока, хранящий основную информмацию о Игроке:
имя, цвет, позицию на поле, инвентарь и т.п.
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "position.h"

// состояние игрока
enum class PlayerState : unsigned int
{
    Healthy,
    Injured,
    Died
};
// контроль над игроком
enum class PlayerControl : unsigned int
{
    Human,
    PC
};

class Player
{
public:
    Player();

    void setID(int id);
    int ID();

private:
    int             m_ID    = -1;
    const QString   m_name  = QString("Player");
    PlayerState     m_playerState;
    PlayerControl   m_playerControl;
//    Position currPos();
};

#endif // PLAYER_H
