#include "LoadingScene.h"
#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "PublicVariables.h"


// Create Loading scene
Scene* LoadingScene::createScene() {
    return LoadingScene::create();
}

// Initialize scene
bool LoadingScene::init() {
    // Screen size
    auto visibleSize = Director::getInstance()->getVisibleSize();

    PublicVariables::Instance()->setDeltaX(-1 * visibleSize.width/2);
    PublicVariables::Instance()->setDeltaY(visibleSize.height * 0.64f);

    auto fadeBGNode = DrawNode::create();
    Vec2 fadeBG[] = { Vec2(0, 0), Vec2(0, visibleSize.height), Vec2(visibleSize.width, visibleSize.height), Vec2(visibleSize.width, 0) };
    Color4F aW(1.0f, 1.0f, 1.0f, 1.0f);
    fadeBGNode->drawPolygon(fadeBG, 4, aW, 0, aW);
    this->addChild(fadeBGNode);

    // First circle sprite
    auto cOne = Sprite::create("snowflake.png");
    cOne->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(cOne);
    auto animOne = RotateBy::create(2.0f, Vec3(0.0f, 0.0f, 360.0f));
    cOne->runAction(RepeatForever::create(animOne));

    // Get load
    this->schedule(schedule_selector(LoadingScene::loadSources), 0.5f);

    return true;
}

void LoadingScene::loadSources(float dt) {
    // Unschedule
    this->unschedule(schedule_selector(LoadingScene::loadSources));

    // Loading sprites
    auto spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("sprites.plist");

    // Get audio engine instance
    auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

    // Loading music
    audioEngine->preloadBackgroundMusic("theme.mp3");

    // Loading pick up sound
    audioEngine->preloadEffect("pickup.mp3");

    // Loading click sound
    audioEngine->preloadEffect("click.mp3");

    // Loading high score sound
    audioEngine->preloadEffect("highscore.mp3");

    // Loading jump sound
    audioEngine->preloadEffect("jump.mp3");

    // Loading water sound
    audioEngine->preloadEffect("water.mp3");

    // Loading Game over
    audioEngine->preloadEffect("gameover.mp3");


    // Loading high score and set to public variable    
    PublicVariables::Instance()->setHighScore(UserDefault::getInstance()->getIntegerForKey("SCORES", 0));

    // Loading sound option and set to public variable
    PublicVariables::Instance()->setSFX(UserDefault::getInstance()->getBoolForKey("SFX", true));

    // Loading music option and set to public variable
    PublicVariables::Instance()->setMusic(UserDefault::getInstance()->getBoolForKey("MUSIC", true));

    // Go to main menu scene
    Scene *myScene = TitleScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(255, 255, 255)));
}

