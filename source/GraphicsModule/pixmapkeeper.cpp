#include "pixmapkeeper.h"

PixmapKeeper::PixmapKeeper(int bigSize, int smallSize) :
    big(bigSize),
    small(smallSize)
{
    QPixmap *none           = new QPixmap(QLatin1String(":resources/images/none.png"));
    QPixmap *none_ver       = new QPixmap(QLatin1String(":resources/images/none_ver.png"));
    QPixmap *none_gor       = new QPixmap(QLatin1String(":resources/images/none_gor.png"));
    QPixmap *flour          = new QPixmap(QLatin1String(":resources/images/flour.png"));
    QPixmap *flour_ver      = new QPixmap(QLatin1String(":resources/images/flour_ver.png"));
    QPixmap *flour_gor      = new QPixmap(QLatin1String(":resources/images/flour_gor.png"));
    QPixmap *grass          = new QPixmap(QLatin1String(":resources/images/grass.png"));
    QPixmap *path_right     = new QPixmap(QLatin1String(":resources/images/path.png"));
    QPixmap *wall_gor       = new QPixmap(QLatin1String(":resources/images/wall_gor.png"));
    QPixmap *wall_ver       = new QPixmap(QLatin1String(":resources/images/wall_ver.png"));
    QPixmap *wall_pillar    = new QPixmap(QLatin1String(":resources/images/wall_pillar.png"));
    QPixmap *concrete_gor   = new QPixmap(QLatin1String(":resources/images/concrete_gor.png"));
    QPixmap *concrete_ver   = new QPixmap(QLatin1String(":resources/images/concrete_ver.png"));
    QPixmap *concrete_pil   = new QPixmap(QLatin1String(":resources/images/concrete_pillar.png"));
    QPixmap *wall_gor_dest  = new QPixmap(QLatin1String(":resources/images/wall_gor_dest.png"));
    QPixmap *dest_res       = new QPixmap(QLatin1String(":resources/images/dest_res.png"));
    QPixmap *treasure       = new QPixmap(QLatin1String(":resources/images/treasure.png"));
    QPixmap *arsenal        = new QPixmap(QLatin1String(":resources/images/arsenal.png"));
    QPixmap *hole_type1     = new QPixmap(QLatin1String(":resources/images/hole_type1.png"));
    QPixmap *hole_type2     = new QPixmap(QLatin1String(":resources/images/hole_type2.png"));
    QPixmap *hole_closed    = new QPixmap(QLatin1String(":resources/images/hole_closed.png"));

    QPixmap scNone          = none->scaled(         big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scNone_ver      = none_ver->scaled(     big,    small,  Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scNone_gor      = none_gor->scaled(     small,  big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scNone_pillar   = none->scaled(         small,  small,  Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scFlour         = flour->scaled(        big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scFlour_ver     = flour_ver->scaled(    small,  big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scFlour_gor     = flour_gor->scaled(    big,    small,  Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scGrass         = grass->scaled(        big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scPathRight     = path_right->scaled(   big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scWall_gor      = wall_gor->scaled(     big,    small,  Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scWall_ver      = wall_ver->scaled(     small,  big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scWall_pillar   = wall_pillar->scaled(  small,  small,  Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scConcrete_gor  = concrete_gor->scaled( big,    small,  Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scConcrete_ver  = concrete_ver->scaled( small,  big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scConcrete_pil  = concrete_pil->scaled( small,  small,  Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scWall_gor_dest = wall_gor_dest->scaled(big,    small,  Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scDest_res      = dest_res->scaled(     big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scTreasure      = treasure->scaled(     big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scArsenal       = arsenal->scaled(      big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scHoleType1     = hole_type1->scaled(   big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scHoleType2     = hole_type2->scaled(   big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scHoleClosed    = hole_closed->scaled(  big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

    m_none                  = new QPixmap(scNone);
    m_none_ver              = new QPixmap(scNone_ver);
    m_none_gor              = new QPixmap(scNone_gor);
    m_none_pillar           = new QPixmap(scNone_pillar);
    m_flour                 = new QPixmap(scFlour);
    m_flour_ver             = new QPixmap(scFlour_ver);
    m_flour_gor             = new QPixmap(scFlour_gor);
    m_grass                 = new QPixmap(scGrass);
    m_path_right            = new QPixmap(scPathRight);
    m_wall_gor              = new QPixmap(scWall_gor);
    m_wall_ver              = new QPixmap(scWall_ver);
    m_wall_pillar           = new QPixmap(scWall_pillar);
    m_concrete_gor          = new QPixmap(scConcrete_gor);
    m_concrete_ver          = new QPixmap(scConcrete_ver);
    m_concrete_pillar       = new QPixmap(scConcrete_pil);
    m_wall_gor_dest         = new QPixmap(scWall_gor_dest);
    m_dest_res              = new QPixmap(scDest_res);
    m_treasure              = new QPixmap(scTreasure);
    m_arsenal               = new QPixmap(scArsenal);
    m_hole_type1            = new QPixmap(scHoleType1);
    m_hole_type2            = new QPixmap(scHoleType2);
    m_hole_closed           = new QPixmap(scHoleClosed);

    QMatrix rm;
    rm.rotate(180);
    QPixmap scDest_res_rot  = scDest_res.transformed(rm);
    m_dest_res_rotate       = new QPixmap(scDest_res_rot);


    // TEST IMAGES
    QPixmap *t1     = new QPixmap(QLatin1String(":resources/images/t1.png"));
    QPixmap *t2     = new QPixmap(QLatin1String(":resources/images/t2.png"));
    QPixmap *t3     = new QPixmap(QLatin1String(":resources/images/t3.png"));
    QPixmap scGOR   = t1->scaled( big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scLB    = t2->scaled( big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    QPixmap scCross = t3->scaled( big,    big,    Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

    QMatrix lum;
    lum.rotate(90);
    QPixmap scVER   = scGOR.transformed(lum);
    QPixmap scLU    = scLB.transformed(lum);

    QPixmap scRU    = scLU.transformed(lum);
    QPixmap scRB    = scRU.transformed(lum);

    m_t1_ver        = new QPixmap(scVER);
    m_t1_gor        = new QPixmap(scGOR);
    m_t2_lb         = new QPixmap(scLB);
    m_t2_lu         = new QPixmap(scLU);
    m_t2_ru         = new QPixmap(scRU);
    m_t2_rb         = new QPixmap(scRB);
    m_t3            = new QPixmap(scCross);

    QPixmap scPathBottom    = scPathRight.transformed(lum);
    QPixmap scPathLeft      = scPathBottom.transformed(lum);
    QPixmap scPathUp        = scPathLeft.transformed(lum);

    m_path_bottom   = new QPixmap(scPathBottom);
    m_path_left     = new QPixmap(scPathLeft);
    m_path_up       = new QPixmap(scPathUp);

}

PixmapKeeper::~PixmapKeeper()
{
    delete m_none;
    delete m_none_ver;
    delete m_none_gor;
    delete m_none_pillar;
    delete m_flour;
    delete m_flour_ver;
    delete m_flour_gor;
    delete m_grass;
    delete m_path_right;
    delete m_path_left;
    delete m_path_bottom;
    delete m_path_up;
    delete m_wall_gor;
    delete m_wall_ver;
    delete m_wall_pillar;
    delete m_concrete_gor;
    delete m_concrete_ver;
    delete m_concrete_pillar;
    delete m_wall_gor_dest;
    delete m_dest_res;
    delete m_dest_res_rotate;
    delete m_treasure;
    delete m_arsenal;
    delete m_hole_type1;
    delete m_hole_type2;
    delete m_hole_closed;

    delete m_t1_gor;
    delete m_t1_ver;
    delete m_t2_lb;
    delete m_t2_lu;
    delete m_t2_ru;
    delete m_t2_rb;
    delete m_t3;
}


QPixmap *PixmapKeeper::none()
{
    return m_none;
}

QPixmap *PixmapKeeper::none_ver()
{
    return m_none_ver;
}

QPixmap *PixmapKeeper::none_gor()
{
    return m_none_gor;
}

QPixmap *PixmapKeeper::none_pillar()
{
    return m_none_pillar;
}

QPixmap *PixmapKeeper::flour()
{
    return m_flour;
}

QPixmap *PixmapKeeper::flour_ver()
{
    return m_flour_ver;
}

QPixmap *PixmapKeeper::flour_gor()
{
    return m_flour_gor;
}

QPixmap *PixmapKeeper::grass()
{
    return m_grass;
}

QPixmap *PixmapKeeper::path_right()
{
    return m_path_right;
}

QPixmap *PixmapKeeper::path_left()
{
    return m_path_left;
}

QPixmap *PixmapKeeper::path_bottom()
{
    return m_path_bottom;
}

QPixmap *PixmapKeeper::path_up()
{
    return m_path_up;
}

QPixmap *PixmapKeeper::wall_gor()
{
    return m_wall_gor;
}

QPixmap *PixmapKeeper::wall_ver()
{
    return m_wall_ver;
}

QPixmap *PixmapKeeper::wall_pillar()
{
    return m_wall_pillar;
}

QPixmap *PixmapKeeper::concrete_gor()
{
    return m_concrete_gor;
}

QPixmap *PixmapKeeper::concrete_ver()
{
    return m_concrete_ver;
}

QPixmap *PixmapKeeper::concrete_pillar()
{
    return m_concrete_pillar;
}

QPixmap *PixmapKeeper::wall_gor_dest()
{
    return m_wall_gor_dest;
}

QPixmap *PixmapKeeper::dest_res()
{
    return m_dest_res;
}

QPixmap *PixmapKeeper::dest_res_rotate()
{
    return m_dest_res_rotate;
}

QPixmap *PixmapKeeper::treasure()
{
    return m_treasure;
}

QPixmap *PixmapKeeper::arsenal()
{
    return m_arsenal;
}

QPixmap *PixmapKeeper::hole_type1()
{
    return m_hole_type1;
}

QPixmap *PixmapKeeper::hole_type2()
{
    return m_hole_type2;
}

QPixmap *PixmapKeeper::hole_closed()
{
    return m_hole_closed;
}


QPixmap *PixmapKeeper::test_ver()
{
    return m_t1_ver;
}

QPixmap *PixmapKeeper::test_gor()
{
    return m_t1_gor;
}

QPixmap *PixmapKeeper::test_lb()
{
    return m_t2_lb;
}

QPixmap *PixmapKeeper::test_lu()
{
    return m_t2_lu;
}

QPixmap *PixmapKeeper::test_ru()
{
    return m_t2_ru;
}

QPixmap *PixmapKeeper::test_rb()
{
    return m_t2_rb;
}

QPixmap *PixmapKeeper::test_cross()
{
    return m_t3;
}

