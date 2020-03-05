#include "LineLayer.h"
#include "PublicVariables.h"

#define DECR_TIME 0.1

LineLayer::LineLayer()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    last_timer = 0.1f;
}

void LineLayer::setLinePosition(Vec2 _pos)
{
    myPosition = _pos;
}

Vec2 LineLayer::getLinePosition()
{
    return myPosition;
}

void LineLayer::setLineVelocity(float _vel)
{
    myVelocity = _vel;
}

float LineLayer::getLineVelocity()
{
    return myVelocity;
}

void LineLayer::setLineNumber(int _num)
{
    myNumber = _num;
}

int LineLayer::getLineNumber()
{
    return myNumber;
}

void LineLayer::setVelocityY(float _vy)
{
    for (auto &b : myBlocks)
    {
        b->setVelocityY(_vy);
    }

    for (auto &t : myToys)
    {
        t->setVelY(_vy);
    }

    myPosition = Vec2(myPosition.x, myPosition.y + 2 * PublicVariables::Instance()->getBlockSize());
}

void LineLayer::startedBlocks()
{
    float line_length = 0.0f;

    for (int x = 0; x < 7; x++)
    {
        int _type = rand() % 3;
        int _typeDistance = rand() % 3;
        line_length += (_type + _typeDistance + 2) * PublicVariables::Instance()->getBlockSize();

        Vec2 nPos(0.0f, 0.0f);

        if (myVelocity > 0)
            nPos = Vec2(myPosition.x + line_length, myPosition.y);
        else
            nPos = Vec2(myPosition.x - line_length, myPosition.y);

        createBlock(_type, nPos);
    }
}

void LineLayer::blockCreater(float dt)
{
    float new_time = 0.0f;

    int _type = rand()%3;
    int _typeDistance = rand() % 3;
    new_time = (_type + _typeDistance + 2) * PublicVariables::Instance()->getBlockSize() / abs(myVelocity);

    createBlock(_type, myPosition);

    this->unschedule(schedule_selector(LineLayer::blockCreater));
    this->unschedule(schedule_selector(LineLayer::decrementLastTimer));

    this->schedule(schedule_selector(LineLayer::blockCreater), new_time);

    last_timer = new_time;

    this->schedule(schedule_selector(LineLayer::decrementLastTimer), 0.1f);
}

void LineLayer::createBlock(int _type, Vec2 _pos)
{
    auto ablock = IceBlock::createMe(_type+1, myVelocity);
    ablock->setGamePosition(_pos);
    this->addChild(ablock, 1);
    myBlocks.push_back(ablock);
    createToy(_pos, _type+1);
}

void LineLayer::createToy(Vec2 _pos, int _sizeBlock)
{
    if (1 == rand()%3)
    {
        string filename[] = {"blueball.png", "redball.png", "candy.png", "bell.png", "leaves.png"};

        auto atoy = Toy::create(filename[rand()%int(sizeof(filename)/sizeof(*filename))]);

        if (atoy != nullptr)
        {
            atoy->setVelX(myVelocity);
            atoy->setSizeBlock(_sizeBlock);
            atoy->setNoIsoPosition(_pos);
            this->addChild(atoy, 2);
            myToys.push_back(atoy);
        }
    }
}

void LineLayer::decrementLastTimer(float dt)
{
    last_timer -= 0.1f;

    if (last_timer <= 0)
        last_timer = 0.1f;
}

void LineLayer::emptyTrash()
{
    // delete
    if (!delMyBlocks.empty()) {
        for (auto &db : delMyBlocks) {
            myBlocks.erase(std::remove(myBlocks.begin(), myBlocks.end(), db), myBlocks.end());
            this->removeChild(db);
        }
        delMyBlocks.clear();
    }

    if (!delMyToys.empty()) {
        for (auto &dt : delMyToys) {
            myToys.erase(std::remove(myToys.begin(), myToys.end(), dt), myToys.end());
            this->removeChild(dt);
        }
        delMyToys.clear();
    }
}

void LineLayer::update(float dt)
{
    for (auto &b : myBlocks)
    {
        b->update(dt);

        if ((myVelocity > 0 && b->getGamePosition().x > 1.5f * visibleSize.width + 3*PublicVariables::Instance()->getBlockSize()) ||
                (myVelocity < 0 && b->getGamePosition().x < -visibleSize.width/2 - 3*PublicVariables::Instance()->getBlockSize()))
        {
            delMyBlocks.push_back(b);
        }
    }

    for (auto &t : myToys)
    {
        t->update(dt);

        if ((myVelocity > 0 && t->getNoIsoPosition().x >= 1.5f * visibleSize.width - PublicVariables::Instance()->getBlockSize()) ||
                (myVelocity < 0 && t->getNoIsoPosition().x <= -visibleSize.width/2 + PublicVariables::Instance()->getBlockSize()))
        {
            delMyToys.push_back(t);
        }
    }

    emptyTrash();
}

bool LineLayer::didILand(Vec2 _npos)
{
    for (auto &b : myBlocks)
    {
        if (myVelocity < 0)
        {
            if (_npos.x > b->getGamePosition().x + PublicVariables::Instance()->getBlockSize()/8 &&
                    _npos.x < b->getGamePosition().x + b->getSizeOfBlock() * PublicVariables::Instance()->getBlockSize())
            {
                b->rockBlock();
                return true;
            }
        } else {
            if (_npos.x < b->getGamePosition().x - PublicVariables::Instance()->getBlockSize()/8 &&
                    _npos.x > b->getGamePosition().x - b->getSizeOfBlock() * PublicVariables::Instance()->getBlockSize())
            {
                b->rockBlock();
                return true;
            }
        }
    }

    return false;
}

bool LineLayer::didIPickupToy(Vec2 _npos)
{
    for (auto &t : myToys)
    {
        if (fabs(t->getNoIsoPosition().x - _npos.x) <=  t->getContentSize().width &&
                fabs(_npos.y - t->getNoIsoPosition().y) <= 0.1f)
        {
            delMyToys.push_back(t);
            return true;
        }
    }

    return false;
}

Vec2 LineLayer::getPosStopBlock(float _x0, float _x1)
{
    for (auto &b : myBlocks)
    {
        if (b->getGamePosition().x > _x0 && b->getGamePosition().x < _x1)
            return b->getGamePosition();
    }

    return Vec2(0, 0);
}

void LineLayer::getReady()
{
    startedBlocks();
    resumeMe();
}

void LineLayer::resumeMe()
{
    this->schedule(schedule_selector(LineLayer::blockCreater), last_timer);
}

void LineLayer::pauseMe()
{
    this->unschedule(schedule_selector(LineLayer::decrementLastTimer));
    this->unschedule(schedule_selector(LineLayer::blockCreater));
}

void LineLayer::runAfterContinue()
{
    for (auto &mb : myBlocks) {
        mb->setVelocityX(myVelocity);
    }

    for (auto &mt : myToys) {
        mt->setVelX(myVelocity);
    }

    resumeMe();
}

void LineLayer::stopBeforeContinue()
{
    for (auto &mb : myBlocks) {
        mb->setVelocityX(0);
    }

    for (auto &mt : myToys) {
        mt->setVelX(0);
    }

    pauseMe();
}

