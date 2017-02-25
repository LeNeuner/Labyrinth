#ifndef CELL_H
#define CELL_H

#include "globalModel_global.h"

// состояние объекта
enum class ObjectState : unsigned int
{
    None,
    Whole,
    Looted
};

// тип ямы
enum class HoleType : unsigned int
{
    None,
    TypeA,
    TypeB,
    TypeC,
    TypeI,
    TypeII
};

// тип формы ячейки
enum class FormType : unsigned int
{
    Gorizontal,
    Vertical,
    Pillar,
    Square
};

// тип материала
enum class MaterialType : unsigned int
{
    None,
    Field,
    Grass,
    Wall,
    Concrete,
    WallDest,
    Exit
};

// тип объекта
enum class ObjectType : unsigned int
{
    None,
    RealTreasure,
    FakeTreasure,
    Arsenal,
    Hole
};



class GLOBALMODELSHARED_EXPORT Cell
{
public:
    Cell();
    Cell(FormType fType, MaterialType mType, ObjectType oType,
         ObjectState oState, HoleType hType);

    void setCellTypes(FormType fType, MaterialType mType, ObjectType oType,
                      ObjectState oState, HoleType hType);

    void setFormType(FormType type);
    FormType formType();

    void setMaterialType(MaterialType type);
    MaterialType materialType();

    void setObjectType(ObjectType type);
    ObjectType objectType();

    void setObjectState(ObjectState state);
    ObjectState objectState();

    void setHoleType(HoleType type);
    HoleType holeType();

    void setBlocked(bool blocked);
    bool blocked();
    void setVisited(bool visited);
    bool visited();

    int  testVisitedNum = 0;

private:

    FormType     m_formType;
    MaterialType m_materialType;
    ObjectType   m_objectType;
    ObjectState  m_objectState;
    HoleType     m_holeType;

    bool testAlgBlocked = true;
    bool testAlgVisited = false;
};

#endif // CELL_H
