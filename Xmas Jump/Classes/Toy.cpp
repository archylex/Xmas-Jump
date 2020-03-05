#include "Toy.h"
#include "Isometry.h"
#include "PublicVariables.h"


Toy *Toy::create(string _name) {
    Toy *toy = new Toy();

    if(toy && toy->initialize(_name)) {
        toy->autorelease();
        return toy;
    }

    CC_SAFE_DELETE(toy);

    return nullptr;
}

bool Toy::initialize(string _name) {
    visibleSize = Director::getInstance()->getVisibleSize();

    auto spritecache = SpriteFrameCache::getInstance();

    this->setSpriteFrame(spritecache->getSpriteFrameByName(_name));

    this->setAnchorPoint(Vec2(0.5f, 0.0f));

    this->setPosition(Vec2(0.0f, -500.0f));

    noIsoPos = Vec2(0.0f, 0.0f);

    sizeBlock = 0;

    velX = 2.0f;
    velY = 0.0f;
    oldY = 0.0f;

    return true;
}

void Toy::setNoIsoPosition(Vec2 _pos) {
    if (velX < 0)
        noIsoPos.x = _pos.x + sizeBlock * PublicVariables::Instance()->getBlockSize() / 2;
    else
        noIsoPos.x = _pos.x - sizeBlock * PublicVariables::Instance()->getBlockSize() / 2;

    noIsoPos.y = _pos.y - PublicVariables::Instance()->getBlockSize() / 2;
}

Vec2 Toy::getNoIsoPosition() {
    return noIsoPos;
}

void Toy::update(float dt) {
    noIsoPos += Vec2(velX*dt, velY);

    if (velY > 0) {
        if (noIsoPos.y >= oldY + 2 * PublicVariables::Instance()->getBlockSize()) {
            velY = 0.0f;
            noIsoPos.y = oldY + 2 * PublicVariables::Instance()->getBlockSize();
        }
    }

    Vec2 isoPosition = Isometry::toIsometric(noIsoPos);

    this->setPosition(isoPosition);
}

void Toy::setVelY(float _velY) {
    oldY = noIsoPos.y;
    velY = _velY;
}

void Toy::setVelX(float _velX) {
    velX = _velX;
}

float Toy::getVelX() {
    return velX;
}

float Toy::getVelY() {
    return velY;
}

void Toy::setSizeBlock(int _size) {
    sizeBlock = _size;
}
