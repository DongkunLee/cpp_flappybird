#pragma once
#include "config.h" 
#include "gui.h"
#include "buttonActionMap.h"
#include <string>
class SettingScreen
{
    public :
        void Init(int width, int height, std::string title); 
        void Tick();
        SettingScreen();
        ~SettingScreen();

    private: 
        void Draw(); 
        void Update(); 
        void KeyboardInputCheck();
        void KeyboardButtonCheck();
        void Save();
        void Load();
        enum class settingMenuEnum 
        {
            volume = 0,log,save,load,menu,exit
        };

        GUI* gui[6];
        
       // Font font;
        Texture2D img[6];
        Texture2D boximg[4];

        SceneManager* menuManager;
        settingMenuEnum menuState;
        LangManager* langs;
     //   Music music;  // 배경음악 선언 
        int gamepad = 0; // 제일 처음에 꽂은 게임패드만 사용하도록 하자. 제일 처음이므로 0이다. 

        bool isDisplayTimer = false;
        int DisplayTimer = 0;
        const char* DisplayString;

};