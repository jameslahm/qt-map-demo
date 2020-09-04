#include "parse.h"
#include "map.h"

void Util::Parse::parse(const QString &fileName, Map *map)
{
    qDebug()<< QDir::currentPath() <<endl;
    QFile mapfile(fileName);
    if(!mapfile.exists()){
        qDebug()<<"file not exist"<<endl;
        return;}
    if(!mapfile.open(QIODevice::ReadOnly)){
        qDebug()<<"some error when read the file"<<endl;
        return;
    }
    QByteArray allData=mapfile.readAll();
    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData,&jsonError));

    if(jsonError.error!=QJsonParseError::NoError){
        qDebug()<<"json parse error"<<endl;
        return ;
    }
    QVariantList dataList=jsonDoc.toVariant().toList();
    foreach(QVariant data,dataList){
        QVariantMap dataMap=data.toMap();
        QString type=dataMap.value("type").toString();
        QString id=dataMap.value("id").toString();
        qint32 x=dataMap.value("x").toInt();
        qint32 y=dataMap.value("y").toInt();
        qint32 w=dataMap.value("w").toInt();
        qint32 h=dataMap.value("h").toInt();
        QRect rect(x,y,w,h);
//        QVariantList colorList=dataMap.value("color").toList();
//        int r=colorList[0].toInt();
//        int g=colorList[1].toInt();
//        int b=colorList[2].toInt();
//        int a=colorList.value(3,100).toInt();
//        QColor color(r,g,b,a);
        if(type.isNull() || id.isNull()){
            qDebug()<<"Invalid data format"<<endl;
        }
        if (type=="terrain"){
            map->terrains.push_back(Terrain::make_terrain(id,rect));
        }
    }
}

void Util::Parse::write(const QString &fileName, Map *map)
{
    QFile mapfile(fileName);
    QJsonArray jsonArray;
    foreach(Terrain* terrain,map->terrains){
        QJsonObject obj;
        obj.insert("type",terrain->type);
        obj.insert("id",terrain->id);
        obj.insert("x",terrain->r.x());
        obj.insert("y",terrain->r.y());
        obj.insert("w",terrain->r.width());
        obj.insert("h",terrain->r.height());
        jsonArray.append(obj);
    }
    QJsonDocument doc(jsonArray);
    QByteArray ba=doc.toJson(QJsonDocument::Indented);
    if(!mapfile.open(QIODevice::WriteOnly)){
        qDebug()<<"file write error"<<endl;
    }
    mapfile.write(ba);
    mapfile.close();
}
