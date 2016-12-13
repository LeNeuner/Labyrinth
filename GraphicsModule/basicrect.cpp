#include "basicrect.h"

#include <QGradient>
#include <QGraphicsLinearLayout>
#include <QPainter>

BasicRect::BasicRect(QPixmap *pixmap, QSizeF size, QString text, QGraphicsItem *parent/* = 0*/)
    : QGraphicsLayoutItem(), QGraphicsItem(parent)
{
    m_size.setWidth(size.width());
    m_size.setHeight(size.height());

    QPixmap image = pixmap->scaled(size.width(), size.height(), Qt::IgnoreAspectRatio, Qt::FastTransformation );
    QPixmap* test = new QPixmap(image);

//    m_pix = test;
    m_pix = pixmap;


    if (text != "")
        m_text = text;

//    m_pix->scaledToWidth(m_size.width());
//    m_pix->scaledToHeight(m_size.height());

    setGraphicsItem(this);
}

BasicRect::~BasicRect()
{
//    if (m_pix != nullptr)
//        delete m_pix;
}

//! [1]
void BasicRect::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QRectF frame(QPointF(0,0), geometry().size());
    qreal w = m_size.width();
    qreal h = m_size.height();

    QPointF pixpos = frame.center() - (QPointF(w, h) / 2);
    painter->drawPixmap(pixpos, *m_pix);

    if (m_text != "")
        painter->drawText(frame.center(), m_text);
}
//! [2]

//! [3]
QRectF BasicRect::boundingRect() const
{
    return QRectF(QPointF(0,0), geometry().size());
}
//! [3]

//! [4]
void BasicRect::setGeometry(const QRectF &geom)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.topLeft());
}
//! [4]

//! [5]
QSizeF BasicRect::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    switch (which) {
    case Qt::MinimumSize:
    case Qt::PreferredSize:
        // Do not allow a size smaller than the pixmap with two frames around it.
 //       return QSizeF(10,10);//m_pix->size() + QSize(0, 0); // 12
        return m_size + QSize(0, 0); // 12
    case Qt::MaximumSize:
        return QSizeF(1000,1000);
    default:
        break;
    }
    return constraint;
}
//! [5]