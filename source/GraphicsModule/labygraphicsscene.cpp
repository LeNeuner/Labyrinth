#include "labygraphicsscene.h"
#include <QPainter>

#include <QDebug>

LabyGraphicsScene::LabyGraphicsScene(GlobalModel* model) /*: QObject(), QGraphicsScene()*/
{
    int big   = DEFAULT_BIG_PICTURE_SIZE;
    int small = DEFAULT_SMALL_PICTURE_SIZE;

    m_pixmaps = new PixmapKeeper(big, small);
    m_scene   = new QGraphicsScene(this);

//    QPixmap *bGrass  = new QPixmap(QLatin1String(":resources/images/bigGrass.jpg"));
//    QPixmap bigGrass = bGrass->scaled(1000, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
//    m_scene->setBackgroundBrush(Qt::green);

    BasicRect *item = new BasicRect(m_pixmaps->none(), QSizeF(small, small));

    QGraphicsLinearLayout *windowLayout = new QGraphicsLinearLayout(Qt::Vertical);
    m_grid = new QGraphicsGridLayout(windowLayout);
    m_grid->setVerticalSpacing(0);
    m_grid->setHorizontalSpacing(0);

    if (model == nullptr)
        qDebug() << "nullptr";

    QSizeF  cellSize;
    QPixmap *currPixmap = m_pixmaps->none();
    for (int y = 0; y < model->fieldModel->getFullHeight(); y++)
    {
        for (int x = 0; x < model->fieldModel->getFullWidth(); x++)
        {
            if (model->fieldModel->cell[y][x].formType() == FormType::Square)
                cellSize = QSizeF(big, big);
            else if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                cellSize = QSizeF(small, big);
            else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                cellSize = QSizeF(big, small);
            else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                cellSize = QSizeF(small, small);

            currPixmap = m_pixmaps->grass();


//            if (model->fieldModel->cell[y][x].materialType() == MaterialType::None)
//            {
//                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
//                    currPixmap = m_pixmaps->field_ver();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
//                    currPixmap = m_pixmaps->field_gor();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
//                    currPixmap = m_pixmaps->field_pillar();
//                else
//                    currPixmap = m_pixmaps->field();
//            }
//            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Field)
//                currPixmap = m_pixmaps->flour();
//            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Grass)
//                currPixmap = m_pixmaps->grass();
//            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Wall)
//            {
//                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
//                    currPixmap = m_pixmaps->wall_ver();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
//                    currPixmap = m_pixmaps->wall_gor();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
//                    currPixmap = m_pixmaps->wall_pillar();
//            }
//            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Concrete)
//            {
//                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
//                    currPixmap = m_pixmaps->concrete_ver();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
//                    currPixmap = m_pixmaps->concrete_gor();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
//                    currPixmap = m_pixmaps->concrete_pillar();
//            }


            item = new BasicRect(currPixmap, cellSize);
            m_grid->addItem(item, y, x);
        }
    }

    windowLayout->addItem(m_grid);
    QGraphicsWidget* gWidget = new QGraphicsWidget();
    gWidget->setLayout(windowLayout);

    // заплатка от бага (съезжает поле)
    m_scene->addItem(gWidget);
    m_scene->update();
}

LabyGraphicsScene::~LabyGraphicsScene()
{
    delete m_pixmaps;
    delete m_grid;
    delete m_scene;
}

QGraphicsScene* LabyGraphicsScene::graphScene()
{
    return m_scene;
}

QGraphicsScene *LabyGraphicsScene::updateScene(GlobalModel* model)
{
    //--------------------------------------------------
    // установка поля
    QPixmap *bGrass  = new QPixmap(QLatin1String(":resources/images/bigGrass.jpg"));
    QPixmap bigGrass = bGrass->scaled(m_scene->width()+200, m_scene->height()+100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    m_scene->setBackgroundBrush(bigGrass);

    //--------------------------------------------------
    // отрисовка в соответствии с новой моделью
    int big   = DEFAULT_BIG_PICTURE_SIZE;
    int small = DEFAULT_SMALL_PICTURE_SIZE;


    //--------------------------------------------------
    // очистка сцены
    for (int y = 0; y < model->fieldModel->getFullHeight(); y++)
    {
        for (int x = 0; x < model->fieldModel->getFullWidth(); x++)
        {
            m_grid->removeItem(m_grid->itemAt(y,x));
        }
    }
    delete m_grid;
    m_scene->clear();

    // TEST
    for (int y = 0; y < model->fieldModel->getFullHeight(); y++)
    {
        for (int x = 0; x < model->fieldModel->getFullWidth(); x++)
        {
           if (model->fieldModel->cell[y][x].objectType() == ObjectType::Arsenal)
               model->fieldModel->cell[y][x].testVisitedNum = 0;
        }
    }

    //--------------------------------------------------
    // отрисовка новой сцены
    QGraphicsLinearLayout *windowLayout = new QGraphicsLinearLayout(Qt::Vertical);
    m_grid = new QGraphicsGridLayout(windowLayout);
    m_grid->setVerticalSpacing(0);
    m_grid->setHorizontalSpacing(0);

    QSizeF  cellSize;
    QPixmap *currPixmap = m_pixmaps->none();
    double  currOpacity = 1.0;
    BasicRect *item = new BasicRect(m_pixmaps->none(), QSizeF(small, small));
    // ссылка на предыдущее поле
    BasicRect *lastItem = nullptr;
    for (int y = 0; y < model->fieldModel->getFullHeight(); y++)
    {
        for (int x = 0; x < model->fieldModel->getFullWidth(); x++)
        {
            QPixmap *testPixmap = nullptr;
            QString text = "";

            // форма поля
            if (model->fieldModel->cell[y][x].formType() == FormType::Square)
                cellSize = QSizeF(big, big);
            else if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                cellSize = QSizeF(small, big);
            else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                cellSize = QSizeF(big, small);
            else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                cellSize = QSizeF(small, small);

            // материал поля
            if (model->fieldModel->cell[y][x].materialType() == MaterialType::None)
            {
                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                    currPixmap = m_pixmaps->none_ver();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                    currPixmap = m_pixmaps->none_gor();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                    currPixmap = m_pixmaps->none_pillar();
                else
                    currPixmap = m_pixmaps->none();
            }
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Flour)
            {
                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                    currPixmap = m_pixmaps->flour_ver();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                    currPixmap = m_pixmaps->flour_gor();
                else
                    currPixmap = m_pixmaps->flour();
            }
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Grass)
            {
                    currPixmap = m_pixmaps->grass();
            }
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Wall)
            {
                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                    currPixmap = m_pixmaps->wall_ver();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                    currPixmap = m_pixmaps->wall_gor();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                    currPixmap = m_pixmaps->wall_pillar();
            }
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Concrete)
            {
                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                    currPixmap = m_pixmaps->concrete_ver();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                    currPixmap = m_pixmaps->concrete_gor();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                    currPixmap = m_pixmaps->concrete_pillar();
            }
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Exit)
            {
                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                    currPixmap = m_pixmaps->flour_ver();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                    currPixmap = m_pixmaps->flour_gor();
                else
                    currPixmap = m_pixmaps->flour();
            }
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::PathRight)
                currPixmap = m_pixmaps->path_right();
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::PathLeft)
                currPixmap = m_pixmaps->path_left();
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::PathUp)
                currPixmap = m_pixmaps->path_up();
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::PathBottom)
                currPixmap = m_pixmaps->path_bottom();
            else
                currPixmap = m_pixmaps->grass();


            // тип объекта в поле
            if ((model->fieldModel->cell[y][x].objectType() == ObjectType::RealTreasure) ||
                (model->fieldModel->cell[y][x].objectType() == ObjectType::FakeTreasure))
                currPixmap = m_pixmaps->treasure();
            else if (model->fieldModel->cell[y][x].objectType() == ObjectType::Arsenal)
                currPixmap = m_pixmaps->arsenal();
            else if ((model->fieldModel->cell[y][x].objectType() == ObjectType::HoleTypeI) ||
                (model->fieldModel->cell[y][x].objectType() == ObjectType::HoleTypeII))
            {
                currPixmap = m_pixmaps->hole_closed();
//                text = "I-II";
            }
            else if ((model->fieldModel->cell[y][x].objectType() == ObjectType::HoleTypeA) ||
                (model->fieldModel->cell[y][x].objectType() == ObjectType::HoleTypeB) ||
                (model->fieldModel->cell[y][x].objectType() == ObjectType::HoleTypeC))
            {
                currPixmap = m_pixmaps->hole_closed();
//                text = "ABC";
            }


//            if ((model->fieldModel->cell[y][x].testVisitedNum != 0) &&
//                (model->fieldModel->cell[y][x].formType() == FormType::Square) &&
//                (model->fieldModel->cell[y][x].objectType() != ObjectType::Arsenal))
//            {
//                text = QString::number(model->fieldModel->cell[y][x].testVisitedNum);
//            }


            item = new BasicRect(currPixmap, cellSize, currOpacity, text);
            m_grid->addItem(item, y, x);


            if (testPixmap != nullptr)
            {
                item = new BasicRect(testPixmap, cellSize, currOpacity, text);
                m_grid->addItem(item, y, x);
            }

            connect(item, &BasicRect::mousePressed,
                    [this, x, y, item, lastItem]()mutable ->void
                    {
                        if ((x%2 == 0) && (y%2 == 0) && (x>=2) && (x<=20) && (y>=2) && (y<=20))
                        {
//                            qDebug() << "X:  " << x << " Y : " << y;
                            qDebug() << "RX: " << x/2 << " RY: " << y/2;
                            item->addPlayer(Qt::red);

//                            if (item != lastItem)
//                            {
//                                if (lastItem)
//                                    lastItem->delPlayer();

//                                lastItem = item;
//                            }
                        }
                    });
        }
    }

    windowLayout->addItem(m_grid);
    QGraphicsWidget* gWidget = new QGraphicsWidget();
    gWidget->setLayout(windowLayout);
    m_scene->addItem(gWidget);
    m_scene->update();

    return m_scene;
}

// обновить графическую сцену игрока
QGraphicsScene *LabyGraphicsScene::updatePlayerScene(GlobalModel *model)
{
    //--------------------------------------------------
    // set background field (need update)
    int scnW = static_cast<int>(m_scene->width());
    int scnH = static_cast<int>(m_scene->height());
    QPixmap *bGrass  = new QPixmap(QLatin1String(":resources/images/bigGrass.jpg"));
    QPixmap bigGrass = bGrass->scaled(scnW+200, scnH-100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    m_scene->setBackgroundBrush(/*bigGrass*/Qt::white);

    //--------------------------------------------------
    //  to clear scene
    clearScene(model);

    //--------------------------------------------------
    // create grid for new scene
    QGraphicsLinearLayout *windowLayout = new QGraphicsLinearLayout(Qt::Vertical);
    m_grid = new QGraphicsGridLayout(windowLayout);
    m_grid->setVerticalSpacing(0);
    m_grid->setHorizontalSpacing(0);

    // create default item
    int small = DEFAULT_SMALL_PICTURE_SIZE;
    BasicRect *item = new BasicRect(m_pixmaps->none(), QSizeF(small, small));

    // draw field
    for (int y = 0; y < model->fieldModel->getFullHeight(); y++)
    {
        for (int x = 0; x < model->fieldModel->getFullWidth(); x++)
        {
            // set size for cells
            QSizeF currCellSize = getCellSize(model->fieldModel->cell[y][x]);

            // set opacity for cells
            double currOpacity  = getOpacity(model->playerFieldModel->cell[y][x]);

            // draw open and closed cells
            QPixmap *currPixmap = m_pixmaps->none();
            if (model->playerFieldModel->cell[y][x].visible())
                currPixmap = getRealPixmap(model->fieldModel->cell[y][x]);
            else
                currPixmap = getPlayersPixmap(model->fieldModel->cell[y][x]);

            // create final item
            QString text = "";
            item = new BasicRect(currPixmap, currCellSize, currOpacity, text);
            m_grid->addItem(item, y, x);

            // connect item with model
            connect(item, &BasicRect::mousePressed,
                    [x, y, model]()mutable->void
                    {
                        model->fieldModel->openCell(x,y);
                        model->playerFieldModel->openCell(x,y);
//                        model->fieldModel->cell[y][x].cellClicked(x, y);
//                        model->playerFieldModel->cell[y][x].cellClicked(x, y);
                    });
        }
    }

    // add grid to scene
    windowLayout->addItem(m_grid);
    QGraphicsWidget* gWidget = new QGraphicsWidget();
    gWidget->setLayout(windowLayout);
    m_scene->addItem(gWidget);
    m_scene->update();

    return m_scene;
}

/// to clear csene
void LabyGraphicsScene::clearScene(GlobalModel *model)
{
    if (m_grid != nullptr)
    {
        for (int y = 0; y < model->fieldModel->getFullHeight(); y++)
        {
            for (int x = 0; x < model->fieldModel->getFullWidth(); x++)
            {
                m_grid->removeItem(m_grid->itemAt(y,x));
            }
        }
        delete m_grid;
        m_scene->clear();
    }
}

/// get current cell size
QSizeF LabyGraphicsScene::getCellSize(const Cell &cell)
{
    // cells graphic size
    int big   = DEFAULT_BIG_PICTURE_SIZE;
    int small = DEFAULT_SMALL_PICTURE_SIZE;

    QSizeF cellSize;
    if (cell.formType() == FormType::Square)
        cellSize = QSizeF(big, big);
    else if (cell.formType() == FormType::Vertical)
        cellSize = QSizeF(small, big);
    else if (cell.formType() == FormType::Gorizontal)
        cellSize = QSizeF(big, small);
    else if (cell.formType() == FormType::Pillar)
        cellSize = QSizeF(small, small);
    else
    {
        cellSize = QSizeF();
        qWarning() << "Incorrect cell size";
    }
    return cellSize;
}

/// get current cell opacity
double LabyGraphicsScene::getOpacity(const Cell &cell)
{
    double opacity;
    if (cell.visible())
        opacity = 1.0;
    else
        opacity = DEFAULT_CLOSED_CELL_OPACITY;
    return opacity;
}

/// get real field pixmap
QPixmap *LabyGraphicsScene::getRealPixmap(const Cell &cell)
{
    QPixmap* currPixmap;
    if (cell.materialType() == MaterialType::Grass)
        currPixmap = m_pixmaps->grass();
    else if (cell.materialType() == MaterialType::None)
    {
        if (cell.formType() == FormType::Vertical)
            currPixmap = m_pixmaps->flour_ver();
        else if (cell.formType() == FormType::Gorizontal)
            currPixmap = m_pixmaps->flour_gor();
        else
            currPixmap = m_pixmaps->flour();
    }
    else if (cell.materialType() == MaterialType::Wall)
    {
        if (cell.formType() == FormType::Vertical)
            currPixmap = m_pixmaps->wall_ver();
        else if (cell.formType() == FormType::Gorizontal)
            currPixmap = m_pixmaps->wall_gor();
        else if (cell.formType() == FormType::Pillar)
            currPixmap = m_pixmaps->wall_pillar();
        else
            currPixmap = m_pixmaps->none();
    }
    else if (cell.materialType() == MaterialType::Concrete)
    {
        if (cell.formType() == FormType::Vertical)
            currPixmap = m_pixmaps->concrete_ver();
        else if (cell.formType() == FormType::Gorizontal)
            currPixmap = m_pixmaps->concrete_gor();
        else if (cell.formType() == FormType::Pillar)
            currPixmap = m_pixmaps->concrete_pillar();
        else
            currPixmap = m_pixmaps->none();
    }
    else if (cell.materialType() == MaterialType::Exit)
    {
        if (cell.formType() == FormType::Vertical)
            currPixmap = m_pixmaps->flour_ver();
        else if (cell.formType() == FormType::Gorizontal)
            currPixmap = m_pixmaps->flour_gor();
        else
            currPixmap = m_pixmaps->flour();
    }
    else if (cell.materialType() == MaterialType::Flour)
    {
        if (cell.formType() == FormType::Vertical)
            currPixmap = m_pixmaps->flour_ver();
        else if (cell.formType() == FormType::Gorizontal)
            currPixmap = m_pixmaps->flour_gor();
        else
            currPixmap = m_pixmaps->flour();
    }
    else if (cell.materialType() == MaterialType::PathRight)
        currPixmap = m_pixmaps->path_right();
    else if (cell.materialType() == MaterialType::PathLeft)
        currPixmap = m_pixmaps->path_left();
    else if (cell.materialType() == MaterialType::PathUp)
        currPixmap = m_pixmaps->path_up();
    else if (cell.materialType() == MaterialType::PathBottom)
        currPixmap = m_pixmaps->path_bottom();
    else
        currPixmap = m_pixmaps->grass();

    // add objects
    // тип объекта в поле
    if ((cell.objectType() == ObjectType::RealTreasure) ||
        (cell.objectType() == ObjectType::FakeTreasure))
        currPixmap = m_pixmaps->treasure();
    else if (cell.objectType() == ObjectType::Arsenal)
        currPixmap = m_pixmaps->arsenal();
    else if ((cell.objectType() == ObjectType::HoleTypeI) ||
             (cell.objectType() == ObjectType::HoleTypeII))
    {
        currPixmap = m_pixmaps->hole_closed();
    }
    else if ((cell.objectType() == ObjectType::HoleTypeA) ||
             (cell.objectType() == ObjectType::HoleTypeB) ||
             (cell.objectType() == ObjectType::HoleTypeC))
    {
        currPixmap = m_pixmaps->hole_closed();
    }
    return currPixmap;
}

/// get players variant of field pixmap
QPixmap *LabyGraphicsScene::getPlayersPixmap(const Cell &cell)
{
    QPixmap *currPixmap;
    if (cell.materialType() == MaterialType::Grass)
        currPixmap = m_pixmaps->grass();
    else if (cell.materialType() == MaterialType::Concrete)
    {
        if (cell.formType() == FormType::Vertical)
            currPixmap = m_pixmaps->concrete_ver();
        else if (cell.formType() == FormType::Gorizontal)
            currPixmap = m_pixmaps->concrete_gor();
        else if (cell.formType() == FormType::Pillar)
            currPixmap = m_pixmaps->concrete_pillar();
        else
            currPixmap = m_pixmaps->none();
    }
    else if (cell.materialType() == MaterialType::Exit)
    {
        if (cell.formType() == FormType::Vertical)
            currPixmap = m_pixmaps->concrete_ver();
        else if (cell.formType() == FormType::Gorizontal)
            currPixmap = m_pixmaps->concrete_gor();
        else
            currPixmap = m_pixmaps->none();
    }
    else if ((cell.materialType() == MaterialType::Flour) ||
             (cell.materialType() == MaterialType::Wall))
    {
        if (cell.formType() == FormType::Vertical)
            currPixmap = m_pixmaps->flour_ver();
        else if (cell.formType() == FormType::Gorizontal)
            currPixmap = m_pixmaps->flour_gor();
        else
            currPixmap = m_pixmaps->flour();
    }
    else if ((cell.materialType() == MaterialType::PathRight) ||
             (cell.materialType() == MaterialType::PathLeft) ||
             (cell.materialType() == MaterialType::PathUp) ||
             (cell.materialType() == MaterialType::PathBottom))
    {
        currPixmap = m_pixmaps->grass();
    }
    else
        currPixmap = m_pixmaps->none();
    return currPixmap;
}
