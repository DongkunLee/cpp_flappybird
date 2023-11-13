#include "config.h"
#include <iostream>
#include <fstream>
#include "dkfont.h"

// Save Setting to json file
bool SceneManager::SaveJson()
{
    using namespace nlohmann;

    json j;
    j["Name"] = "DK Flappy Bird!";
    j["SoundVolume"] = volume;
    j["bLog"] = isLog;

    // write prettified JSON to another file
    std::ofstream o("settings.json");
    if (o.bad())
    {
        return false;
    }
    
    o << std::setw(4) << j << std::endl;
    o.close();

    return true;
}


bool SceneManager::LoadJson()  // 설정 불러오기
{
    using namespace nlohmann;

    std::ifstream f("settings.json");

    if (f.bad())
    {
        return false;
    }

    json data = json::parse(f);
    volume = data["SoundVolume"];
    isLog = data["bLog"];
    f.close();
    return true;
}

void SceneManager::LoadResource()  // 전역 리소스 불러오기 
{
    music = LoadMusicStream("Assets/country.mp3");
    fontStrawberry = LoadBMFontEX("Assets/font/gostrawberry.fnt");
    fontGukdae = LoadBMFontEX("Assets/font/gukdae.fnt");
    fontNice = LoadBMFontEX("Assets/font/elandnice.fnt");
}

SceneManager::~SceneManager()
{
    UnloadMusicStream(music);   // Unload music stream buffers from RAM
    UnloadFont(fontStrawberry);
    UnloadFont(fontGukdae);
    UnloadFont(fontNice);
}

void LangManager::Init()
{
    title = "DK Flappy Bird!";
    start = "Start";
    mainMenu = "MainMenu";
    settings = "Settings"; 
    exit = "Exit";
    settingsScreen = "Settings Screen";
    save = "Save";
    load = "Load";
    volume = "Volume";
    log = "Log";     
}

void LangManager::LoadStrings(const char* lang)
{
    using namespace nlohmann;

    std::ifstream f("localization.json");

    outputData = json::parse(f);

    // 해당 언어가 있는지 확인하고 없으면 영어를 출력하기
    if (!outputData.contains(std::string(lang)))
    {
        lang = "en";
    }

    // Strings set up by language localization.
    title = GetString(lang, "Title");
    start = GetString(lang, "Start");
    mainMenu = GetString(lang, "MainMenu");
    settings = GetString(lang, "Settings");
    exit = GetString(lang,"Exit");
    settingsScreen = GetString(lang, "SettingsScreen");
    save = GetString(lang, "Save");
    load = GetString(lang, "Load");
    volume = GetString(lang, "Volume");
    log = GetString(lang, "Log");

    f.close();
}

// 해당 언어중에 빠트린 문장이 있으면 영어 문장을 출력하기
std::string LangManager::GetString(const char* _lang, std::string _elem)
{
    if (!outputData[_lang].contains(_elem)) return outputData["en"][_elem];
     else return outputData[_lang][_elem];
}

LangManager::~LangManager()
{

}