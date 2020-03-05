#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "PublicVariables.h"
#include "MenuLayer.h"
#include "GameOverLayer.h"
#include "Isometry.h"

USING_NS_CC;

#define LAST_LINE 6

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if(PublicVariables::Instance()->getMusic())
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("theme.mp3", true);

    // Background layer
    bglayer = new BackgroundLayer();
    this->addChild(bglayer);

    isGround = false;
    isGameOver = false;
    isHighScore = false;
    score = 0;
    lineID = 0;
    pauseMode = false;

    auto camera = this->getDefaultCamera();    
    camera->setPositionX(PublicVariables::Instance()->getDeltaX());

    // start block
    startBlock = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block.png"));
    startBlock->setAnchorPoint(Vec2(0, 0.7f));
    startBlock->setPosition(Isometry::toIsometric(Vec2(visibleSize.width/2, PublicVariables::Instance()->getDeltaY() + 2 * PublicVariables::Instance()->getBlockSize())));
    this->addChild(startBlock);

    // player    
    player = Player::create(PublicVariables::Instance()->getCharacter());
    player->setNoIsoPosition(Vec2(visibleSize.width/2 + PublicVariables::Instance()->getBlockSize()/2, PublicVariables::Instance()->getDeltaY() + 1.5 * PublicVariables::Instance()->getBlockSize()));
    player->setVelX(0.0f);
    player->setVelY(0.0f);
    this->addChild(player, 7);

    // UI
    headlayer = new HeadLayer();
    this->addChild(headlayer, 30);

    // line layer    
    for (int cc = 0; cc < LAST_LINE; cc++)
    {
       lineCreater(cc, cc);
    }

    this->scheduleUpdate();

    // listener
    auto listenerT = EventListenerTouchOneByOne::create();
    listenerT->setSwallowTouches(true);
    listenerT->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerT, this);

    return true;
}

void HelloWorld::lineCreater(int cc, int _id)
{
    float lx;
    int velconf[] = {48, 96, 144, 192};
    int speed = velconf[rand() % int(sizeof(velconf)/sizeof(*velconf))];

    if (int(_id % 2))
    {
        speed *= -1;
        lx = 1.5f * float(visibleSize.width);
    } else {
        lx = -visibleSize.width/2;
    }

    auto *tline = new LineLayer();
    tline->setLineNumber(_id);
    tline->setLinePosition(Vec2(lx, PublicVariables::Instance()->getDeltaY() - cc * 2 * PublicVariables::Instance()->getBlockSize()));
    tline->setLineVelocity(speed);
    this->addChild(tline, 3);
    tline->getReady();
    glines.push_back(tline);
}

bool HelloWorld::onTouchesBegan(Touch *touch, Event *event) {
    if (!pauseMode) {
        if (!isTouch) {
            isTouch = true;
            isGround = false;
            player->setVelX(0.0f);
            player->setVelY(-5.0f);

            if (PublicVariables::Instance()->getSFX())
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump.mp3");
        }
    }

    return true;
}

void HelloWorld::update(float dt) {
    if(!pauseMode) {

        player->update(dt);

        for (auto &ll : glines)
        {            
            ll->update(dt);

            if (ll->getLinePosition().y > visibleSize.height + 2 * PublicVariables::Instance()->getBlockSize())
                delLines.push_back(ll);


            if (isTouch && lineID == ll->getLineNumber())
            {
                if (!isGameOver && player->isJumped() && !isGround && ll->didILand(player->getNoIsoPosition()))
                {
                    isGround = true;

                    player->rockMe();
                    player->setVelX(ll->getLineVelocity());

                    isAddLine = true;
                }
            }

            if (!isGameOver && isGround && ll->didIPickupToy(player->getNoIsoPosition()))
            {
                auto particleToy = ParticleSystemQuad::create("pickup.plist");
                particleToy->setPosition(Vec2(0, PublicVariables::Instance()->getBlockSize()/2));
                particleToy->setScale(0.37f);
                player->addChild(particleToy, 5);
                particleToy->setAutoRemoveOnFinish(true);

                score++;

                headlayer->SetScore(score);

                if (PublicVariables::Instance()->getSFX())
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pickup.mp3");

                if (!isHighScore && score > PublicVariables::Instance()->getHighScore())
                {
                    if (PublicVariables::Instance()->getSFX())
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("highscore.mp3");

                    isHighScore = true;

                    PublicVariables::Instance()->setHighScore(score);
                    UserDefault::getInstance()->setIntegerForKey("SCORES", score);
                    UserDefault::getInstance()->flush();
                }
            }

            if(isContinue && isTouch && ll->getLineNumber() == lineID - 1)
            {
                isContinue = false;
                ll->runAfterContinue();
            }

            ll->emptyTrash();
        }

        if (isAddLine)
        {
            lineCreater(LAST_LINE, lineID + LAST_LINE);
            lineID++;
            isAddLine = false;
        }

        if (!isGameOver && isTouch && !isYMoved && isGround && !player->getIsRock()) {
            player->setVelY(5.0f);

            if (lineID == 1) {
                auto mv = MoveTo::create(0.5f, Vec2(Isometry::toIsometric(Vec2(visibleSize.width/2 + PublicVariables::Instance()->getBlockSize()/2,
                                                                               PublicVariables::Instance()->getDeltaY() + 9.5*PublicVariables::Instance()->getBlockSize()))));
                startBlock->runAction(mv);
            }

            for (auto &ll : glines)
            {
                ll->setVelocityY(5.0f);
            }

            isYMoved = true;
        }

        if (!isGameOver && isYMoved && player->getVelY() <= 0.0f)
        {
            isYMoved = false;
            isTouch = false;
        }

        if (!isGameOver && isTouch && player->isJumped() && !isGround)
        {
            auto particleCircle = ParticleSystemQuad::create("circle.plist");
            particleCircle->setPosition(Vec2(player->getPosition().x, player->getPosition().y));
            particleCircle->setScale(0.37f);
            this->addChild(particleCircle, 1);
            particleCircle->setAutoRemoveOnFinish(true);

            isGameOver = true;
            player->setVisible(false);

            if (PublicVariables::Instance()->getSFX())
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("water.mp3");

            auto *cobj = ClipObject::create(1, 0);
            cobj->setPosition(player->getPosition());
            this->addChild(cobj, 1);
            sinkingPlayer.push_back(cobj);
            this->schedule(schedule_selector(HelloWorld::removeSinkingPlayer), 1);

            this->schedule(schedule_selector(HelloWorld::GameOver), 2.0f);
        }

        for (auto &sp : sinkingPlayer) {
            sp->update(dt);
        }

        if (delLines.size() > 0) {
            for (auto &dl : delLines)
            {
                glines.erase(std::remove(glines.begin(), glines.end(), dl), glines.end());
                this->removeChild(dl, true);
            }

            delLines.clear();
        }
    }
}

void HelloWorld::removeSinkingPlayer(float dt)
{
    for (auto &sp : sinkingPlayer) {
        this->removeChild(sp);
    }
    sinkingPlayer.clear();
}

void HelloWorld::ContinueGame() {
    if (lineID > 0)
    {
        headlayer->ShowMe();

        for (auto &ll : glines)
        {
            if (ll->getLineNumber() == lineID - 1)
            {
                ll->stopBeforeContinue();

                float dx = 1;

                if (ll->getLineVelocity() > 0)
                    dx = -1;

                Vec2 nwPos = ll->getPosStopBlock(200, 420);
                player->setNoIsoPosition(Vec2(nwPos.x + dx * PublicVariables::Instance()->getBlockSize()/2,
                                              nwPos.y - PublicVariables::Instance()->getBlockSize()/2));
                player->setVisible(true);
            }
        }

        isGround = false;
        isGameOver = false;
        pauseMode = false;
        isTouch = false;
        isContinue = true;

    } else {
        auto scene = HelloWorld::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}

void HelloWorld::GameOver(float dt) {
    this->unschedule(schedule_selector(HelloWorld::GameOver));

    isTouch = false;

    player->setVisible(false);

    headlayer->HideMe();

    if (isHighScore)
    {
        PublicVariables::Instance()->setHighScore(score);
        UserDefault::getInstance()->setIntegerForKey("SCORES", score);
        UserDefault::getInstance()->flush();
    }

    auto gameoverLayer = new GameOverLayer();
    gameoverLayer->setScore(score);
    this->addChild(gameoverLayer, 100);

    if (PublicVariables::Instance()->getSFX()) {
        stopSounds();
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("gameover.mp3");
    }

}

void HelloWorld::stopSounds() {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

void HelloWorld::startSounds() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("theme.mp3", true);
}

void HelloWorld::pauseMyGame() {
    if (!isGameOver && !pauseMode) {        
        bglayer->pauseBG();
        headlayer->HideMe();

        for (auto &ll : glines) {
            ll->pauseMe();
        }

        auto menulayer = new MenuLayer();
        this->addChild(menulayer, 100);

        pauseMode = true;
    }    
}

void HelloWorld::resumeMyGame() {    
    pauseMode = false;

    for (auto &ll : glines)
    {
        ll->resumeMe();
    }

    bglayer->resumeBG();
    headlayer->ShowMe();
}








