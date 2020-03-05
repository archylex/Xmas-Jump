#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "IceBlock.h"
#include "Player.h"
#include "Toy.h"
#include "HeadLayer.h"
#include "BackgroundLayer.h"
#include "LineLayer.h"
#include "ClipObject.h"
#include "ui/CocosGUI.h"

using namespace ui;
using namespace cocos2d;

class HelloWorld : public Scene
{
public:
    static Scene* createScene();
    virtual bool init();
    virtual void update(float dt);
    virtual bool onTouchesBegan(Touch* touch, Event* event);    
    void pauseMyGame();
    void resumeMyGame();
    void lineCreater(int cc, int _id);
    void GameOver(float dt);
    void stopSounds();
    void startSounds();
    void ContinueGame();
    void removeSinkingPlayer(float dt);
    Size visibleSize;
    int score;
    int lineID;
    Player *player;
    BackgroundLayer *bglayer;
    HeadLayer *headlayer;
    Sprite *startBlock;
    vector<ClipObject*> sinkingPlayer;
    vector<LineLayer*> delLines;
    vector<LineLayer*> glines;
    bool isTouch;
    bool pauseMode;
    bool isGround;
    bool isYMoved;
    bool isGameOver;
    bool isHighScore;
    bool isContinue;
    bool isAddLine;
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
