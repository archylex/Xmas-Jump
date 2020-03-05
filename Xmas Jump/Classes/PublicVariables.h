#include <iostream>

#pragma once

using namespace std;

class PublicVariables {
    public:        
        static PublicVariables* Instance();
        void setHighScore(int _score);
        int getHighScore();
        void setSFX(bool _sfx);
        bool getSFX();
        void setMusic(bool _music);
        bool getMusic();
        void setCharacter(string _fname);
        string getCharacter();
        void setBlockSize(int _size);
        int getBlockSize();
        void setDeltaX(float _dx);
        float getDeltaX();
        void setDeltaY(float _dx);
        float getDeltaY();
        
    private:
        PublicVariables();        
        static PublicVariables* m_pInstance;
        float deltaX;
        float deltaY;
        int highScore;
        bool sfx;
        bool music;
        string character;
        int BlockSize;
        
};
