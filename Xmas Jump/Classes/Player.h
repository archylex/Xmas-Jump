#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Player : public Node {
    public:
        static Player *create(string _name);   
        void update(float dt);
        void setNoIsoPosition(Vec2 _pos);
        void setVelX(float _velX);
        void setVelY(float _velY);
        float getVelX();
        float getVelY();
        Vec2 getNoIsoPosition();     
        bool isJumped();
        void rockMe();
        bool getIsRock();
                
    private:
        bool initialize(string _name);   
        Size visibleSize;
        Vec2 noIsoPos;
        int sizeBlock;
        float velX;
        float velY;
        float velZ;
        float oldY;
        double jdgree;
        bool jumpFinished;
        bool isRock;
        double dgree;
        Sprite *shadow;
        Sprite *plfront;
        
};

#endif
