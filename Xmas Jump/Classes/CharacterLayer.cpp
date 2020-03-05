#include "CharacterLayer.h"
#include "TitleScene.h"
#include "PublicVariables.h"

CharacterLayer::CharacterLayer() {
    // Screen size
    visibleSize = Director::getInstance()->getVisibleSize();

    charNum = 0;

    auto charFrame = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("emptyDot.png"));
    charFrame->setAnchorPoint(Vec2(0.5f, 0.5f));
    charFrame->setPosition(Vec2(visibleSize.width/2, visibleSize.height * 0.45f));
    this->addChild(charFrame);

    characterBefore = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(PublicVariables::Instance()->getCharacter()));
    characterBefore->setAnchorPoint(Vec2(0.5f, 0.5f));
    characterBefore->setPosition(Vec2(visibleSize.width/2, visibleSize.height * 0.45f));
    characterBefore->setScale(0.7f);
    this->addChild(characterBefore);

    // Pause button
    leftButton = Button::create("LeftButton.png", "LeftButton.png", "LeftButton.png", Widget::TextureResType::PLIST);
    leftButton->setAnchorPoint(Vec2(0.5f,0.5f));
    leftButton->setPosition(Vec2(visibleSize.width/2 - charFrame->getContentSize().width, visibleSize.height * 0.45f));
    leftButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:
                charNum--;
                if (charNum < 0)
                    charNum = 1;
                updateCharFrame();
                break;
        }
    });
    this->addChild(leftButton);

    rightButton = Button::create("RightButton.png", "RightButton.png", "RightButton.png", Widget::TextureResType::PLIST);
    rightButton->setAnchorPoint(Vec2(0.5f,0.5f));
    rightButton->setPosition(Vec2(visibleSize.width/2 + charFrame->getContentSize().width , visibleSize.height * 0.45f));
    rightButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:
                charNum++;
                if (charNum > 1)
                    charNum = 0;
                updateCharFrame();
                break;
        }
    });
    this->addChild(rightButton);


    // ok button
    auto okButton = Button::create("OkButton.png", "OkButton.png", "OkButton.png", TextureResType::PLIST);
    okButton->setAnchorPoint(Vec2(0.5f,0.5f));
    okButton->setPosition(Vec2(visibleSize.width * 0.64f, visibleSize.height * 0.3f));
    okButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:
                TitleScene *scene = (TitleScene*)this->getParent();
                scene->showMe();
                this->removeFromParentAndCleanup(true);
                break;
        }
    });
    this->addChild(okButton);

    // cancel button
    auto cancelButton = Button::create("CancelButton.png", "CancelButton.png", "CancelButton.png", TextureResType::PLIST);
    cancelButton->setAnchorPoint(Vec2(0.5f,0.5f));
    cancelButton->setPosition(Vec2(visibleSize.width * 0.36f, visibleSize.height * 0.3f));
    cancelButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:
                TitleScene *scene = (TitleScene*)this->getParent();
                scene->showMe();
                this->removeFromParentAndCleanup(true);
                break;
        }
    });
    this->addChild(cancelButton);
}

void CharacterLayer::updateCharFrame() {
    string fname = "";
    switch (charNum) {
        case 0:
            fname = "snowman.png";
            break;
        case 1:
            fname = "santa.png";
            break;
    }
    characterBefore->setSpriteFrame(fname);
    PublicVariables::Instance()->setCharacter(fname);
}





