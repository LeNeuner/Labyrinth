#include "cell.h"

Cell::Cell()
{
}

Cell::Cell(FormType fType, MaterialType mType, ObjectType oType, ObjectState oState, HoleType hType)
{
    m_formType      = fType;
    m_materialType  = mType;
    m_objectType    = oType;
    m_objectState   = oState;
    m_holeType      = hType;
}

void Cell::setCellTypes(FormType fType, MaterialType mType, ObjectType oType, ObjectState oState, HoleType hType)
{
    m_formType      = fType;
    m_materialType  = mType;
    m_objectType    = oType;
    m_objectState   = oState;
    m_holeType      = hType;
}

void Cell::setFormType(FormType type)
{
    m_formType = type;
}
FormType Cell::formType()
{
    return m_formType;
}

void Cell::setMaterialType(MaterialType type)
{
    m_materialType = type;
}
MaterialType Cell::materialType()
{
    return m_materialType;
}

void Cell::setObjectType(ObjectType type)
{
    m_objectType = type;
}
ObjectType Cell::objectType()
{
    return m_objectType;
}

void Cell::setObjectState(ObjectState state)
{
    m_objectState = state;
}
ObjectState Cell::objectState()
{
    return m_objectState;
}

void Cell::setHoleType(HoleType type)
{
    m_holeType = type;
}
HoleType Cell::holeType()
{
    return m_holeType;
}

void Cell::setBlocked(bool blocked)
{
    testAlgBlocked = blocked;
}
bool Cell::blocked()
{
    return testAlgBlocked;
}

void Cell::setVisited(bool visited)
{
    testAlgVisited = visited;
}
bool Cell::visited()
{
    return testAlgVisited;
}



