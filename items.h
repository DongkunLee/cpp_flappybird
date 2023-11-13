#pragma once
#ifndef __items__
#define __items__
#include "raylib.h"
#include "coin.h"
#include <vector>
#include "bird.h"
#include "config.h"

class Items
{
    private:
        Items() {} 
        static Items* instance; 

    public:

        static Items* GetInstance()
        {
            if (instance != nullptr)
            {
                return instance;
            }else
            {
                instance = new Items();
                return instance;
            }
        }

    public:
        void Init();
        void Update(Bird* _player);
        void Draw();
        ~Items();
        void SetTimer();

    private:
        // 텍스처 로드하기 
        // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
        Texture2D  CoinSprite;        // Texture loading;  
        std::vector<Coin>  coins;
        Sound fxCoin;         // Load WAV audio file   

        Texture2D LifeSprite;
        std::vector<Life> lifes;
        Sound fxLife;
        SceneManager* menuManager;
        bool canSpawn;
        int timer;
};

#endif