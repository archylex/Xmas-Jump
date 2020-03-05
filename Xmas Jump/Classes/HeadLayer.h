#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>  

#pragma once

using namespace cocos2d;
using namespace std;
using namespace ui;

class HeadLayer : public Layer {
    public:
        HeadLayer();
        void SetScore(int _score);
        void HideMe();
        void ShowMe();
                
    private:       
        Size visibleSize;
        Label *scoreLabel;
        Sprite *head;
        Sprite *toysScore;
        Button *menuButton;

};
