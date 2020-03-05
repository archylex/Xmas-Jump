#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>  

using namespace cocos2d;
using namespace std;
using namespace ui;

class GameOverLayer : public Layer {
    public:
        GameOverLayer();
        void setScore(int _score);
                
    private:       
        Size visibleSize;
        Button *playButton;
        Button *homeButton;
        Button *continueButton;
        Label *scoreLabel;
        void updateStatusAdVideo(float dt);

};
