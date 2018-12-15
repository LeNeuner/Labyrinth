#include "cell.h"
#include <QDebug>
Cell::Cell()
{
}

Cell::Cell(FormType fType, MaterialType mType, ObjectType oType, ObjectState oState)
{
    m_formType      = fType;
    m_materialType  = mType;
    m_objectType    = oType;
    m_objectState   = oState;
}

void Cell::setCellTypes(FormType fType, MaterialType mType, ObjectType oType, ObjectState oState)
{
    m_formType      = fType;
    m_materialType  = mType;
    m_objectType    = oType;
    m_objectState   = oState;
}

void Cell::setFormType(FormType type)
{
    m_formType = type;
}
FormType Cell::formType() const
{
    return m_formType;
}

void Cell::setMaterialType(MaterialType type)
{
    m_materialType = type;
}
MaterialType Cell::materialType() const
{
    return m_materialType;
}

void Cell::setObjectType(ObjectType type)
{
    m_objectType = type;
}
ObjectType Cell::objectType() const
{
    return m_objectType;
}

void Cell::setObjectState(ObjectState state)
{
    m_objectState = state;
}
ObjectState Cell::objectState() const
{
    return m_objectState;
}

void Cell::setVisibilityState(bool isVisible)
{
    m_isVisibleCell = isVisible;
}

bool Cell::visible() const
{
    return  m_isVisibleCell;
}

void Cell::setClickabilityState(bool isClickable)
{
    m_isClickableCell = isClickable;
}

bool Cell::clickable() const
{
    return m_isClickableCell;
}


void Cell::cellClicked(int x, int y)
{
    qDebug() << "Eprst: " << x << y;
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



