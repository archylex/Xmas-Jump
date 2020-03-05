#ifndef LINELAYER_H
#define LINELAYER_H

#include "cocos2d.h"
#include "math.h"
#include "IceBlock.h"
#include "Toy.h"

using namespace cocos2d;

class LineLayer : public Layer
{
public:
    LineLayer();
    void emptyTrash();
    void getReady();
    void resumeMe();
    void pauseMe();
    void setLinePosition(Vec2 _pos);
    Vec2 getLinePosition();
    void setLineVelocity(float _vel);
    float getLineVelocity();
    void setLineNumber(int _num);
    int getLineNumber();
    void runAfterContinue();
    void stopBeforeContinue();
    void update(float dt);
    bool didILand(Vec2 _npos);
    bool didIPickupToy(Vec2 _npos);
    void setVelocityY(float _vy);
    Vec2 getPosStopBlock(float _x0, float _x1);

private:
    void blockCreater(float dt);
    void startedBlocks();
    void decrementLastTimer(float dt);
    void createToy(Vec2 _pos, int _sizeBlock);
    void createBlock(int _type, Vec2 _pos);

    Size visibleSize;
    Vec2 myPosition;
    int myNumber;
    float myVelocity;
    float last_timer;
    vector<IceBlock*> myBlocks;
    vector<IceBlock*> delMyBlocks;
    vector<Toy*> myToys;
    vector<Toy*> delMyToys;
};

#endif // LINELAYER_H
