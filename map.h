#ifndef MAP_H
#define MAP_H
#include<QtWidgets>
#include<QVector>
#include "terrain.h"
#include"parse.h"
#include"namespace.h"

class Map:public QWidget{
public:
    enum State {EDIT,IDLE};

    State s = State::EDIT;
    QLabel* current;
    Map(QString& fileName,Map::State s=Map::State::IDLE):s(s){
        Util::Parse::parse(fileName,this);
        init();
        if(s==Map::State::IDLE){
            qDebug()<<"hello"<<endl;
            QTimer* timer=new QTimer(this);
            timer->setInterval(1000);
            timer->start();
            connect(timer,&QTimer::timeout,this,&Map::update);
        }
        setAcceptDrops(true);
    }
    Map(){
    }
    ~Map() override;
    void init();
    void update();
    void mousePressEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    QVector<Terrain*> terrains;
    void save();

private:
    QVector<QLayoutItem*> m_items;
};

#endif // MAP_H
