#include "obstacle.h"

Obstacle::Obstacle()
{
    
}

void Obstacle::Init(Texture2D* upPipeAddr, Texture2D* downPipeAddr)
{
    int typeValue = GetRandomValue(0, 2);   // 장애물 타입 0은 top, 1은 bottom, 2는 both
    type = ObstacleType(typeValue);  // 장애물 타입을 랜덤하게 설정함
    width = 100;  // 파이프 너비는 위와 아래 파이프가 동일 하다 
    upPipeHeight = GetRandomValue(250, 350);  // 위 파이프의 높이 
    middleHeight = GetRandomValue(300, 400);  // 위와 아래 파이프 사이의 공간 

    upPipe = {GetScreenWidth(), 0, width, upPipeHeight}; 

    downPipe = {GetScreenWidth(), upPipeHeight + middleHeight, width, GetScreenHeight() - (upPipeHeight + middleHeight)};

    UpPipePtr = upPipeAddr;
    DownPipePtr = downPipeAddr;

    topRectImg = {0.0f, 350.0f - float(upPipe.bHeight), 100.0f, float(upPipe.bHeight)};   // 위쪽 파이프 그림에서 가져올 부분이다. 
    bottomRectImg = {0.0f, 0.0f, 100, float(downPipe.bHeight)};  // 아래쪽 파이프 그림에서 가져올 부분이다. 
}

void Obstacle::Update()
{
    upPipe.x -= speed;
    downPipe.x -= speed;
}


void Obstacle::UnloadPipeTexture()
{
    // UnloadTexture(DownPipeImage);       // Texture unloading
    // UnloadTexture(UpPipeImage);       // Texture unloading
}

// 파이프가 화면 왼쪽끝을 넘어가면 지우기 위해 왼쪽 끝의 값을 가져옴
int Obstacle::GetPipePosition()
{
    return upPipe.x + upPipe.bWidth;
}

// 드로잉 메서드 
void Obstacle::Draw()
{
    if (type == ObstacleType::top) {
        // DrawRectangle(upPipe.x, upPipe.y, upPipe.bWidth, upPipe.bHeight, DARKGREEN);
        DrawTextureRec(*UpPipePtr, topRectImg, Vector2{float(upPipe.x), float(upPipe.y)}, WHITE);  // 천장 파이프 그리기  
        DrawText(TextFormat("Addr : %p", UpPipePtr), upPipe.x, upPipe.y + upPipe.bHeight, 20, RED);
    }else if (type == ObstacleType::bottom) {
        // DrawRectangle(downPipe.x, downPipe.y, downPipe.bWidth, downPipe.bHeight, DARKGREEN);
        DrawTextureRec(*DownPipePtr, bottomRectImg, Vector2{float(downPipe.x), float(downPipe.y)}, WHITE ); // 바닥 파이프 그리기 
        DrawText(TextFormat("Addr : %p", DownPipePtr), downPipe.x, downPipe.y -20, 20, RED);
    }else {
        DrawTextureRec(*UpPipePtr, topRectImg, Vector2{float(upPipe.x), float(upPipe.y)}, WHITE);
        DrawTextureRec(*DownPipePtr, bottomRectImg, Vector2{float(downPipe.x), float(downPipe.y)}, WHITE );  // 천장과 바닥 파이프 그리기 
        DrawText(TextFormat("Addr : %p", UpPipePtr), upPipe.x, upPipe.y + upPipe.bHeight, 20, RED);
        DrawText(TextFormat("Addr : %p", DownPipePtr), downPipe.x, downPipe.y - 20, 20, RED);
    }
}

// 새가 파이프와 부딪히는지 체크
bool Obstacle::CheckCollide(Rectangle bird)
{
    
    Rectangle topRect = {float(upPipe.x), float(upPipe.y), float(upPipe.bWidth), float(upPipe.bHeight)}; 
    Rectangle bottomRect = {float(downPipe.x), float(downPipe.y), float(downPipe.bWidth), float(downPipe.bHeight)};

    if (type == ObstacleType::top) {
       bCollide = CheckCollisionRecs(bird, topRect);
    }else if (type == ObstacleType::bottom) {
        bCollide = CheckCollisionRecs(bird, bottomRect);
    }else {
        bCollide = CheckCollisionRecs(bird, topRect) || CheckCollisionRecs(bird, bottomRect);
    }

    return bCollide;
} 

// 새가 파이프를 무사히 건넜는지 확인
bool Obstacle::checkPassing(Rectangle bird)
{
    if (!isPassed) {
     if (bird.x > upPipe.x + upPipe.bWidth) 
     {
        isPassed = true;
        return isPassed;

    }
    }

    return false;
}