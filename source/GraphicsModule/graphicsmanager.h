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
    explicit GraphicsManager(QObject *parent = nullptr);
    ~GraphicsManager();

    // установка модели настроек
    void setGlobalModel(GlobalModel* model){
        glModel = model;
    }
    // построение графической сцены
    QGraphicsScene *createGraphicsScene();
    // обновление сцены
    QGraphicsScene *updateGraphicsScene();

    // построение и обновление графической сцены поля игрока
    QGraphicsScene *createPlayerGraphicsScene();
    QGraphicsScene *updatePlayerGraphicsScene();

private:
    GlobalModel         *glModel                = nullptr;
    LabyGraphicsScene   *lGraphicsScene         = nullptr;
    LabyGraphicsScene   *lGraphicsPlayerScene   = nullptr;
};

#endif // GRAPHICSMANAGER_H
