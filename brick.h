#ifndef BRICK_H
#define BRICK_H
#include<terrain.h>
#include<QLabel>
#include<QSizePolicy>

class Brick: public Terrain
{
public:
    Brick(QString id,QRect r):Terrain(id,r){
        QPixmap* p=new QPixmap(":/brick.jpg");
        setPixmap(p->scaled(r.width(),r.height(),Qt::KeepAspectRatio,Qt::FastTransformation));
    }
    ~Brick() override {}
    void update() override;
    void resizeEvent(QResizeEvent* event) override;
//    void moveEvent(QMoveEvent* event) override;
};

#endif // BRICK_H
