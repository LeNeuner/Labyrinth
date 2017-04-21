/*!
\file
\brief Заголовочный файл, содержащий класс Player -
класс игрока, хранящий основную информмацию о Игроке:
имя, цвет, позицию на поле, инвентарь и т.п.
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QColor>
#include "position.h"
#include "playerfieldinfo.h"

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
    Player(int id, const QString &name, QColor color, Position pos);
    ~Player();

    // установка/получение ID
    void setID(int id);
    int ID();

private:
    int             m_ID            = -1;
    const QString   m_name          = QString("Player");
    QColor          m_playerColor   = Qt::black;
    PlayerState     m_playerState   = PlayerState::Healthy;
    PlayerControl   m_playerControl = PlayerControl::Human;
    Position        m_playerPos;
    PlayerFieldInfo *m_playerField;
//    Position currPos();
};

#endif // PLAYER_H
