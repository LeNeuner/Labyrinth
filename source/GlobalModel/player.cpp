#include "player.h"

Player::Player(int id, const QString &name, QColor color, Position pos)
{
    m_ID            = id;
//    m_name          = name;
    m_playerColor   = color;

    m_playerPos     = pos;
}

Player::~Player()
{

}

// установка ID игрока
void Player::setID(int id)
{

}

// получение ID игрока
int Player::ID()
{
    return 0;
}
