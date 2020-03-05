#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer() {
    // Screen size
    visibleSize = Director::getInstance()->getVisibleSize();

    // gradient
    Color4B nColor(71, 203, 241, 255);
    Color4B wColor(250, 250, 255, 255);
    auto seabg = LayerGradient::create(wColor, nColor);
    seabg->setAnchorPoint(Vec2(0.0f, 0.0f));
    seabg->setPosition(Vec2(DELTA_X - visibleSize.width/2,0));
    seabg->setVector(Point(1,-1));
    this->addChild(seabg);

    particleSystem = ParticleSystemQuad::create("sea.plist");
    particleSystem->setPosition(-200,100);
    this->addChild(particleSystem);
    particleSystem->setAutoRemoveOnFinish(true);

}

void BackgroundLayer::pauseBG() {
    particleSystem->pause();
}

void BackgroundLayer::resumeBG() {
    particleSystem->resume();
}



