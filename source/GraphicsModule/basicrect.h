#ifndef BASICRECT_H
#define BASICRECT_H

#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <QObject>

class BasicRect : public QObject, public QGraphicsItem, public QGraphicsLayoutItem
{
    Q_OBJECT
public:
    BasicRect(QPixmap *pixmap, QSizeF size, QString text = "", QGraphicsItem *parent = 0);
    ~BasicRect();

    // Inherited from QGraphicsLayoutItem
    void setGeometry(const QRectF &geom) Q_DECL_OVERRIDE;
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const Q_DECL_OVERRIDE;

    // Inherited from QGraphicsItem
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;

    // обработка событий нажатия клавишей мыши
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    // нарисовать/убрать игрока
    void addPlayer(QColor clr);
    void delPlayer();

signals:
    void mousePressed();

private:
    QPixmap *m_pix = nullptr;
    QSizeF  m_size;
    QString m_text = "";

    bool    needPlayerDraw = false;
    QColor  color = Qt::red;
};

#endif // BASICRECT_H
