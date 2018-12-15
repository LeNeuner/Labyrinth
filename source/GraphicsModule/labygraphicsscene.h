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

    QGraphicsScene *updatePlayerScene(GlobalModel* model);

private:
    QGraphicsScene          *m_scene   = nullptr;
    QGraphicsGridLayout     *m_grid    = nullptr;
    PixmapKeeper            *m_pixmaps = nullptr;

    void    clearScene(GlobalModel* model);
    QSizeF  getCellSize(const Cell &cell);
    double  getOpacity(const Cell &cell);

    QPixmap *getRealPixmap(const Cell &cell);
    QPixmap *getPlayersPixmap(const Cell &cell);
};

#endif // LABYGRAPHICSSCENE_H
