#include "labygraphicsscene.h"
#include <QPainter>

#include <QDebug>

LabyGraphicsScene::LabyGraphicsScene(GlobalModel* model) /*: QObject(), QGraphicsScene()*/
{
    int big   = DEFAULT_BIG_PICTURE_SIZE;
    int small = DEFAULT_SMALL_PICTURE_SIZE;

    pixmaps = new PixmapKeeper(big, small);
    scene = new QGraphicsScene(this);

//    QPixmap *bGrass  = new QPixmap(QLatin1String(":resources/images/bigGrass.jpg"));
//    QPixmap bigGrass = bGrass->scaled(1000, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
//    scene->setBackgroundBrush(Qt::green);

    BasicRect *item = new BasicRect(pixmaps->none(), QSizeF(small, small));

    QGraphicsLinearLayout *windowLayout = new QGraphicsLinearLayout(Qt::Vertical);
    grid = new QGraphicsGridLayout(windowLayout);
    grid->setVerticalSpacing(0);
    grid->setHorizontalSpacing(0);

    if (model == nullptr)
        qDebug() << "nullptr";

    QSizeF  cellSize;
    QPixmap *currPixmap = pixmaps->none();
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

            currPixmap = pixmaps->grass();


//            if (model->fieldModel->cell[y][x].materialType() == MaterialType::None)
//            {
//                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
//                    currPixmap = pixmaps->field_ver();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
//                    currPixmap = pixmaps->field_gor();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
//                    currPixmap = pixmaps->field_pillar();
//                else
//                    currPixmap = pixmaps->field();
//            }
//            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Field)
//                currPixmap = pixmaps->flour();
//            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Grass)
//                currPixmap = pixmaps->grass();
//            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Wall)
//            {
//                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
//                    currPixmap = pixmaps->wall_ver();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
//                    currPixmap = pixmaps->wall_gor();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
//                    currPixmap = pixmaps->wall_pillar();
//            }
//            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Concrete)
//            {
//                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
//                    currPixmap = pixmaps->concrete_ver();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
//                    currPixmap = pixmaps->concrete_gor();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
//                    currPixmap = pixmaps->concrete_pillar();
//            }


            item = new BasicRect(currPixmap, cellSize);
            grid->addItem(item, y, x);
        }
    }

    windowLayout->addItem(grid);
    QGraphicsWidget* gWidget = new QGraphicsWidget();
    gWidget->setLayout(windowLayout);

    // заплатка от бага (съезжает поле)
    scene->addItem(gWidget);
    scene->update();
}

LabyGraphicsScene::~LabyGraphicsScene()
{
    delete pixmaps;
    delete grid;
    delete scene;
}

QGraphicsScene* LabyGraphicsScene::graphScene()
{
    return scene;
}

QGraphicsScene *LabyGraphicsScene::updateScene(GlobalModel* model)
{
    //--------------------------------------------------
    // установка поля
    QPixmap *bGrass  = new QPixmap(QLatin1String(":resources/images/bigGrass.jpg"));
    QPixmap bigGrass = bGrass->scaled(scene->width()+200, scene->height()+100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    scene->setBackgroundBrush(bigGrass);

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
            grid->removeItem(grid->itemAt(y,x));
        }
    }
    delete grid;
    scene->clear();

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
    grid = new QGraphicsGridLayout(windowLayout);
    grid->setVerticalSpacing(0);
    grid->setHorizontalSpacing(0);

    QSizeF  cellSize;
    QPixmap *currPixmap = pixmaps->none();
    double  currOpacity = 1.0;
    BasicRect *item = new BasicRect(pixmaps->none(), QSizeF(small, small));
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
                    currPixmap = pixmaps->none_ver();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                    currPixmap = pixmaps->none_gor();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                    currPixmap = pixmaps->none_pillar();
                else
                    currPixmap = pixmaps->none();
            }
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Flour)
            {
                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                    currPixmap = pixmaps->flour_ver();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                    currPixmap = pixmaps->flour_gor();
                else
                    currPixmap = pixmaps->flour();
            }
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Grass)
            {
                    currPixmap = pixmaps->grass();
            }
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Wall)
            {
                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                    currPixmap = pixmaps->wall_ver();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                    currPixmap = pixmaps->wall_gor();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                    currPixmap = pixmaps->wall_pillar();
            }
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Concrete)
            {
                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                    currPixmap = pixmaps->concrete_ver();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                    currPixmap = pixmaps->concrete_gor();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                    currPixmap = pixmaps->concrete_pillar();
            }
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Exit)
            {
                if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                    currPixmap = pixmaps->flour_ver();
                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                    currPixmap = pixmaps->flour_gor();
                else
                    currPixmap = pixmaps->flour();
            }
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::PathRight)
                currPixmap = pixmaps->path_right();
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::PathLeft)
                currPixmap = pixmaps->path_left();
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::PathUp)
                currPixmap = pixmaps->path_up();
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::PathBottom)
                currPixmap = pixmaps->path_bottom();
            else
                currPixmap = pixmaps->grass();


            // тип объекта в поле
            if ((model->fieldModel->cell[y][x].objectType() == ObjectType::RealTreasure) ||
                (model->fieldModel->cell[y][x].objectType() == ObjectType::FakeTreasure))
                currPixmap = pixmaps->treasure();
            else if (model->fieldModel->cell[y][x].objectType() == ObjectType::Arsenal)
                currPixmap = pixmaps->arsenal();
            else if ((model->fieldModel->cell[y][x].objectType() == ObjectType::HoleTypeI) ||
                (model->fieldModel->cell[y][x].objectType() == ObjectType::HoleTypeII))
            {
                currPixmap = pixmaps->hole_closed();
//                text = "I-II";
            }
            else if ((model->fieldModel->cell[y][x].objectType() == ObjectType::HoleTypeA) ||
                (model->fieldModel->cell[y][x].objectType() == ObjectType::HoleTypeB) ||
                (model->fieldModel->cell[y][x].objectType() == ObjectType::HoleTypeC))
            {
                currPixmap = pixmaps->hole_closed();
//                text = "ABC";
            }


//            if ((model->fieldModel->cell[y][x].testVisitedNum != 0) &&
//                (model->fieldModel->cell[y][x].formType() == FormType::Square) &&
//                (model->fieldModel->cell[y][x].objectType() != ObjectType::Arsenal))
//            {
//                text = QString::number(model->fieldModel->cell[y][x].testVisitedNum);
//            }


            item = new BasicRect(currPixmap, cellSize, currOpacity, text);
            grid->addItem(item, y, x);


            if (testPixmap != nullptr)
            {
                item = new BasicRect(testPixmap, cellSize, currOpacity, text);
                grid->addItem(item, y, x);
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

    windowLayout->addItem(grid);
    QGraphicsWidget* gWidget = new QGraphicsWidget();
    gWidget->setLayout(windowLayout);
    scene->addItem(gWidget);
    scene->update();

    return scene;
}

// обновить графическую сцену игрока
QGraphicsScene *LabyGraphicsScene::updatePlayerScene(GlobalModel *model)
{
    //--------------------------------------------------
    // установка поля
    int scnW = static_cast<int>(scene->width());
    int scnH = static_cast<int>(scene->height());
    QPixmap *bGrass  = new QPixmap(QLatin1String(":resources/images/bigGrass.jpg"));
    QPixmap bigGrass = bGrass->scaled(scnW+200, scnH-100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    scene->setBackgroundBrush(/*bigGrass*/Qt::white);

    //--------------------------------------------------
    // отрисовка в соответствии с новой моделью
    int big   = DEFAULT_BIG_PICTURE_SIZE;
    int small = DEFAULT_SMALL_PICTURE_SIZE;

    //--------------------------------------------------
    // очистка сцены
    if (grid != nullptr)
    {
        for (int y = 0; y < model->fieldModel->getFullHeight(); y++)
        {
            for (int x = 0; x < model->fieldModel->getFullWidth(); x++)
            {
                grid->removeItem(grid->itemAt(y,x));
            }
        }
        delete grid;
        scene->clear();
    }

    //--------------------------------------------------
    // отрисовка новой сцены
    QGraphicsLinearLayout *windowLayout = new QGraphicsLinearLayout(Qt::Vertical);
    grid = new QGraphicsGridLayout(windowLayout);
    grid->setVerticalSpacing(0);
    grid->setHorizontalSpacing(0);

    QSizeF  cellSize;
    QPixmap *currPixmap = pixmaps->none();
    double  currOpacity = 1.0;
    BasicRect *item = new BasicRect(pixmaps->none(), QSizeF(small, small));
    for (int y = 0; y < model->fieldModel->getFullHeight(); y++)
    {
        for (int x = 0; x < model->fieldModel->getFullWidth(); x++)
        {
            QPixmap *testPixmap = nullptr;
            QString text = "";

            // установка размера ячейки в соответствии с формой поля
            if (model->fieldModel->cell[y][x].formType() == FormType::Square)
                cellSize = QSizeF(big, big);
            else if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                cellSize = QSizeF(small, big);
            else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                cellSize = QSizeF(big, small);
            else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                cellSize = QSizeF(small, small);

            // отрисовка закрытых и открытых для пользователя ячеек
            double closedOpacity = 0.3;
            if (!model->playerFieldModel->playerCell[y][x].visible())
            {
                if (model->fieldModel->cell[y][x].materialType() == MaterialType::Grass)
                    currPixmap = pixmaps->grass();
                else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Concrete)
                {
                    if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                        currPixmap = pixmaps->concrete_ver();
                    else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                        currPixmap = pixmaps->concrete_gor();
                    else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                        currPixmap = pixmaps->concrete_pillar();
                    currOpacity = closedOpacity;
                }
                else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Exit)
                {
                    if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                        currPixmap = pixmaps->concrete_ver();
                    else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                        currPixmap = pixmaps->concrete_gor();
                    currOpacity = closedOpacity;
                }
                else if ((model->fieldModel->cell[y][x].materialType() == MaterialType::Flour) ||
                         (model->fieldModel->cell[y][x].materialType() == MaterialType::Wall))
                {
                    if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                        currPixmap = pixmaps->flour_ver();
                    else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                        currPixmap = pixmaps->flour_gor();
                    else
                        currPixmap = pixmaps->flour();
                    currOpacity = closedOpacity;
                }
                else if ((model->fieldModel->cell[y][x].materialType() == MaterialType::PathRight) ||
                         (model->fieldModel->cell[y][x].materialType() == MaterialType::PathLeft) ||
                         (model->fieldModel->cell[y][x].materialType() == MaterialType::PathUp) ||
                         (model->fieldModel->cell[y][x].materialType() == MaterialType::PathBottom))
                {
                    currPixmap = pixmaps->grass();
                }


//                if (model->fieldModel->cell[y][x].formType() == FormType::Square)
//                    currPixmap = pixmaps->flour(); // field();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
//                    currPixmap = pixmaps->flour_ver(); // field_ver();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
//                    currPixmap = pixmaps->wall_gor(); // field_gor();
//                else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
//                    currPixmap = pixmaps->concrete_pillar(); //field_pillar();
//                currOpacity = 0.7;
            }
            else
            {
                if (model->fieldModel->cell[y][x].materialType() == MaterialType::Grass)
                    currPixmap = pixmaps->grass();
                else if (model->fieldModel->cell[y][x].materialType() == MaterialType::None)
                {
                    if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                        currPixmap = pixmaps->flour_ver();
                    else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                        currPixmap = pixmaps->flour_gor();
                    else
                        currPixmap = pixmaps->flour();
                }
                else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Wall)
                {
                    if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                        currPixmap = pixmaps->wall_ver();
                    else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                        currPixmap = pixmaps->wall_gor();
                    else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                        currPixmap = pixmaps->wall_pillar();
                }
                else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Concrete)
                {
                    if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                        currPixmap = pixmaps->concrete_ver();
                    else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                        currPixmap = pixmaps->concrete_gor();
                    else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                        currPixmap = pixmaps->concrete_pillar();
                }
                else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Exit)
                {
                    if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                        currPixmap = pixmaps->flour_ver();
                    else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                        currPixmap = pixmaps->flour_gor();
                    else
                        currPixmap = pixmaps->flour();
                }
                else if (model->fieldModel->cell[y][x].materialType() == MaterialType::PathRight)
                    currPixmap = pixmaps->path_right();
                else if (model->fieldModel->cell[y][x].materialType() == MaterialType::PathLeft)
                    currPixmap = pixmaps->path_left();
                else if (model->fieldModel->cell[y][x].materialType() == MaterialType::PathUp)
                    currPixmap = pixmaps->path_up();
                else if (model->fieldModel->cell[y][x].materialType() == MaterialType::PathBottom)
                    currPixmap = pixmaps->path_bottom();
                else
                    currPixmap = pixmaps->grass();

                currOpacity = 1.0;
            } // end if open/close cell

            item = new BasicRect(currPixmap, cellSize, currOpacity, text);
            grid->addItem(item, y, x);
        }
    }

    windowLayout->addItem(grid);
    QGraphicsWidget* gWidget = new QGraphicsWidget();
    gWidget->setLayout(windowLayout);
    scene->addItem(gWidget);
    scene->update();

    return scene;
}
