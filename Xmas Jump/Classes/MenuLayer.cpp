#include "MenuLayer.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "PublicVariables.h"

MenuLayer::MenuLayer() {
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
    logo->setPosition(Vec2(DELTA_X, visibleSize.height*0.7f));
    this->addChild(logo);

    auto playButton = Button::create("PlayButton.png", "PlayButton.png", "PlayButton.png", Widget::TextureResType::PLIST);
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
                if (PublicVariables::Instance()->getSFX())
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("click.mp3");

                HelloWorld *game = (HelloWorld*)this->getParent();
                game->resumeMyGame();
                this->removeFromParentAndCleanup(true);
                break;
        }
    });
    this->addChild(playButton);

    // music button
    string muspic = "MusicOnButton.png";
    if (!PublicVariables::Instance()->getMusic())
        muspic = "MusicOffButton.png";

    musicButton = Button::create(muspic, muspic, muspic, TextureResType::PLIST);
    musicButton->setAnchorPoint(Vec2(0.5f,0.5f));
    musicButton->setPosition(Vec2(2*DELTA_X, visibleSize.height/2));
    musicButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:                
                HelloWorld *game = (HelloWorld*)this->getParent();

                if (PublicVariables::Instance()->getSFX())
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("click.mp3");

                if (PublicVariables::Instance()->getMusic()) {
                    musicButton->loadTextures("MusicOffButton.png", "MusicOffButton.png", "MusicOffButton.png", TextureResType::PLIST);
                    PublicVariables::Instance()->setMusic(false);
                    UserDefault::getInstance()->setBoolForKey("MUSIC", false);
                    game->stopSounds();
                } else {
                    musicButton->loadTextures("MusicOnButton.png", "MusicOnButton.png", "MusicOnButton.png", TextureResType::PLIST);
                    PublicVariables::Instance()->setMusic(true);
                    UserDefault::getInstance()->setBoolForKey("MUSIC", true);
                    game->startSounds();
                }
                UserDefault::getInstance()->flush();
                break;
        }
    });
    this->addChild(musicButton);

    // sound button
    string sfxpic = "SoundOnButton.png";
    if (!PublicVariables::Instance()->getSFX())
        sfxpic = "SoundOffButton.png";

    soundButton = Button::create(sfxpic, sfxpic, sfxpic, TextureResType::PLIST);
    soundButton->setAnchorPoint(Vec2(0.5f,0.5f));
    soundButton->setPosition(Vec2(0, visibleSize.height/2));
    soundButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:
                if (PublicVariables::Instance()->getSFX())
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("click.mp3");

                if (PublicVariables::Instance()->getSFX()) {
                    soundButton->loadTextures("SoundOffButton.png", "SoundOffButton.png", "SoundOffButton.png", TextureResType::PLIST);
                    PublicVariables::Instance()->setSFX(false);
                    UserDefault::getInstance()->setBoolForKey("SFX", false);
                } else {
                    soundButton->loadTextures("SoundOnButton.png", "SoundOnButton.png", "SoundOnButton.png", TextureResType::PLIST);
                    PublicVariables::Instance()->setSFX(true);
                    UserDefault::getInstance()->setBoolForKey("SFX", true);
                }
                UserDefault::getInstance()->flush();
                break;
        }
    });
    this->addChild(soundButton);

    // home button
    auto homeButton = Button::create("HomeButton.png", "HomeButton.png", "HomeButton.png", TextureResType::PLIST);
    homeButton->setAnchorPoint(Vec2(0.5f,0.5f));
    homeButton->setPosition(Vec2(DELTA_X, visibleSize.height*0.43f - playButton->getContentSize().height));
    homeButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:
                if (PublicVariables::Instance()->getSFX())
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                HelloWorld *game = (HelloWorld*)this->getParent();
                game->stopSounds();
                auto scene = TitleScene::createScene();
                Director::getInstance()->replaceScene(scene);
                break;
        }
    });
    this->addChild(homeButton);

    // s
    auto dotOne = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("emptyDot.png"));
    dotOne->setPosition(Vec2(2*DELTA_X + visibleSize.width * 0.3f, visibleSize.height * 0.31f));
    dotOne->setScale(0.5f);
    dotOne->setOpacity(0);
    this->addChild(dotOne);

    auto dotTwo = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("emptyDot.png"));
    dotTwo->setPosition(Vec2(2*DELTA_X + visibleSize.width - visibleSize.width * 0.3f, visibleSize.height * 0.31f));
    dotTwo->setScale(0.5f);
    dotTwo->setOpacity(0);
    this->addChild(dotTwo);

    auto playMove1 = MoveTo::create(0.2f, Vec2(DELTA_X  , visibleSize.height*0.43f+visibleSize.height/10));
    auto playMove2 = MoveTo::create(0.2f, Vec2(DELTA_X  , visibleSize.height*0.43f-visibleSize.height/20));
    auto playMove3 = MoveTo::create(0.2f, Vec2(DELTA_X  , visibleSize.height*0.43f ));
    auto pseq = Sequence::create(playMove1, playMove2, playMove3, nullptr);
    playButton->runAction(pseq);

    auto musicMove1 = MoveTo::create(0.2f, Vec2(DELTA_X - playButton->getContentSize().width + musicButton->getContentSize().width/2, visibleSize.height*0.43f));
    auto musicMove2 = MoveTo::create(0.2f, Vec2(DELTA_X - playButton->getContentSize().width - musicButton->getContentSize().width/2 , visibleSize.height*0.43f));
    auto musicMove3 = MoveTo::create(0.2f, Vec2(DELTA_X - playButton->getContentSize().width, visibleSize.height*0.43f ));
    auto mseq = Sequence::create(musicMove1, musicMove2, musicMove3, nullptr);
    musicButton->runAction(mseq);

    auto soundMove1 = MoveTo::create(0.2f, Vec2(DELTA_X + playButton->getContentSize().width - musicButton->getContentSize().width/2, visibleSize.height*0.43f));
    auto soundMove2 = MoveTo::create(0.2f, Vec2(DELTA_X + playButton->getContentSize().width + musicButton->getContentSize().width/2 , visibleSize.height*0.43f));
    auto soundMove3 = MoveTo::create(0.2f, Vec2(DELTA_X + playButton->getContentSize().width , visibleSize.height*0.43f));
    auto sseq = Sequence::create(soundMove1, soundMove2, soundMove3, nullptr);
    soundButton->runAction(sseq);

    auto homeMove1 = MoveTo::create(0.2f, Vec2(DELTA_X  , visibleSize.height*0.43f - playButton->getContentSize().height+playButton->getContentSize().height/2));
    auto homeMove2 = MoveTo::create(0.2f, Vec2(DELTA_X  , visibleSize.height*0.43f - playButton->getContentSize().height-playButton->getContentSize().height/2));
    auto homeMove3 = MoveTo::create(0.2f, Vec2(DELTA_X, visibleSize.height*0.43f - playButton->getContentSize().height));
    auto hseq = Sequence::create(homeMove1, homeMove2, homeMove3, nullptr);
    homeButton->runAction(hseq);

    auto fadeOne = FadeIn::create(0.5f);
    dotOne->runAction(fadeOne);

    auto fadeTwo = FadeIn::create(0.5f);
    dotTwo->runAction(fadeTwo);
}



