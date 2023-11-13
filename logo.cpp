#include "logo.h"
#include <string>

void Logo::Init(int width, int height, std::string title, int maxTimer)
{
    SetWindowSize(width, height); 
   SetWindowTitle(title.c_str());
    timer = 0;  // 타이머 설정 
    MaxTimer = maxTimer;
}

void Logo::Tick()
{
    BeginDrawing();    
    Update();
    Draw();
    EndDrawing(); 
}

void Logo::Update()
{
    timer++;     // 타이머는 BeginDrawing과 End Erawing사이에 있어야만 설정된 FPS대로 숫자가 올라간다. 
}

void Logo::Draw()
{
    ClearBackground(DARKBLUE);
    DrawText("Flappy Bird Game!", GetScreenWidth() / 2 - 160, GetScreenHeight() / 2  - 40, 40, DARKBROWN);
}