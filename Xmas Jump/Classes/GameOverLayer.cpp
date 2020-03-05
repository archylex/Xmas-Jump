#include "GameOverLayer.h"
#include "HelloWorldScene.h"
#include "TitleScene.h"
#include "AddMob.h"

GameOverLayer::GameOverLayer() {
    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AddMob::showInterstitial();
    #endif

    // Screen size
    visibleSize = Director::getInstance()->getVisibleSize();

    auto fadeBGNode = DrawNode::create();
    Vec2 fadeBG[] = { Vec2(2*DELTA_X, 0), Vec2(2*DELTA_X, visibleSize.height), Vec2(visibleSize.width, visibleSize.height), Vec2(visibleSize.width, 0) };
    //Color4F aBlack(1.0f, 1.0f, 1.0f, 0.5f);
    Color4F aBlack(0.0f, 0.4f, 0.5f, 0.5f);
    fadeBGNode->drawPolygon(fadeBG, 4, aBlack, 0, aBlack);
    this->addChild(fadeBGNode);

    auto head = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("head.png"));
    head->setAnchorPoint(Vec2(0.5f, 1.0f));
    head->setPosition(Vec2(DELTA_X, visibleSize.height));
    this->addChild(head);

    auto logo = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("logo.png"));
    logo->setAnchorPoint(Vec2(0.5f, 0.5f));
    logo->setPosition(Vec2(DELTA_X, visibleSize.height*0.71f));
    this->addChild(logo);

    auto sScore = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("GOScore.png"));
    sScore->setAnchorPoint(Vec2(0.5f, 0.5f));
    sScore->setPosition(Vec2(DELTA_X, visibleSize.height*0.47f));
    this->addChild(sScore);

    // score label
    scoreLabel = Label::createWithBMFont("font.fnt", to_string(0));
    scoreLabel->setAnchorPoint(Vec2(0.5f,0.5f));
    scoreLabel->setPosition(Vec2(DELTA_X, visibleSize.height*0.405f));
    scoreLabel->setScale(0.7f);
    this->addChild(scoreLabel, 10);

    playButton = Button::create("PlayButton.png", "PlayButton.png", "PlayButton.png", Widget::TextureResType::PLIST);
    playButton->setAnchorPoint(Vec2(0.5f,0.5f));
    playButton->setPosition(Vec2( DELTA_X  , 0));
    playButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:
                auto scene = HelloWorld::createScene();
                Director::getInstance()->replaceScene(scene);
                break;
        }
    });
    this->addChild(playButton);

    // continue button
    continueButton = Button::create("ContinueButton.png", "ContinueButton.png", "ContinueButton.png", TextureResType::PLIST);
    continueButton->setAnchorPoint(Vec2(0.5f,0.5f));
    continueButton->setPosition(Vec2(2*DELTA_X, visibleSize.height*0.22f));
    continueButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:
                #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
                AddMob::showVideo();
                this->schedule(schedule_selector(GameOverLayer::updateStatusAdVideo), 0.5f);
                #endif                
                break;
        }
    });
    this->addChild(continueButton);

    // home button
    homeButton = Button::create("HomeButton.png", "HomeButton.png", "HomeButton.png", TextureResType::PLIST);
    homeButton->setAnchorPoint(Vec2(0.5f,0.5f));
    homeButton->setPosition(Vec2(0, visibleSize.height*0.22f));
    homeButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:
                auto scene = TitleScene::createScene();
                Director::getInstance()->replaceScene(scene);
                break;
        }
    });
    this->addChild(homeButton);

    auto playMove1 = MoveTo::create(0.2f, Vec2(DELTA_X  , visibleSize.height*0.22f+playButton->getContentSize().height/2));
    auto playMove2 = MoveTo::create(0.2f, Vec2(DELTA_X  , visibleSize.height*0.22f-playButton->getContentSize().height/2));
    auto playMove3 = MoveTo::create(0.2f, Vec2(DELTA_X  , visibleSize.height*0.22f ));
    auto pseq = Sequence::create(playMove1, playMove2, playMove3, nullptr);
    playButton->runAction(pseq);

    auto conMove1 = MoveTo::create(0.2f, Vec2(DELTA_X - playButton->getContentSize().width + continueButton->getContentSize().width/2, visibleSize.height*0.22f));
    auto conMove2 = MoveTo::create(0.2f, Vec2(DELTA_X - playButton->getContentSize().width - continueButton->getContentSize().width/2 , visibleSize.height*0.22f));
    auto conMove3 = MoveTo::create(0.2f, Vec2(DELTA_X - playButton->getContentSize().width, visibleSize.height*0.22f ));
    auto cseq = Sequence::create(conMove1, conMove2, conMove3, nullptr);
    continueButton->runAction(cseq);

    auto homeMove1 = MoveTo::create(0.2f, Vec2(DELTA_X + playButton->getContentSize().width - homeButton->getContentSize().width/2, visibleSize.height*0.22f));
    auto homeMove2 = MoveTo::create(0.2f, Vec2(DELTA_X + playButton->getContentSize().width + homeButton->getContentSize().width/2 , visibleSize.height*0.22f));
    auto homeMove3 = MoveTo::create(0.2f, Vec2(DELTA_X + playButton->getContentSize().width , visibleSize.height*0.22f));
    auto hseq = Sequence::create(homeMove1, homeMove2, homeMove3, nullptr);
    homeButton->runAction(hseq);
}

void GameOverLayer::setScore(int _score)
{
    scoreLabel->setString(to_string(_score));
}

void GameOverLayer::updateStatusAdVideo(float dt)
{
    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    if (AddMob::getIsFinalVideo())
    {
        this->unschedule(schedule_selector(GameOverLayer::updateStatusAdVideo));
        AddMob::resetIsFinalVideo();
        HelloWorld *game = (HelloWorld*)this->getParent();
        game->ContinueGame();
        this->removeFromParentAndCleanup(true);
    }
    #endif
}

