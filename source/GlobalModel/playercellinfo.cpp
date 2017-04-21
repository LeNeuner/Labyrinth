#include "playercellinfo.h"

PlayerCellInfo::PlayerCellInfo()
{
    m_cellState = CellState::Closed;
}

PlayerCellInfo::PlayerCellInfo(CellState cState)
{
    m_cellState     = cState;
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

void PlayerCellInfo::setCellState(CellState state)
{
    m_cellState = state;
}
CellState PlayerCellInfo::cellState()
{
    return m_cellState;
}



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
