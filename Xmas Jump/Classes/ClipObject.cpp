#include "ClipObject.h"
#include "PublicVariables.h"

ClipObject *ClipObject::create(int _tObj, float _vel) {
    ClipObject *_cobj = new ClipObject();

    if(_cobj && _cobj->initialize(_tObj, _vel)) {
        _cobj->autorelease();
        return _cobj;
    }

    CC_SAFE_DELETE(_cobj);

    return nullptr;
}

bool ClipObject::initialize(int _tObj, float _vel) {
    tObj = _tObj;

    degree = 0;

    Vec2 pLine[6];

    sprite = Sprite::create();
    auto stencil = DrawNode::create();

    if (tObj)
    {
        sprite->setSpriteFrame(PublicVariables::Instance()->getCharacter());
        sprite->setAnchorPoint(Vec2(0.5f, 0.0f));

        pLine[0] = Vec2(- sprite->getContentSize().width/2, 0);
        pLine[1] = Vec2(- sprite->getContentSize().width/2, sprite->getContentSize().height);
        pLine[2] = Vec2(sprite->getContentSize().width/2, sprite->getContentSize().height);
        pLine[3] = Vec2(sprite->getContentSize().width/2, 0);

        stencil->drawPolygon(pLine, 4, Color4F::RED, 0, Color4F::RED);
    } else {
        sprite->setSpriteFrame("block.png");

        if (_vel < 0) {
            sprite->setAnchorPoint(Vec2(0.0f, 0.7f));

            pLine[0] = Vec2(0.0f, 0.0f);
            pLine[1] = Vec2(0.5f * sprite->getContentSize().width, 0.3f * sprite->getContentSize().height);
            pLine[2] = Vec2(sprite->getContentSize().width, 0.0f);
            pLine[3] = Vec2(sprite->getContentSize().width, - 0.4f * sprite->getContentSize().height);
            pLine[4] = Vec2(0.5f * sprite->getContentSize().width, - 0.7f * sprite->getContentSize().height);
            pLine[5] = Vec2(0, - 0.4f * sprite->getContentSize().height);
        } else {
            sprite->setAnchorPoint(Vec2(0.5f, 1.0f));

            pLine[0] = Vec2(-0.5f * sprite->getContentSize().width, -0.3f * sprite->getContentSize().height);
            pLine[1] = Vec2(0, 0);
            pLine[2] = Vec2(0.5f * sprite->getContentSize().width, -0.3f * sprite->getContentSize().height);
            pLine[3] = Vec2(0.5f * sprite->getContentSize().width, -0.7f * sprite->getContentSize().height);
            pLine[4] = Vec2(0, -sprite->getContentSize().height);
            pLine[5] = Vec2(-0.5f * sprite->getContentSize().width, -0.7f * sprite->getContentSize().height);

        }

        stencil->drawPolygon(pLine, 6, Color4F::RED, 0, Color4F::RED);
    }

    this->setStencil(stencil);

    this->addChild(sprite);

    return true;
}

void ClipObject::setDegree(double _deg)
{
    degree = _deg;
}

void ClipObject::update(float dt) {
    if (tObj) {
        sprite->setPosition(sprite->getPosition().x, sprite->getPosition().y - 12.0f);
    } else {
        sprite->setPosition(sprite->getPosition().x, sprite->getPosition().y - float(200 * sin(degree * 3.14 / 180)) * dt);
    }
}

