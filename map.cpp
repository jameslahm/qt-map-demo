#include "map.h"

Map::~Map(){
    for(int i=0;i<terrains.size();i++){
        delete terrains[i];
    }
    terrains.clear();
}


void Map::init(){
    foreach(Terrain* terrain,terrains){
        terrain->setParent(this);
        terrain->show();
        terrain->setGeometry(terrain->r);
    }
}

void Map::update(){
    foreach(Terrain* terrain,terrains){
        if(s==Map::State::IDLE)terrain->update();
        qDebug()<<terrain->r<<endl;
        terrain->setGeometry(terrain->r);
    }
}

void Map::mousePressEvent(QMouseEvent *event){
    if(s != Map::State::EDIT){
        return ;
    }
    Terrain *child = dynamic_cast<Terrain*>(childAt(event->pos()));
    if (!child) return;

    QPixmap pixmap = *child->pixmap();
    QDrag *drag=new QDrag(this);
    QMimeData *mimeData=new QMimeData;
    QPoint offset =event->pos() - child->pos();
    QString s = QString("%1 %2 %3 %4 %5 %6 %7").arg(child->id,QString::number(child->r.x()),QString::number(child->r.y()),
                                                    QString::number(child->r.width()),QString::number(child->r.height()),
                                                    QString::number(offset.x()),QString::number(offset.y()));
    mimeData->setText(s);
    drag->setPixmap(pixmap);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();
    child->setPixmap(tempPixmap);
    if(drag->exec(Qt::MoveAction)==Qt::MoveAction){
        int index=terrains.indexOf(child);
        delete terrains[index];
        terrains.remove(index);
        update();
    };
}

void Map::dragEnterEvent(QDragEnterEvent *event)
{
   if (event->source() == this) {
       event->setDropAction(Qt::MoveAction);
       event->accept();
    } else {
       event->setDropAction(Qt::CopyAction);
       event->acceptProposedAction();
    }
}

void Map::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
     } else {
        event->setDropAction(Qt::CopyAction);
        event->acceptProposedAction();
    }
}

void Map::dropEvent(QDropEvent *event)
{
    QString s=event->mimeData()->text();
    QTextStream ss(&s);
    QString id;
    int x = 0;
    int y = 0;
    int w = 0;
    int h=0;
    int ox=0;
    int oy=0;
    ss>>id >> x >> y >> w >> h>>ox>>oy;
    x=event->pos().x()-ox;
    y=event->pos().y()-oy;
    Terrain* t=Terrain::make_terrain(id,QRect(x,y,w,h));
    terrains.append(t);
    t->setParent(this);
    t->show();
    if (event->source() == this) {
         event->setDropAction(Qt::MoveAction);
         event->accept();
    } else {
        event->setDropAction(Qt::CopyAction);
        event->acceptProposedAction();
        update();
     }
}

void Map::save(){
    Util::Parse::write("map.json",this);
    QMessageBox msgBox;
    msgBox.setText("The Map has been save successfully!");
    msgBox.exec();
}
