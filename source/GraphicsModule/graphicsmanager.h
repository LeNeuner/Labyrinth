#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <QObject>

#include "graphicsmodule_global.h"
#include "globalmodel.h"
#include "labygraphicsscene.h"


class GRAPHICSMODULESHARED_EXPORT GraphicsManager : public QObject
{
    Q_OBJECT
public:
    explicit GraphicsManager(QObject *parent = 0);
    ~GraphicsManager();

    // установка модели настроек
    void setGlobalModel(GlobalModel* model){
        glModel = model;
    }
    // построение графической сцены
    QGraphicsScene* createGraphicsScene();
    // обновление сцены
    QGraphicsScene *updateGraphicsScene();

private:
    GlobalModel         *glModel = nullptr;
    LabyGraphicsScene   *lGraphicsScene;
};

#endif // GRAPHICSMANAGER_H
