#include "cocos2d.h"
#include <string>  

#pragma once

#define DELTA_X -240

using namespace cocos2d;
using namespace std;

class BackgroundLayer : public Layer {
    public:
        BackgroundLayer();
        void pauseBG();
        void resumeBG();
                
    private:       
        Size visibleSize;
        ParticleSystemQuad *particleSystem;

};
