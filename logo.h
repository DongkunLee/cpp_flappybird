#pragma once
#include "raylib.h" 
#include "config.h" 

class Logo
{
    public :
        void Init(int width, int height, std::string title, int maxTimer); 
        void Tick();
        int timer;
        int MaxTimer;

    private: 
        void Draw(); 
        void Update();
};