#include "brick.h"
#include<QDebug>
#include<QResizeEvent>

void Brick::update(){
    this->r.moveLeft(r.left()+10);
}

void Brick::resizeEvent(QResizeEvent *event)
{

    QPixmap p = *pixmap();
    setPixmap(p.scaled(r.width(),r.height(),Qt::KeepAspectRatio,Qt::FastTransformation));
    event->accept();
}


