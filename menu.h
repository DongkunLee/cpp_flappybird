#pragma once
#include "config.h" 
#include "gui.h"
#include "buttonActionMap.h"
#include "raylib.h"
#include <string>
#include  <vector>

enum class menuEnum 
{
    us = 0, kr, jp, game, settingScreen, exit, 
};

class Menu
{
    public :
        void Init(int width, int height, std::string title); 
        void Tick();
        Menu();
        ~Menu();

    private: 
        void Draw(); 
        void Update(); 
        void KeyboardInputCheck();
        void KeyboardButtonCheck();
        bool IsActionPressed();
        void RefreshLang();

        // Text set up
        LangManager* langs;
        SceneManager* menuManager;
        // GUI button; 
        GUI* button[6];
        Texture2D flagImg[3];
        // std::vector<std::string> texts;
      //  Font font;

        menuEnum menuState;

        int gamepad = 0; // 제일 처음에 꽂은 게임패드만 사용하도록 하자. 제일 처음이므로 0이다. 
};

