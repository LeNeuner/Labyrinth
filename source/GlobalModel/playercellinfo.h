#ifndef PLAYERCELLINFO_H
#define PLAYERCELLINFO_H

#include "globalModel_global.h"

// видимость (открытость) ячейки для игрока
enum class CellState : unsigned int
{
    Opened,
    Closed
};


class GLOBALMODELSHARED_EXPORT PlayerCellInfo
{
public:
    PlayerCellInfo();
    PlayerCellInfo(CellState cState);

//    void setCellTypes(FormType fType, MaterialType mType, ObjectType oType,
//                      ObjectState oState);

//    void setFormType(FormType type);
//    FormType formType();

//    void setMaterialType(MaterialType type);
//    MaterialType materialType();

//    void setObjectType(ObjectType type);
//    ObjectType objectType();

    void setCellState(CellState state);
    CellState cellState();


//    void setBlocked(bool blocked);
//    bool blocked();
//    void setVisited(bool visited);
//    bool visited();

//    int  testVisitedNum = 0;

private:

    CellState     m_cellState;
//    MaterialType m_materialType;
//    ObjectType   m_objectType;
//    ObjectState  m_objectState;

//    bool testAlgBlocked = true;
//    bool testAlgVisited = false;
};

#endif // PLAYERCELLINFO_H
