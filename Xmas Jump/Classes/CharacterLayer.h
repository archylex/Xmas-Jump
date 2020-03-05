#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>  

#pragma once

using namespace cocos2d;
using namespace std;
using namespace ui;

class CharacterLayer : public Layer {
    public:
        CharacterLayer();
                
    private:       
        Size visibleSize;
        Sprite *characterAfter;
        Sprite *characterBefore;
        Button *leftButton;
        Button *rightButton;
        int charNum;
        void updateCharFrame();
};
