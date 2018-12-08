#ifndef GLOBALMODEL_H
#define GLOBALMODEL_H

#include <QObject>

#include "globalModel_global.h"
#include "field.h"
#include "playerfieldinfo.h"
#include "gamesettings.h"

class GLOBALMODELSHARED_EXPORT GlobalModel : public QObject
{
    Q_OBJECT
public:
    explicit GlobalModel(QObject *parent = nullptr);

    // сбросить значения в дефолт для всех моделей
    void setDefaults();

    Field               *fieldModel;
    PlayerFieldInfo     *playerFieldModel;
    GameSettings        *gameSettModel;
};

#endif // GLOBALMODEL_H
