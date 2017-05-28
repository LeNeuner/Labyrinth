#ifndef PIXMAPKEEPER_H
#define PIXMAPKEEPER_H

#include <QPixmap>
#include "constlist.h"

class PixmapKeeper
{

public:
    PixmapKeeper(int bigSize, int smallSize);
    ~PixmapKeeper();

    QPixmap *none();
    QPixmap *none_ver();
    QPixmap *none_gor();
    QPixmap *none_pillar();
    QPixmap *flour();
    QPixmap *flour_ver();
    QPixmap *flour_gor();
    QPixmap *grass();
    QPixmap *path_right();
    QPixmap *path_left();
    QPixmap *path_up();
    QPixmap *path_bottom();
    QPixmap *wall_gor();
    QPixmap *wall_ver();
    QPixmap *wall_pillar();
    QPixmap *concrete_gor();
    QPixmap *concrete_ver();
    QPixmap *concrete_pillar();
    QPixmap *wall_gor_dest();
    QPixmap *dest_res();
    QPixmap *dest_res_rotate();
    QPixmap *treasure();
    QPixmap *arsenal();
    QPixmap *hole_type1();
    QPixmap *hole_type2();
    QPixmap *hole_closed();

    QPixmap *test_ver();
    QPixmap *test_gor();
    QPixmap *test_lb();
    QPixmap *test_lu();
    QPixmap *test_ru();
    QPixmap *test_rb();
    QPixmap *test_cross();
private:
    int big   = DEFAULT_BIG_PICTURE_SIZE;
    int small = DEFAULT_SMALL_PICTURE_SIZE;

    QPixmap *m_none;
    QPixmap *m_none_ver;
    QPixmap *m_none_gor;
    QPixmap *m_none_pillar;
    QPixmap *m_flour;
    QPixmap *m_flour_ver;
    QPixmap *m_flour_gor;
    QPixmap *m_grass;
    QPixmap *m_path_right;
    QPixmap *m_path_left;
    QPixmap *m_path_up;
    QPixmap *m_path_bottom;
    QPixmap *m_wall_gor;
    QPixmap *m_wall_ver;
    QPixmap *m_wall_pillar;
    QPixmap *m_concrete_gor;
    QPixmap *m_concrete_ver;
    QPixmap *m_concrete_pillar;
    QPixmap *m_wall_gor_dest;
    QPixmap *m_dest_res;
    QPixmap *m_dest_res_rotate;
    QPixmap *m_treasure;
    QPixmap *m_arsenal;
    QPixmap *m_hole_type1;
    QPixmap *m_hole_type2;
    QPixmap *m_hole_closed;

    QPixmap *m_t1_ver;
    QPixmap *m_t1_gor;
    QPixmap *m_t2_lb;
    QPixmap *m_t2_lu;
    QPixmap *m_t2_ru;
    QPixmap *m_t2_rb;
    QPixmap *m_t3;
};

#endif // PIXMAPKEEPER_H
