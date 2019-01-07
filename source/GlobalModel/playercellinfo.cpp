#include "playercellinfo.h"

PlayerCellInfo::PlayerCellInfo()
{
}

PlayerCellInfo::PlayerCellInfo(bool isVisible, bool isClickable)
{
    m_isVisibleCell     = isVisible;
    m_isClickableCell   = isClickable;
}

void PlayerCellInfo::setVisibilityState(bool isVisible)
{
    m_isVisibleCell = isVisible;
}

bool PlayerCellInfo::visible() const
{
    return  m_isVisibleCell;
}

void PlayerCellInfo::setClickabilityState(bool isClickable)
{
    m_isClickableCell = isClickable;
}

bool PlayerCellInfo::clickable() const
{
    return m_isClickableCell;
}
