#include "player.h"

Player::Player(int id, const QString &name, QColor color, Position pos)
{
    m_ID            = id;
    m_name          = name;
    m_playerColor   = color;
    m_playerPos     = pos;
}

Player::~Player()
{
}

// установка ID игрока
void Player::setID(int id)
{
    m_ID = id;
}

// получение ID игрока
int Player::ID()
{
    return m_ID;
}

// установка имени игрока
void Player::setName(const QString &name)
{
    m_name = name;
}

// получение имени игрока
QString Player::name()
{
    return m_name;
}

// установка цвета игрока
void Player::setColor(QColor color)
{
    m_playerColor = color;
}

// получение цвета игрока
QColor Player::color()
{
    return m_playerColor;
}
