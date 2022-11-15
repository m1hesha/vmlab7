#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QTime>
#include <QTimer>

class graphics : public QGraphicsScene
{
    Q_OBJECT
public:
    graphics(QObject* parent= nullptr);
    QGraphicsItem* itemCollidesWith(QGraphicsItem* item);
    void Init();
private:
    QGraphicsRectItem* walls[4];
    QGraphicsPixmapItem* fly;

    int speed;
    double dx, dy;
public slots:
    void MoveFly();
};

#endif // GRAPHICS_H
