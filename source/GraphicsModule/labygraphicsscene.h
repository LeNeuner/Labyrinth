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

class GRAPHICSMODULESHARED_EXPORT LabyGraphicsScene : public QGraphicsScene
{
public:
    LabyGraphicsScene(GlobalModel* model);
    ~LabyGraphicsScene();

    QGraphicsScene *graphScene();

    QGraphicsScene *updateScene(GlobalModel* model);

private:
    QGraphicsScene          *scene   = nullptr;
    QGraphicsGridLayout     *grid    = nullptr;
    PixmapKeeper            *pixmaps = nullptr;
};

#endif // LABYGRAPHICSSCENE_H
