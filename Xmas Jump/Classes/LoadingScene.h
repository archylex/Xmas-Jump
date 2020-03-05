#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class LoadingScene : public Scene {
    public:
        virtual bool init();  
    	static Scene *createScene();
    	
    private:
        void loadSources(float dt);
        	
    CREATE_FUNC(LoadingScene)
};

#endif 
