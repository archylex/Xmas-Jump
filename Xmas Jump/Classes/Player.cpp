#include "Player.h"
#include "Isometry.h"
#include "PublicVariables.h"

Player *Player::create(string _name) {
    Player *player = new Player();

    if(player && player->initialize(_name)) {
        player->autorelease();
        player->setTag(1);
        return player;
    }

    CC_SAFE_DELETE(player);

    return nullptr;
}

bool Player::initialize(string _name) {
    visibleSize = Director::getInstance()->getVisibleSize();

    plfront = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_name));
    plfront->setAnchorPoint(Vec2(0.5f, 0.0f));
    this->addChild(plfront, 3);

    shadow = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("shadow.png"));
    shadow->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->addChild(shadow, 1);

    velX = 0.0f;
    velY = 0.0f;
    jdgree = 0.0;
    dgree = 0.0;

    jumpFinished = false;

    noIsoPos = Vec2(0.0f, 0.0f);

    return true;
}

void Player::setVelY(float _velY) {
    oldY = noIsoPos.y;
    velY = _velY;
}

void Player::setVelX(float _velX) {
    velX = _velX;
}

float Player::getVelX() {
    return velX;
}

float Player::getVelY() {
    return velY;
}

void Player::setNoIsoPosition(Vec2 _pos) {
    noIsoPos = _pos;
}

Vec2 Player::getNoIsoPosition() {
    return noIsoPos;
}

bool Player::isJumped() {
    return jumpFinished;
}

void Player::rockMe() {
    isRock = true;
}

bool Player::getIsRock() {
    return isRock;
}

void Player::update(float dt) {    
    noIsoPos += Vec2(velX * dt, velY);

    if (velY < 0.0f) {
        jumpFinished = false;

        jdgree += 360.0 / double(2 * PublicVariables::Instance()->getBlockSize() / abs(velY));

        if (jdgree >= 360)
            jdgree = 0.0;

        velZ += 350 * float(sin(jdgree * PI / 180)) * dt;
    }


    if (velY < 0.0f && noIsoPos.y <= oldY - 2 * PublicVariables::Instance()->getBlockSize())
    {
        velY = 0.0f;
        jdgree = 0.0;
        velZ = 0.0f;
        noIsoPos.y = oldY - 2 * PublicVariables::Instance()->getBlockSize();
        jumpFinished = true;        
    }

    if (velY > 0.0f && noIsoPos.y >= oldY + 2 * PublicVariables::Instance()->getBlockSize()) {
        velY = 0.0f;
        noIsoPos.y = oldY + 2 * PublicVariables::Instance()->getBlockSize();
    }

    Vec2 isoPos = Isometry::toIsometric(noIsoPos);

    if (!jumpFinished)
        plfront->setPosition(Vec2(0, velZ));

    if (isRock)
    {
        dgree += 30;

        if (dgree >= 360) {
            dgree = 0.0;
            velZ = 0.0f;
            isRock = false;
        }

        velZ -= 200 * float(sin(dgree * PI / 180)) * dt;

        shadow->setPosition(Vec2(0, velZ));
        plfront->setPosition(Vec2(0, velZ));
    }

    this->setPosition(isoPos);
}
