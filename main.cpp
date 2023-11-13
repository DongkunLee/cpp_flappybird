#include "game.h"
#include "logo.h"
#include "menu.h"
#include "settingscreen.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

SceneManager* SceneManager::instance = nullptr;
LangManager*  LangManager::instance = nullptr;

int main(void) 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int GamescreenWidth = 1200;
    const int GamescreenHeight = 900;
    
    // SceneManager 셋팅 
    SceneManager* menuManager = SceneManager::GetInstance(); 

    // 언어 세팅
    LangManager* langs = LangManager::GetInstance();
    langs->LoadStrings("ko");

    menuManager->gameExit = false;   // gameExit가 false인 한 게임 루프는 계속 돌아감 
    menuManager->scene = Scene::logo;
    menuManager->lastSce = Scene::scoreScene;

    // 게임창 만들기 
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    InitWindow(screenWidth, screenHeight, "Flappy Bird"); 

    // Image icon = LoadImage("Assets/DKIcon.png");
    // SetWindowIcon(icon);

    // 오디오 디바이스 초기화하기
    InitAudioDevice();      // Initialize audio device

    // InitWIndow() 이후에 선언해 줘야 한다.
    Logo logo = Logo();
    Game game = Game();
    Menu menu = Menu();
    SettingScreen setting = SettingScreen();
    menuManager->LoadJson();
    menuManager->LoadResource();


    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!menuManager->gameExit)    // 게임 루프
    {
        switch (menuManager->scene) 
        {
            case Scene::logo :   // 로고 화면 
                if (menuManager->lastSce != menuManager->scene)  // 로고화면으로 전환시에 로고 클래스 초기화 하기 
                {
                    logo.Init(screenWidth, screenHeight, "Flappy Bird Logo Screen", 120);
                    menuManager->lastSce = menuManager->scene;    // 마지막 씬을 현재 씬으로 저장하여 앞으로 씬 전환이 아니라고 알려주기 
                }else
                {              
                    if(logo.timer < logo.MaxTimer)
                    {
                        logo.Tick();    // 설정된 시간 동안 루프를 돌린다. 
                    }else
                    {
                        menuManager->scene = Scene::titleMenu;  // 설정된 시간을 넘기면 게임 화면으로 넘어간다. 
                    }
                }
            break;

            case Scene::titleMenu :
                if (menuManager->lastSce != menuManager->scene) // 다른 씬에서 게임화면으로 전환하면 클래스를 초기화한다. 
                {
                    menu.Init(screenWidth, screenHeight, "Flappy Bird Main Menu");  // 게임화면을 초기화한다. 로고화면과 다르다는 것을 알리기 위해 화면을 크게 했다. 
                    menuManager->lastSce = menuManager->scene;   // 마지막 씬도 현재 씬과 똑같다고 설정한다. 
                }else
                {
                  menu.Tick();   // 게임 루프를 돌린다. 
                }
            break;

            case Scene::settingScreen :
                if (menuManager->lastSce != menuManager->scene) // 다른 씬에서 게임화면으로 전환하면 클래스를 초기화한다. 
                {
                    setting.Init(screenWidth, screenHeight, "Flappy Bird Setting Screen");  // 게임화면을 초기화한다. 로고화면과 다르다는 것을 알리기 위해 화면을 크게 했다. 
                    menuManager->lastSce = menuManager->scene;   // 마지막 씬도 현재 씬과 똑같다고 설정한다. 
                }else
                {
                    setting.Tick();   // 게임 루프를 돌린다. 
                }
            break;

            case Scene::game :
                if (menuManager->lastSce != menuManager->scene) // 다른 씬에서 게임화면으로 전환하면 클래스를 초기화한다. 
                {
                    game.Init(GamescreenWidth, GamescreenHeight, "Flappy Bird");  // 게임화면을 초기화한다. 로고화면과 다르다는 것을 알리기 위해 화면을 크게 했다. 
                    menuManager->lastSce = menuManager->scene;   // 마지막 씬도 현재 씬과 똑같다고 설정한다. 
                }else
                {
                  game.Tick();   // 게임 루프를 돌린다. 
                }
            break;


            default :

            break;
        }
    
    }

    // UnloadImage(icon);
    CloseAudioDevice();     // Close audio device
    CloseWindow();                  // Close window and OpenGL context
    return 0;

};
