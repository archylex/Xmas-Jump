#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>  

using namespace cocos2d;
using namespace std;
using namespace ui;

class MenuLayer : public Layer {
    public:
        MenuLayer();
                
    private:       
        Size visibleSize;
        Button *soundButton;
        Button *musicButton;

};
