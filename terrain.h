#ifndef TERRAIN_H
#define TERRAIN_H
#include<QString>
#include<QLabel>

class Terrain:public QLabel
{
public:
    QString type="terrain";
    QString id;
    QRect r;
    QColor c;
    Terrain(QString id,QRect r):id(id),r(r){}
    static Terrain* make_terrain(QString id,QRect r);
    ~Terrain() override {}
    virtual void update(){}
};

#endif // TERRAIN_H
