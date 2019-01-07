#ifndef GLOBALMODEL_H
#define GLOBALMODEL_H

#include <QObject>

#include "globalModel_global.h"
#include "gamesettings.h"
#include "field.h"

class GLOBALMODELSHARED_EXPORT GlobalModel : public QObject
{
    Q_OBJECT
public:
    explicit GlobalModel(QObject *parent = nullptr);

    // сбросить значения в дефолт для всех моделей
    void setDefaults();

    GameSettings    *gameSettModel;
    Field           *fieldModel;

private:
    GameSettings m_gameSettingsModel;
    Field        m_fieldModel;
};

#endif // GLOBALMODEL_H
