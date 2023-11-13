#pragma once
#include <string>
#include "raylib.h" 
#include "config.h"
// #include "bird.h"
// #include <vector>
#include "obstacle.h"
#include "items.h"
#include "buttonActionMap.h"

enum class Gamestate
{
    pause, game
};

class Game
{
    public :
        void Init(int width, int height, std::string title); 
        ~Game() noexcept;
        void Tick();

    private: 
        void Draw(); 
        void Update();
        void Reset();
        void DrawBackground(); 
        void ObstacleLogic();

        Texture2D backgroundImage;        // Texture loading;  
        // Music music;  // 배경음악 선언 

        // 플레이어 
        Bird bird;
        // 장애물 변수 선언
        std::vector<Obstacle> pipes;
        int timer = 0;
        int maxTimer = 120; 

       Texture2D UpPipeImage;        // Texture loading;  
       Texture2D DownPipeImage;        // Texture loading;  
        
       // Items 에이전트
       Items* items;

       int gamepad = 0; // 제일 처음에 꽂은 게임패드만 사용하도록 하자. 제일 처음이므로 0이다. 

};

