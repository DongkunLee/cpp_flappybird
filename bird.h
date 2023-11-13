#pragma once
#include "raylib.h"

#define GRAVITY 0.2f;  // 중력 값 : 가속도의 값이다.  한 프레임당 가속도이다. 

class Bird {
    public: 
    ~Bird(); 

    void Init();
    void Update();
    void Jump();
    void Draw();

    bool GetInvincible();
    void Hurt();
    void SetAddScore(int increment);
    void SetAddLife(int increment);

    Rectangle GetPosition();
    int Score = 0; 
    int Life = 3;

    private:
    Vector2 pos; 
    float downSpeed = 0;
    float jumpSpeed = 6; 
    float halfLengthH = 18; 
    float halfLengthW = 25; 
    bool isInvincible = false; 
    int timer = 0;
    int MaxTimer = 80;


    // 텍스처 로드하기 
    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D birdImage;        // Texture loading;  
    Sound fxJump;         // Load WAV audio file
    Sound fxHurt;
    Sound fxExplosion;

    // 내부적으로 불러오는 함수
    void CheckCollision();
    void SetInvincible(bool flag);
};
