#ifndef GLOBALMODEL_H
#define GLOBALMODEL_H

#include <QObject>

#include "globalModel_global.h"
#include "field.h"
#include "gamesettings.h"

class GLOBALMODELSHARED_EXPORT GlobalModel : public QObject
{
    Q_OBJECT
public:
    explicit GlobalModel(QObject *parent = 0);

    // сбросить значения в дефолт для всех моделей
    void setDefaults();

    Field*          fieldModel;
    GameSettings*   gameSettModel;
//    ComMessageKeeper*   messageModel;
//    HotkeyKeeper*       hotkeysModel;
};

#endif // GLOBALMODEL_H
