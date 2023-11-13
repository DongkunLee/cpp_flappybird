#pragma once
#include "raylib.h"

class Coin 
{
    public: 
        Coin();
        Coin(Texture2D* _image);
        void Update();
        void Draw();
        int GetPosition();
        bool GetCollision(Rectangle bRect);
        int GetAddValue();

    protected:
        Vector2 pos;                            // 코인 위치
        Texture2D* coinImage;        // Texture의 주소값
        Rectangle frameRec;            // 보여줄 프레임
        
        int currentFrame = 0;
        int framesCounter = 0;
        int framesSpeed = 16;            // Number of spritesheet frames shown by second

        int SPRITE_NUMBERS ; // 스프라이트 개수
        int speed;  // 스피드
        int addValue; // 넘겨줄 값
}; 

class Life : public Coin
{
    public : 
        Life(Texture2D* _image, int _sprite_numbers, int _speed, int _addValue);
};