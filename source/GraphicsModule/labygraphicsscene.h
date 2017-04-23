#ifndef LABYGRAPHICSSCENE_H
#define LABYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsRectItem>
#include <QGraphicsGridLayout>
#include <QGraphicsLinearLayout>

#include "graphicsmodule_global.h"
#include "globalmodel.h"
#include "basicrect.h"
#include "pixmapkeeper.h"

class GRAPHICSMODULESHARED_EXPORT LabyGraphicsScene : /*public QObject,*/ public QGraphicsScene
{
//    Q_OBJECT
public:
    LabyGraphicsScene(GlobalModel* model);
    ~LabyGraphicsScene();

    QGraphicsScene *graphScene();

    QGraphicsScene *updateScene(GlobalModel* model);

    QGraphicsScene *updatePlayerScene(GlobalModel* model);

signals:
    void HZ();

private:
    QGraphicsScene          *scene   = nullptr;
    QGraphicsGridLayout     *grid    = nullptr;
    PixmapKeeper            *pixmaps = nullptr;
};

#endif // LABYGRAPHICSSCENE_H
