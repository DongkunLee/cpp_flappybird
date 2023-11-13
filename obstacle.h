#pragma once
#include "raylib.h"

enum class ObstacleType 
{
    top = 0, bottom, both
};

typedef struct Box 
{
    int x; 
    int y;
    int bWidth;
    int bHeight;
} Box ;

class Obstacle {
    public: 
    Obstacle();
    void Init(Texture2D* upPipeAddr, Texture2D* downPipeAddr);
    void Update();
    void Draw();
    int GetPipePosition();
    bool CheckCollide(Rectangle bird);
    bool checkPassing(Rectangle bird);
    void UnloadPipeTexture();

    private:
    Box upPipe;
    Box downPipe;
    int upPipeHeight; 
    int width;
    int middleHeight;
    int speed = 2; 
    ObstacleType type = ObstacleType::top;
    bool isPassed = false;
    bool bCollide = false;

     // 텍스처 로드하기 
    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D* UpPipePtr;        // Texture loading;  
    Texture2D* DownPipePtr;        // Texture loading;  

    Rectangle topRectImg;
    Rectangle bottomRectImg;

};
