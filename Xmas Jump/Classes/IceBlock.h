#ifndef __ICEBLOCK_H__
#define __ICEBLOCK_H__

#include <iostream>
#include "cocos2d.h"
#include "Isometry.h"
#include "ClipObject.h"

using namespace std;
using namespace cocos2d;

class IceBlock : public Node {
    public:
        static IceBlock *createMe(int _bsize, float _vel);
        void update(float dt);
        void setGamePosition(Vec2 _pos);
        void setVelocityX(float _velX);
        void setVelocityY(float _velY);
        float getVelocityX();
        float getVelocityY();
        int getSizeOfBlock();
        Vec2 getGamePosition();
        void rockBlock();
        
    private:
        bool initialize(int _bsize, float _vel);        
        Size visibleSize;
        Vec2 gamePos;
        int sizeOfBlock;
        float velX;
        float velY;
        float velZ;
        float oldY;
        double dgree;
        bool isRock;
        vector<Sprite*> blockArr;
        vector<ClipObject*> clipArr;

};

#endif
