#include "basicrect.h"

#include <QGradient>
#include <QGraphicsLinearLayout>
#include <QPainter>

#include <QDebug>

BasicRect::BasicRect(QPixmap *pixmap, QSizeF size, double opac, QString text,
                     QGraphicsItem *parent/* = 0*/)
    : QObject(),
      QGraphicsItem(parent),
      QGraphicsLayoutItem()
{
    m_size.setWidth(size.width());
    m_size.setHeight(size.height());

    QPixmap image = pixmap->scaled(size.width(), size.height(), Qt::IgnoreAspectRatio, Qt::FastTransformation );
//    QPixmap* test = new QPixmap(image);

//    m_pix = test;
    m_pix = pixmap;

    if (text != "")
        m_text = text;

    // установка прозрачности ячеек
    if (opac)
        m_opacity = opac;
    this->setOpacity(m_opacity);

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

    // основная форма ячеек сетки
    QRectF frame(QPointF(0,0), geometry().size());
    qreal w = m_size.width();
    qreal h = m_size.height();

    // добавить задний фон ячейкам
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(frame);

    // добавить основную текстуру ячейки
    QPointF pixpos = frame.center() - (QPointF(w, h) / 2);
    painter->drawPixmap(pixpos, *m_pix);

    // добавить текст
    if (m_text != "")
        painter->drawText(frame.center(), m_text);

    // добавить отрисовку игрока
    if (needPlayerDraw)
    {
        painter->setBrush(color);
        painter->setPen(color);
        painter->drawEllipse(frame.center(), 5, 5);
    }
    else
    {
        painter->setBrush(QColor(0,0,0,0));
        painter->setPen(QColor(0,0,0,0));
        painter->drawEllipse(frame.center(), 5, 5);
    }
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


void BasicRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "XXX";
    this->setOpacity(0.5);
    emit mousePressed();
}

void BasicRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "YYY";
    this->setOpacity(1.0);
}


void BasicRect::addPlayer(QColor clr)
{
    color = clr;
    needPlayerDraw = true;
}
void BasicRect::delPlayer()
{
    needPlayerDraw = false;
//    color = Qt::transparent;
}
