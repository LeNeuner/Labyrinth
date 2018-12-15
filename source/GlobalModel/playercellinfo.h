#ifndef PLAYERCELLINFO_H
#define PLAYERCELLINFO_H

#include "globalModel_global.h"

//// видимость (открытость) ячейки для игрока
//enum class VisibilityState : unsigned int
//{
//    Opened,
//    Closed
//};

//// доступность ячейки для выбора
//enum class ClickabilityState : unsigned int
//{
//    Allowed,
//    Prohibited
//};

class GLOBALMODELSHARED_EXPORT PlayerCellInfo
{
public:
    PlayerCellInfo();
    PlayerCellInfo(bool isVisible, bool isClickable);

//    void setCellTypes(FormType fType, MaterialType mType, ObjectType oType,
//                      ObjectState oState);

//    void setFormType(FormType type);
//    FormType formType();

//    void setMaterialType(MaterialType type);
//    MaterialType materialType();

//    void setObjectType(ObjectType type);
//    ObjectType objectType();

//    void setCellVisibilityState(VisibilityState state);
//    VisibilityState cellVisibilityState();


    void setVisibilityState(bool isVisible);
    bool visible();
    void setClickabilityState(bool isClickable);
    bool clickable();

private:

//    VisibilityState     m_cellVisState;

    bool m_isVisibleCell    = false;
    bool m_isClickableCell  = false;
//    MaterialType m_materialType;
//    ObjectType   m_objectType;
//    ObjectState  m_objectState;

//    bool testAlgBlocked = true;
//    bool testAlgVisited = false;
};

#endif // PLAYERCELLINFO_H
