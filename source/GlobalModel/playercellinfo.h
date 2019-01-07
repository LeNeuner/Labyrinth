#ifndef PLAYERCELLINFO_H
#define PLAYERCELLINFO_H

#include "globalModel_global.h"


class GLOBALMODELSHARED_EXPORT PlayerCellInfo
{
public:
    PlayerCellInfo();
    PlayerCellInfo(bool isVisible, bool isClickable);

    void setVisibilityState(bool isVisible);
    bool visible() const;
    void setClickabilityState(bool isClickable);
    bool clickable() const;

private:
    bool m_isVisibleCell    = false;
    bool m_isClickableCell  = false;
};

#endif // PLAYERCELLINFO_H
