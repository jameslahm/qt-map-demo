#include "terrain.h"
#include "brick.h"


Terrain* Terrain::make_terrain(QString id,QRect r){
    if(id=="brick"){
        return new Brick(id,r);
    }
    return new Terrain(id,r);
}
