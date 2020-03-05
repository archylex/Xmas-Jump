#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#include <string>  


using namespace ui;
using namespace cocos2d;


class TitleScene : public Scene
{
public:
    static Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    void hideMe();
    void showMe();

private:
    Size visibleSize;
    Button *playButton;
    Button *soundButton;
    Button *musicButton;
    Button *quitButton;
    Button *characterButton;
    
    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);
};

#endif // __TITLE_SCENE_H__
