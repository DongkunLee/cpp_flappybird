#include "bird.h"


void Bird::Init()
{
    // 최초의 포지션 정하기
    pos = {150, float(GetScreenHeight()) / 2} ;
    // 그림으로 넣기
    birdImage = LoadTexture("Assets/birddrawing.png");        // Texture loading
    fxJump = LoadSound("Assets/jump.wav");
    fxHurt = LoadSound("Assets/zap1.wav");
    fxExplosion = LoadSound("Assets/explosion.wav");

    // 기존에 있던 플레이어 속성 초기화
    Score = 0;
    Life = 3;
    isInvincible = false;
    timer = 0;
}

Bird::~Bird()
{
    UnloadTexture(birdImage);       // Texture unloading
    UnloadSound(fxJump);     // Unload sound data
}

void Bird::Update()
{
    downSpeed += GRAVITY;
    pos.y += downSpeed;

    CheckCollision();

    if (isInvincible)
    {
        timer++;
        if (timer > MaxTimer) 
        {
            timer = 0;
            isInvincible = false;
        }
    }
}

void Bird::CheckCollision()
{
    if (pos.y - halfLengthH <= 0) pos.y = halfLengthH; 

    if (pos.y + halfLengthH >= GetScreenHeight()) pos.y = GetScreenHeight() - halfLengthH;
}

// 플레이어가 데미지를 입는 메서드
void Bird::Hurt()
{
    Life--;
    SetInvincible(true);    

    if (Life > 0)  PlaySound(fxHurt);
    else PlaySound(fxExplosion);
}

// 플레이어 점수 추가 
void Bird::SetAddScore(int increment)
{
    Score += increment;
}

// 플레이어 생명력 추가
void Bird::SetAddLife(int increment)
{
    Life += increment;
}

void Bird::SetInvincible(bool flag)
{
    isInvincible = flag;
}

bool Bird::GetInvincible()
{
    return isInvincible;
}

void Bird::Jump()
{
    downSpeed = -jumpSpeed; 
    PlaySound(fxJump);      // Play WAV sound
}

// 플레이어 그리기 
void Bird::Draw()
{
    if (isInvincible)
    {
       //  DrawRectangle(pos.x - halfLength, pos.y - halfLength, halfLength * 2, halfLength * 2, GRAY);  // 플레이어가 무적일 떄 
        DrawTexture(birdImage, int(pos.x) - halfLengthW, int(pos.y) - halfLengthH, GRAY);
    }else
    {
       // DrawRectangle(pos.x - halfLengthW, pos.y - halfLengthH, halfLengthW * 2, halfLengthH * 2, DARKGREEN); // 평상시
       DrawTexture(birdImage, int(pos.x) - halfLengthW, int(pos.y) - halfLengthH, WHITE); 
    }
}

// 플레이어의 컬리젼 네모 값을 리턴한다. 
Rectangle Bird::GetPosition()
{
    return {pos.x - halfLengthW, pos.y - halfLengthH, halfLengthW * 2, halfLengthH * 2};  
}