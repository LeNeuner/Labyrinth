#ifndef BASICRECT_H
#define BASICRECT_H

#include <QGraphicsLayoutItem>
#include <QGraphicsItem>

class BasicRect : public QGraphicsItem, public QGraphicsLayoutItem
{
public:
    BasicRect(QPixmap *pixmap, QSizeF size, QString text = "", QGraphicsItem *parent = 0);
    ~BasicRect();

    // Inherited from QGraphicsLayoutItem
    void setGeometry(const QRectF &geom) Q_DECL_OVERRIDE;
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const Q_DECL_OVERRIDE;

    // Inherited from QGraphicsItem
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;

private:
    QPixmap *m_pix = nullptr;
    QSizeF  m_size;
    QString m_text = "";
};

#endif // BASICRECT_H
