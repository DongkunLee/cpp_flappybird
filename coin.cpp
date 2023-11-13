#include "coin.h"

Coin::Coin()
{}

Coin::Coin(Texture2D* _image)
{
    int x = GetScreenWidth(); 
    int y = GetRandomValue(100, GetScreenHeight() - 100);
    pos = {float(x), float(y)};

    coinImage = _image;

    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 16;            // Number of spritesheet frames shown by second
    
    SPRITE_NUMBERS = 31;  // 스프라이트 개수
    speed = 2;  // 코인 스피드 
    addValue = 3;

    frameRec = { 0.0f, 0.0f, (float)coinImage->width / SPRITE_NUMBERS, (float)coinImage->height };
}

int Coin::GetAddValue()
{
    return addValue;
}

int Coin::GetPosition()
{
    return (int)pos.x + (float)coinImage->width / SPRITE_NUMBERS;  // 47은 코인의 너비이다. 
}

bool Coin::GetCollision(Rectangle bRect)
{
    Rectangle rect = {pos.x, pos.y, (float)coinImage->width / SPRITE_NUMBERS, (float)coinImage->height};

    return CheckCollisionRecs(bRect, rect);   
}

void Coin::Update()
{
    framesCounter++; 

    if (framesCounter >= (60/framesSpeed))   // FPS를 60으로 설정했으므로 60을 프레임스피드로 나눈다. 그러면 1초당 몇번 돌릴지 결과 값이 나온다. 
    {
        framesCounter = 0;
        currentFrame++;

        if (currentFrame >  SPRITE_NUMBERS) currentFrame = 0;

        frameRec.x = (float)currentFrame * (float)coinImage->width / SPRITE_NUMBERS;
    }
    pos.x -= speed;
}

void Coin::Draw()
{
    DrawTextureRec(*coinImage, frameRec, pos, WHITE);  // Draw part of the texture
}


Life::Life(Texture2D* _image, int _sprite_numbers, int _speed, int _addValue)
{
    int x = GetScreenWidth(); 
    int y = GetRandomValue(100, GetScreenHeight() - 100);
    pos = {float(x), float(y)};

    coinImage = _image;
    
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 8;            // Number of spritesheet frames shown by second
    
    SPRITE_NUMBERS = _sprite_numbers;  // 스프라이트 개수
    speed = _speed;  // 코인 스피드 
    addValue = _addValue;

    frameRec = { 0.0f, 0.0f, (float)coinImage->width / SPRITE_NUMBERS, (float)coinImage->height };
}