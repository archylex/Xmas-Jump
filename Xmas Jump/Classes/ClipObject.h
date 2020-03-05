#ifndef __CLIPOBJECT_H__
#define __CLIPOBJECT_H__

#include <iostream>
#include "cocos2d.h"
#include "Isometry.h"

using namespace std;
using namespace cocos2d;

class ClipObject : public ClippingNode {
    public:
        static ClipObject *create(int _tObj, float _vel);
        void update(float dt);
        void setDegree(double _deg);
                
    private:
        bool initialize(int _tObj, float _vel);
        Sprite *sprite;
        int tObj;
        double degree;
};

#endif
