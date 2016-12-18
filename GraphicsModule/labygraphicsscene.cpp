#include "labygraphicsscene.h"
#include <QPainter>

#include <QDebug>

LabyGraphicsScene::LabyGraphicsScene(GlobalModel* model)
{
    int big   = DEFAULT_BIG_PICTURE_SIZE;
    int small = DEFAULT_SMALL_PICTURE_SIZE;

    pixmaps = new PixmapKeeper(big, small);
    scene = new QGraphicsScene(this);

    BasicRect *item = new BasicRect(pixmaps->field(), QSizeF(small, small));

    QGraphicsLinearLayout *windowLayout = new QGraphicsLinearLayout(Qt::Vertical);
    grid = new QGraphicsGridLayout(windowLayout);
    grid->setVerticalSpacing(0);
    grid->setHorizontalSpacing(0);


    if (model == nullptr)
        qDebug() << "nullptr";


    QSizeF  cellSize;
    QPixmap *currPixmap = pixmaps->field();
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


            if (model->fieldModel->cell[y][x].materialType() == MaterialType::None)
                currPixmap = pixmaps->field();
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Field)
                currPixmap = pixmaps->flour();
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Grass)
                currPixmap = pixmaps->grass();
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


            item = new BasicRect(currPixmap, cellSize);
            grid->addItem(item, y, x);
        }
    }

    windowLayout->addItem(grid);
    QGraphicsWidget* gWidget = new QGraphicsWidget();
    gWidget->setLayout(windowLayout);
    scene->addItem(gWidget);

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
    QPixmap *currPixmap = pixmaps->field();
    BasicRect *item = new BasicRect(pixmaps->field(), QSizeF(small, small));
    for (int y = 0; y < model->fieldModel->getFullHeight(); y++)
    {
        for (int x = 0; x < model->fieldModel->getFullWidth(); x++)
        {
            QPixmap *testPixmap = nullptr;
            QString text = "";
            if (model->fieldModel->cell[y][x].formType() == FormType::Square)
                cellSize = QSizeF(big, big);
            else if (model->fieldModel->cell[y][x].formType() == FormType::Vertical)
                cellSize = QSizeF(small, big);
            else if (model->fieldModel->cell[y][x].formType() == FormType::Gorizontal)
                cellSize = QSizeF(big, small);
            else if (model->fieldModel->cell[y][x].formType() == FormType::Pillar)
                cellSize = QSizeF(small, small);


            if (model->fieldModel->cell[y][x].materialType() == MaterialType::None)
                currPixmap = pixmaps->field();
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Field)
                currPixmap = pixmaps->flour();
            else if (model->fieldModel->cell[y][x].materialType() == MaterialType::Grass)
                currPixmap = pixmaps->grass();
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
                currPixmap = pixmaps->flour();
            }


            if ((model->fieldModel->cell[y][x].objectType() == ObjectType::RealTreasure) ||
                (model->fieldModel->cell[y][x].objectType() == ObjectType::FakeTreasure))
                currPixmap = pixmaps->treasure();

            if (model->fieldModel->cell[y][x].objectType() == ObjectType::Arsenal)
                currPixmap = pixmaps->arsenal();

            if ((model->fieldModel->cell[y][x].holeType() == HoleType::TypeI) ||
                (model->fieldModel->cell[y][x].holeType() == HoleType::TypeII))
                currPixmap = pixmaps->hole_type1();

            if ((model->fieldModel->cell[y][x].holeType() == HoleType::TypeA) ||
                (model->fieldModel->cell[y][x].holeType() == HoleType::TypeB) ||
                (model->fieldModel->cell[y][x].holeType() == HoleType::TypeC))
                currPixmap = pixmaps->hole_type2();

            if ((model->fieldModel->cell[y][x].testVisitedNum != 0) &&
                (model->fieldModel->cell[y][x].formType() == FormType::Square) &&
                (model->fieldModel->cell[y][x].objectType() != ObjectType::Arsenal))
            {
                text = QString::number(model->fieldModel->cell[y][x].testVisitedNum);

                // TEST LINE
                //--------------------------------------------------
                int Z  = model->fieldModel->cell[y][x].testVisitedNum;
                int LZ = model->fieldModel->cell[y][x-2].testVisitedNum;
                int RZ = model->fieldModel->cell[y][x+2].testVisitedNum;
                int UZ = model->fieldModel->cell[y-2][x].testVisitedNum;
                int BZ = model->fieldModel->cell[y+2][x].testVisitedNum;


//                if ((( RZ == Z + 1) && ( LZ == Z - 1)) ||
//                    (( RZ == Z - 1) && ( LZ == Z + 1)))
//                        testPixmap = pixmaps->test_gor();

//                else if ((( UZ == Z + 1) && ( BZ == Z - 1)) ||
//                         (( UZ == Z - 1) && ( BZ == Z + 1)))
//                             testPixmap = pixmaps->test_ver();

//                else if ((( LZ == Z + 1) && ( BZ == Z - 1)) ||
//                         (( LZ == Z - 1) && ( BZ == Z + 1)))
//                             testPixmap = pixmaps->test_lb();

//                else if ((( LZ == Z + 1) && ( UZ == Z - 1)) ||
//                         (( LZ == Z - 1) && ( UZ == Z + 1)))
//                             testPixmap = pixmaps->test_lu();

//                else if ((( UZ == Z + 1) && ( RZ == Z - 1)) ||
//                         (( UZ == Z - 1) && ( RZ == Z + 1)))
//                             testPixmap = pixmaps->test_ru();

//                else if ((( RZ == Z + 1) && ( BZ == Z - 1)) ||
//                         (( RZ == Z - 1) && ( BZ == Z + 1)))
//                             testPixmap = pixmaps->test_rb();
//                else
//                    testPixmap = pixmaps->test_cross();

                //--------------------------------------------------
            }


            item = new BasicRect(currPixmap, cellSize, text);
            grid->addItem(item, y, x);


            if (testPixmap != nullptr)
            {
                item = new BasicRect(testPixmap, cellSize, text);
                grid->addItem(item, y, x);
            }
        }
    }

    windowLayout->addItem(grid);
    QGraphicsWidget* gWidget = new QGraphicsWidget();
    gWidget->setLayout(windowLayout);
    scene->addItem(gWidget);
    scene->update();

    return scene;
}
