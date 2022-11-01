#include <graphics.h>

void graphics::Init(){

    QPolygon poligonebed;
    poligonebed << QPoint(0, 0) << QPoint(200, 0)<<QPoint(200, 200)<<QPoint(0, 200);
    QGraphicsPolygonItem* bed = addPolygon(poligonebed, QPen(Qt::black), QBrush(QColor(100, 50, 150)));
    bed->setPos(300, 300);
    bed->setFlags(QGraphicsItem::ItemIsMovable);
    bed->setData(0, "bed");

    /*QGraphicsPolygonItem* bed2 = addPolygon(poligonebed, QPen(Qt::black), QBrush(QColor(102, 51, 0)));
    bed2->setPos(500, 300);
    bed2->setFlags(QGraphicsItem::ItemIsMovable);
    bed2->setData(0, "bed");*/

    QPixmap newImage;
    if (!newImage.load(QStringLiteral(":/images/dinner.png"))){
        return;
    }

/*
    QGraphicsPixmapItem* dinner[2];
    for(int i=0; i<2; i++){
            dinner[i] = addPixmap(newImage);
            dinner[i]->setPos(i*500+100,350);
            dinner[i]->setScale(0.5);
            dinner[i]->setData(0, "bed");
            dinner[i]->setFlags(QGraphicsItem::ItemIsMovable);
        };
*/
            QGraphicsPixmapItem* dinner;
            dinner = addPixmap(newImage);
            dinner->setPos(365,360);
            dinner->setScale(0.5);
            dinner->setData(0, "bed");
            dinner->setFlags(QGraphicsItem::ItemIsMovable);


    if (!newImage.load(QStringLiteral(":/images/fly.png"))) {
        return;
    }
    fly = addPixmap(newImage);
    fly->setScale(0.5);
    fly->setPos(360, 200);
    fly->setData(0, "fly");

    walls[0] = addRect(QRectF(0,0,10,500),QPen(Qt::black), QBrush(QColor(220, 20, 60)));
    walls[1] = addRect(QRectF(800,0,10,500), QPen(Qt::black), QBrush(QColor(220, 20, 60)));
    walls[2] = addRect(QRectF(0,0,800,10), QPen(Qt::black), QBrush(QColor(220, 20, 60)));
    walls[3] = addRect(QRectF(0,500,800,10), QPen(Qt::black), QBrush(QColor(220, 20, 60)));

    for(int i=0; i<4; i++)
            walls[i]->setData(0,"Wall");
}

void graphics::MoveFly(){
    QTransform transform = fly->transform();
    transform.translate(dx,dy);
    fly->setTransform(transform);
    QGraphicsItem* barrier = itemCollidesWith(fly);
    transform=fly->transform();
    if(barrier){
        if(barrier->data(0)=="Wall" || barrier->data(0)=="bed"){
            dx=-dx;
            dy=-dy;
        }
    }
}


graphics::graphics(QObject* parent):QGraphicsScene (parent)
{
    Init();
    dx = 1;
    dy = 1;
    speed = 1;
    qsrand(QTime(1,1,1).secsTo(QTime::currentTime()));
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MoveFly()));
    timer->start(10);

}


QGraphicsItem * graphics::itemCollidesWith(QGraphicsItem *item)
{
    QList<QGraphicsItem *> collisions = collidingItems(item);
    foreach (QGraphicsItem *it, collisions){
        if(it == item)
            continue;
        return it;
    }
    return nullptr;
}
