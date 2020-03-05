#include "PublicVariables.h"


PublicVariables* PublicVariables::m_pInstance = nullptr;

PublicVariables::PublicVariables() {
    sfx = true;
    music = true;
    highScore = 0;
    character = "snowman.png";
}

PublicVariables* PublicVariables::Instance() {
    if (!m_pInstance)
        m_pInstance = new PublicVariables;

    return m_pInstance;
}

void PublicVariables::setSFX(bool _sfx) {
    sfx = _sfx;
}

bool PublicVariables::getSFX() {
    return sfx;
}

void PublicVariables::setMusic(bool _music) {
    music = _music;
}

bool PublicVariables::getMusic() {
    return music;
}

void PublicVariables::setHighScore(int _score) {
    highScore = _score;
}

int PublicVariables::getHighScore() {
    return highScore;
}

void PublicVariables::setCharacter(string _fname) {
    character = _fname;
}

string PublicVariables::getCharacter() {
    return character;
}

void PublicVariables::setBlockSize(int _size) {
    BlockSize = _size;
}

int PublicVariables::getBlockSize() {
    return BlockSize;
}

void PublicVariables::setDeltaX(float _dx)
{
    deltaX = _dx;
}

float PublicVariables::getDeltaX()
{
    return deltaX;
}

void PublicVariables::setDeltaY(float _dy)
{
    deltaY = _dy;
}

float PublicVariables::getDeltaY()
{
    return deltaY;
}















