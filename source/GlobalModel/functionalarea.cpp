#include "functionalarea.h"

FunctionalArea::FunctionalArea()
{
}

FunctionalArea::FunctionalArea(FormType formTtype, MaterialType matType)
{
    fType = formTtype;
    mType = matType;

//    this->setType(CellType::ConcreteGorizontal);
}

void FunctionalArea::setFormType(FormType type)
{
    fType = type;
}

FormType FunctionalArea::formType()
{
    return fType;
}

void FunctionalArea::setMaterialType(MaterialType type)
{
    mType = type;
}

MaterialType FunctionalArea::materialType()
{
    return mType;
}

void FunctionalArea::draw()
{
    // do something
}

