#include "HeadLayer.h"
#include "HelloWorldScene.h"

HeadLayer::HeadLayer() {
    // Screen size
    visibleSize = Director::getInstance()->getVisibleSize();

    head = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("head.png"));
    head->setAnchorPoint(Vec2(0.0f, 1.0f));
    head->setPosition(Vec2(2*DELTA_X, visibleSize.height));
    this->addChild(head);

    toysScore = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ToyScore.png"));
    toysScore->setAnchorPoint(Vec2(0.0f, 0.5f));
    toysScore->setPosition(Vec2(DELTA_X - visibleSize.width/2 + visibleSize.width/22, visibleSize.height - visibleSize.height/15 ));
    this->addChild(toysScore);

    // Pause button
    menuButton = Button::create("MenuButton.png", "MenuButton.png", "MenuButton.png", Widget::TextureResType::PLIST);
    menuButton->setAnchorPoint(Vec2(0.5f,0.5f));
    menuButton->setPosition(Vec2(DELTA_X + visibleSize.width/2 - visibleSize.width/8, visibleSize.height - visibleSize.height/16));
    menuButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:            
                HelloWorld *game = (HelloWorld*)this->getParent();
                game->pauseMyGame();
                break;
        }
    });
    this->addChild(menuButton);

    // score label
    scoreLabel = Label::createWithBMFont("font.fnt", "0");
    scoreLabel->setAnchorPoint(Vec2(0.0f,0.5f));
    scoreLabel->setPosition(Vec2(toysScore->getContentSize().width*0.4f, toysScore->getContentSize().height*0.47f));
    scoreLabel->setScale(0.45f);
    toysScore->addChild(scoreLabel, 10);

}

void HeadLayer::SetScore(int _score) {
    scoreLabel->setString(to_string(_score));
}

void HeadLayer::HideMe() {
    auto fadeHead = FadeOut::create(0.2f);
    head->runAction(fadeHead);

    auto fadeToys = FadeOut::create(0.1f);
    toysScore->runAction(fadeToys);

    auto fadeButton = FadeOut::create(0.2f);
    menuButton->runAction(fadeButton);

    auto fadeLabel = FadeOut::create(0.1f);
    scoreLabel->runAction(fadeLabel);
}

void HeadLayer::ShowMe() {
    auto fadeHead = FadeIn::create(0.2f);
    head->runAction(fadeHead);

    auto fadeToys = FadeIn::create(0.1f);
    toysScore->runAction(fadeToys);

    auto fadeButton = FadeIn::create(0.2f);
    menuButton->runAction(fadeButton);

    auto fadeLabel = FadeIn::create(0.1f);
    scoreLabel->runAction(fadeLabel);
}



