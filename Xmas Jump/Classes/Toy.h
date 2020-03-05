#ifndef __TOY_H__
#define __TOY_H__

#include <iostream>
#include "cocos2d.h"
#include "IceBlock.h"

using namespace std;
using namespace cocos2d;

class Toy : public Sprite {
    public:
        static Toy *create(string _name);        
        void update(float dt);
        void setNoIsoPosition(Vec2 _pos);
        Vec2 getNoIsoPosition();
        void setVelX(float _velX);
        void setVelY(float _velY);
        void setSizeBlock(int _size);
        float getVelX();
        float getVelY();
        int getSizeBlock();
        
    private:
        bool initialize(string _name);        
        Size visibleSize;
        Vec2 noIsoPos;
        float velX;
        float velY;
        float oldY;
        int sizeBlock;

};

#endif
