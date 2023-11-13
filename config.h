#pragma once
#ifndef __CONFIG__
#define __CONFIG__
#include <iosfwd>
#include "raylib.h" 
#include <string>
#include "utils/json.hpp"

// 로고, 메인메뉴, 게임 화면 등 각각의 씬
enum class Scene 
{
    logo = 0, titleMenu, game, scoreScene, settingScreen
};

// 전역적으로 사용할 싱글톤 클래스
class SceneManager 
{
    private:
        SceneManager() {} 
        static SceneManager* instance; 

    public:

        static SceneManager* GetInstance()
        {
            if (instance != nullptr)
            {
                return instance;
            }else
            {
                instance = new SceneManager();
                return instance;
            }
        }
        ~SceneManager();
        bool SaveJson();
        bool LoadJson();
        void LoadResource();  // Resource Initializing
        
        // Game Manage Variable 
        bool gameExit;
        Scene scene;
        Scene lastSce;
        float volume = 1.0f;
        bool isLog = false;

        Music music;  // 배경음악 선언  
        Font fontStrawberry;
        Font fontGukdae;
        Font fontNice;
};

class LangManager
{
    private:
        LangManager() {} 
        static LangManager* instance; 
        std::string GetString(const char* lang, std::string _elem);
        nlohmann::json outputData;
    public:
        static LangManager* GetInstance()
        {
            if (instance != nullptr)
            {
                return instance;
            }else
            {
                instance = new LangManager();
                return instance;
            }
        }
        ~LangManager();
        void Init();
        void LoadStrings(const char* lang);
        // 멤버 변수 
        std::string title, start, mainMenu, settings, exit, settingsScreen, save, load, volume, log;
};

 #endif


