#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "PublicVariables.h"
#include "CharacterLayer.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    return TitleScene::create();
}

bool TitleScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Background
    auto bg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("TitleBackground.png"));
    bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(bg);

    // score label
    auto scoreLabel = Label::createWithBMFont("font.fnt", to_string(PublicVariables::Instance()->getHighScore()));
    scoreLabel->setAnchorPoint(Vec2(0.5f,0.5f));
    scoreLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.92f));
    scoreLabel->setScale(0.65f);
    this->addChild(scoreLabel, 10);

    auto particleSystem = ParticleSystemQuad::create("snow.plist");
    particleSystem->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(particleSystem);
    particleSystem->setAutoRemoveOnFinish(true);

    auto logo = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("logo.png"));
    logo->setPosition(Vec2(visibleSize.width/2, visibleSize.height * 0.7f));
    this->addChild(logo);

    playButton = Button::create("PlayButton.png", "PlayButton.png", "PlayButton.png", Widget::TextureResType::PLIST);
    playButton->setAnchorPoint(Vec2(0.5f,0.5f));
    playButton->setPosition(Vec2(visibleSize.width/2, -playButton->getContentSize().height));
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

                auto scene = HelloWorld::createScene();
                Director::getInstance()->replaceScene(scene);
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
    musicButton->setPosition(Vec2(-musicButton->getContentSize().width, visibleSize.height * 0.45f));
    musicButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
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

                if (PublicVariables::Instance()->getMusic()) {
                    musicButton->loadTextures("MusicOffButton.png", "MusicOffButton.png", "MusicOffButton.png", TextureResType::PLIST);
                    PublicVariables::Instance()->setMusic(false);
                    UserDefault::getInstance()->setBoolForKey("MUSIC", false);
                } else {
                    musicButton->loadTextures("MusicOnButton.png", "MusicOnButton.png", "MusicOnButton.png", TextureResType::PLIST);
                    PublicVariables::Instance()->setMusic(true);
                    UserDefault::getInstance()->setBoolForKey("MUSIC", true);
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
    soundButton->setPosition(Vec2(visibleSize.width + soundButton->getContentSize().width, visibleSize.height * 0.45f));
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

    // quit button
    quitButton = Button::create("QuitButton.png", "QuitButton.png", "QuitButton.png", TextureResType::PLIST);
    quitButton->setAnchorPoint(Vec2(0.5f,0.5f));
    quitButton->setPosition(Vec2(visibleSize.width, 0));
    quitButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
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
                Director::getInstance()->end();

                #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                exit(0);
                #endif
                break;
        }
    });
    this->addChild(quitButton);

    // character button
    characterButton = Button::create("CharacterButton.png", "CharacterButton.png", "CharacterButton.png", TextureResType::PLIST);
    characterButton->setAnchorPoint(Vec2(0.5f,0.5f));
    characterButton->setPosition(Vec2(0.0f, 0.0f));
    characterButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
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

                hideMe();
                auto characterLayer = new CharacterLayer();
                this->addChild(characterLayer);
                break;
        }
    });
    this->addChild(characterButton);

    auto playMove1 = MoveTo::create(0.2f, Vec2(visibleSize.width/2  , visibleSize.height * 0.45f + visibleSize.height/10));
    auto playMove2 = MoveTo::create(0.2f, Vec2(visibleSize.width/2  , visibleSize.height * 0.45f - visibleSize.height/20));
    auto playMove3 = MoveTo::create(0.2f, Vec2(visibleSize.width/2  , visibleSize.height * 0.45f ));
    auto pseq = Sequence::create(playMove1, playMove2, playMove3, nullptr);
    playButton->runAction(pseq);

    auto musicMove1 = MoveTo::create(0.2f, Vec2(visibleSize.width/2 - playButton->getContentSize().width + musicButton->getContentSize().width/2, visibleSize.height * 0.45f));
    auto musicMove2 = MoveTo::create(0.2f, Vec2(visibleSize.width/2 - playButton->getContentSize().width - musicButton->getContentSize().width/2 , visibleSize.height * 0.45f));
    auto musicMove3 = MoveTo::create(0.2f, Vec2(visibleSize.width/2 - playButton->getContentSize().width, visibleSize.height * 0.45f ));
    auto mseq = Sequence::create(musicMove1, musicMove2, musicMove3, nullptr);
    musicButton->runAction(mseq);

    auto soundMove1 = MoveTo::create(0.2f, Vec2(visibleSize.width/2 + playButton->getContentSize().width - soundButton->getContentSize().width/2, visibleSize.height * 0.45f));
    auto soundMove2 = MoveTo::create(0.2f, Vec2(visibleSize.width/2 + playButton->getContentSize().width + soundButton->getContentSize().width/2 , visibleSize.height * 0.45f));
    auto soundMove3 = MoveTo::create(0.2f, Vec2(visibleSize.width/2 + playButton->getContentSize().width , visibleSize.height * 0.45f));
    auto sseq = Sequence::create(soundMove1, soundMove2, soundMove3, nullptr);
    soundButton->runAction(sseq);

    auto quitMove1 = MoveTo::create(0.2f, Vec2(visibleSize.width * 0.64f - quitButton->getContentSize().width/2, visibleSize.height * 0.3f + quitButton->getContentSize().height/2));
    auto quitMove2 = MoveTo::create(0.2f, Vec2(visibleSize.width * 0.64f + quitButton->getContentSize().width/2, visibleSize.height * 0.3f - quitButton->getContentSize().height/2));
    auto quitMove3 = MoveTo::create(0.2f, Vec2(visibleSize.width * 0.64f, visibleSize.height * 0.3f));
    auto qseq = Sequence::create(quitMove1, quitMove2, quitMove3, nullptr);
    quitButton->runAction(qseq);

    auto chMove1 = MoveTo::create(0.2f, Vec2(visibleSize.width * 0.36f + characterButton->getContentSize().width/2, visibleSize.height * 0.3f + characterButton->getContentSize().height/2));
    auto chMove2 = MoveTo::create(0.2f, Vec2(visibleSize.width * 0.36f - characterButton->getContentSize().width/2, visibleSize.height * 0.3f - characterButton->getContentSize().height/2));
    auto chMove3 = MoveTo::create(0.2f, Vec2(visibleSize.width * 0.36f, visibleSize.height * 0.3f));
    auto cseq = Sequence::create(chMove1, chMove2, chMove3, nullptr);
    characterButton->runAction(cseq);

    return true;
}

void TitleScene::hideMe()
{
    playButton->setEnabled(false);
    soundButton->setEnabled(false);
    musicButton->setEnabled(false);
    quitButton->setEnabled(false);
    characterButton->setEnabled(false);
}

void TitleScene::showMe()
{
    playButton->setEnabled(true);
    soundButton->setEnabled(true);
    musicButton->setEnabled(true);
    quitButton->setEnabled(true);
    characterButton->setEnabled(true);
}

void TitleScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


