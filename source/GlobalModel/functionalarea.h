#ifndef FUNCTIONALAREA_H
#define FUNCTIONALAREA_H

//#include "cell.h"

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
    Wall,
    Wall_dest,
    Concrete,
    Concrete_exit
};

class FunctionalArea /*: public Cell*/
{
public:
    FunctionalArea();
    FunctionalArea(FormType formTtype, MaterialType matType);

    void setFormType(FormType type);
    FormType formType();

    void setMaterialType(MaterialType type);
    MaterialType materialType();

    void draw();

private:
    FormType     fType = FormType::Square;
    MaterialType mType = MaterialType::None;
};

#endif // FUNCTIONALAREA_H
