#include "IceBlock.h"
#include "PublicVariables.h"

IceBlock *IceBlock::createMe(int _bsize, float _vel) {
    IceBlock *_iblock = new IceBlock();

    if(_iblock && _iblock->initialize(_bsize, _vel)) {
        _iblock->autorelease();
        _iblock->setTag(2);
        return _iblock;
    }

    CC_SAFE_DELETE(_iblock);

    return nullptr;
}

bool IceBlock::initialize(int _bsize, float _vel) {
    visibleSize = Director::getInstance()->getVisibleSize();

    velX = _vel;
    velY = 0.0f;
    oldY = 0.0f;
    gamePos = Vec2(0.0f, 0.0f);
    sizeOfBlock = _bsize;
    isRock = false;

    string fname = "block.png";

    if (velX < 0)
    {
        for (int c = sizeOfBlock-1; c >= 0; c--) {
            auto ablock = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(fname));
            ablock->setAnchorPoint(Vec2(0, 0.7f));
            ablock->setPosition(Isometry::toIsometric(Vec2(c * PublicVariables::Instance()->getBlockSize(), 0)));
            this->addChild(ablock);
            blockArr.push_back(ablock);
        }
    } else {
        for (int c = 0; c < sizeOfBlock; c++) {
            auto ablock = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(fname));
            ablock->setAnchorPoint(Vec2(0.5f, 1.0f));
            ablock->setPosition(Isometry::toIsometric(Vec2(-1 * c * PublicVariables::Instance()->getBlockSize(), 0)));
            this->addChild(ablock);
            blockArr.push_back(ablock);
        }
    }

    return true;
}

void IceBlock::setVelocityY(float _velY) {
    oldY = gamePos.y;
    velY = _velY;
}

void IceBlock::setVelocityX(float _velX) {
    velX = _velX;
}

float IceBlock::getVelocityX() {
    return velX;
}

float IceBlock::getVelocityY() {
    return velY;
}

void IceBlock::setGamePosition(Vec2 _pos) {
    gamePos = _pos;
}

Vec2 IceBlock::getGamePosition() {
    return gamePos;
}

int IceBlock::getSizeOfBlock() {
    return sizeOfBlock;
}

void IceBlock::rockBlock() {
    isRock = true;

    for (auto &rb : blockArr)
    {
        rb->setVisible(false);

        ClipObject *cObj = ClipObject::create(0, velX);
        cObj->setPosition(rb->getPosition());
        this->addChild(cObj);
        clipArr.push_back(cObj);
    }
}

void IceBlock::update(float dt) {    
    gamePos += Vec2(velX * dt, velY);

    if (velY > 0)
    {
        if (gamePos.y >= oldY + 2 * PublicVariables::Instance()->getBlockSize()) {
            velY = 0.0f;
            gamePos.y = oldY + 2 * PublicVariables::Instance()->getBlockSize();
        }
    }

    if (isRock)
    {
        dgree += 30;

        if (dgree >= 360) {
            dgree = 0;

            isRock = false;

            for (auto &rb : blockArr)
            {
                rb->setVisible(true);
            }

            for (auto &cb : clipArr)
            {
                this->removeChild(cb);
            }
            clipArr.clear();
        }
    }

    for (auto &cb : clipArr)
    {
        cb->setDegree(dgree);
        cb->update(dt);
    }

    Vec2 isoPos = Isometry::toIsometric(gamePos);
    this->setPosition(isoPos);
}

