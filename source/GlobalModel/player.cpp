#include "player.h"

Player::Player(int id) :
    m_ID(id)
{
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
