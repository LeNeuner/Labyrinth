#ifndef ENGINEMANAGER_H
#define ENGINEMANAGER_H

#include <QObject>

#include "enginemodule_global.h"
#include "globalmodel.h"


class ENGINEMODULESHARED_EXPORT EngineManager : public QObject
{
    Q_OBJECT
public:
    explicit EngineManager(QObject *parent = 0);
    ~EngineManager();

    // установка модели настроек
    void setGlobalModel(GlobalModel* model){
        glModel = model;
    }

    // инициализация новой игры
    bool newGameInitialization();

private:
    GlobalModel         *glModel = nullptr;
};

#endif // ENGINEMANAGER_H
