#ifndef ISOMETRY_H
#define ISOMETRY_H

#include "cocos2d.h"

#define PI 3.14159265359

using namespace cocos2d;

class Isometry
{
public:
    static Vec2 toIsometric(Vec2 _pos);
    static Vec2 fromIsometric(Vec2 _pos);
};

#endif // ISOMETRY_H
