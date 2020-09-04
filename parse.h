#ifndef PARSE_H
#define PARSE_H
#include<QString>
#include "namespace.h"

class Map;

class Util::Parse
{
public:
    static void parse(const QString& fileName,Map* map);
    static void write(const QString& fileName,Map* map);
};

#endif // PARSE_H
