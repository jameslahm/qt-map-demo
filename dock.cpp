#include "dock.h"
#include<QMouseEvent>
#include<QDragEnterEvent>
#include<QDropEvent>
#include<QDragMoveEvent>
#include<QDrag>
#include<QMimeData>
#include<QPainter>
#include<QDebug>
#include<QStyle>

void Dock::mousePressEvent(QMouseEvent *event){
    Terrain *child = dynamic_cast<Terrain*>(childAt(event->pos()));
    if (!child) return;

    QPixmap pixmap = *child->pixmap();
    QDrag *drag=new QDrag(this);
    QMimeData *mimeData=new QMimeData;
    QPoint offset =event->pos() - (child->pos()+QPoint(0,27));
    qDebug()<<offset<<endl;
    QString s = QString("%1 %2 %3 %4 %5 %6 %7").arg(child->id,QString::number(child->r.x()),QString::number(child->r.y()),
                                                    QString::number(child->r.width()),QString::number(child->r.height()),
                                                    QString::number(offset.x()),QString::number(offset.y()));
    mimeData->setText(s);
    drag->setPixmap(pixmap);
    drag->setMimeData(mimeData);
    qDebug()<<child->pos()<<endl;
    qDebug()<<event->pos()<<endl;
    drag->setHotSpot(event->pos() - (child->pos()+QPoint(0,27)));

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();
    child->setPixmap(tempPixmap);
    drag->exec(Qt::CopyAction);
    child->setPixmap(pixmap);
}

void Dock::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->source()!=this){
        event->ignore();
    }
   event->acceptProposedAction();
}

void Dock::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->source()!=this){
        event->ignore();
    }
    event->acceptProposedAction();
}

void Dock::dropEvent(QDropEvent *event)
{
    event->ignore();
}
