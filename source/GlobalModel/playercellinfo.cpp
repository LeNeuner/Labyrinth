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

bool PlayerCellInfo::visible()
{
    return  m_isVisibleCell;
}

void PlayerCellInfo::setClickabilityState(bool isClickable)
{
    m_isClickableCell = isClickable;
}

bool PlayerCellInfo::clickable()
{
    return m_isClickableCell;
}



//void Cell::setCellTypes(FormType fType, MaterialType mType, ObjectType oType, ObjectState oState)
//{
//    m_formType      = fType;
//    m_materialType  = mType;
//    m_objectType    = oType;
//    m_objectState   = oState;
//}

//void Cell::setFormType(FormType type)
//{
//    m_formType = type;
//}
//FormType Cell::formType()
//{
//    return m_formType;
//}

//void Cell::setMaterialType(MaterialType type)
//{
//    m_materialType = type;
//}
//MaterialType Cell::materialType()
//{
//    return m_materialType;
//}

//void Cell::setObjectType(ObjectType type)
//{
//    m_objectType = type;
//}
//ObjectType Cell::objectType()
//{
//    return m_objectType;
//}

//void PlayerCellInfo::setCellVisibilityState(CellVisibilityState state)
//{
//    m_cellVisState = state;
//}
//CellVisibilityState PlayerCellInfo::cellVisibilityState()
//{
//    return m_cellVisState;
//}



//void Cell::setBlocked(bool blocked)
//{
//    testAlgBlocked = blocked;
//}
//bool Cell::blocked()
//{
//    return testAlgBlocked;
//}

//void Cell::setVisited(bool visited)
//{
//    testAlgVisited = visited;
//}
//bool Cell::visited()
//{
//    return testAlgVisited;
//}
