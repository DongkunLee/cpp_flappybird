#include "menu.h"


void Menu::Init(int width, int height, std::string title)
{


    // 창의 사이즈 및 이름을 설정하기 
    SetWindowSize(width, height);
    SetWindowTitle(title.c_str());

    //     Image icon = LoadImage("Assets/DKIcon.png");
    // SetWindowIcon(icon);
    
    menuManager = SceneManager::GetInstance();
    langs = LangManager::GetInstance();

  //  font = LoadBMFontEX("Assets/font/gukdae.fnt");
   //font = GetFont(texts, "Assets/SDKukdetopokki-bBd.otf");
    // 국기 이미지 
    flagImg[0] = LoadTexture("Assets/flags/us.png");
    flagImg[1] = LoadTexture("Assets/flags/KR.png");
    flagImg[2] = LoadTexture("Assets/flags/JP.png");

    // 각 버튼 선언하기 
   button[0] = new ImgButton(GetScreenWidth() - 300, 20, 90, 60, &flagImg[0]);
   button[1] = new ImgButton(GetScreenWidth() - 200, 20, 90, 60, &flagImg[1]);
   button[2] = new ImgButton(GetScreenWidth() - 100, 20, 90, 60, &flagImg[2]);
   button[3] = new ButtonPointer(GetScreenWidth() - 200, GetScreenHeight() - 200, 180, 40, &(langs->start), &menuManager->fontStrawberry);   // 게임 시작 버튼
   button[4] = new ButtonPointer(GetScreenWidth() - 200, GetScreenHeight() - 140, 180, 40, &langs->settings, &menuManager->fontStrawberry);  // 환경설정 버튼
   button[5] = new ButtonPointer(GetScreenWidth() - 200, GetScreenHeight() - 80, 180, 40, &langs->exit, &menuManager->fontStrawberry);   // 게임 종료 버튼

    // 메뉴 스테이트 선언
   menuState = menuEnum::game;

    KeyboardButtonCheck();  // 키보드 상태를 현재 메뉴스테이트에 따라 달리 설정해 주기
}

void Menu::Tick()   // 기본적인 루프
{
    BeginDrawing();    // 레이라이브 기본 함수이다. 
    Update();
    Draw();
    EndDrawing();  // 레이라이브 기본 함수이다. 
}

Menu::Menu()
{
}

Menu::~Menu()
{
    UnloadTexture(flagImg[0]);
    UnloadTexture(flagImg[1]);
    UnloadTexture(flagImg[2]);
}


void Menu::Update()
{
    for (int i = 0; i < 6; i++)
    {
        button[i]->Update();
    }

    // 버튼 선택하고 마우스 입력한 신호 받기 
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && button[0]->GetChecked()) langs->LoadStrings("en");

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && button[1]->GetChecked())  langs->LoadStrings("ko");

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && button[2]->GetChecked()) langs->LoadStrings("jp"); 

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && button[3]->GetChecked())  menuManager->scene = Scene::game; 

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && button[4]->GetChecked())  menuManager->scene = Scene::settingScreen; 

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && button[5]->GetChecked())  menuManager->gameExit = true;

    KeyboardInputCheck();
}

// 키보드 인풋
void Menu::KeyboardInputCheck()
{

    if (IsLeftAxisUpChecked() )
    {
        int mI = (int)menuState;  
        mI--; 
        if (mI < 0) mI = 5; 
        menuState = menuEnum(mI); 

        KeyboardButtonCheck();
    }

    if (IsLeftAxisDownChecked())
    {
        int mI = (int)menuState;  
        mI++; 
        if (mI >  5) mI = 0; 
        menuState = menuEnum(mI); 

        KeyboardButtonCheck();
    }

    // 선택 키를 눌렀을 때 로직, (엔터키 또는 E키)
    if (IsActionPressed())
    {
          switch (menuState) 
          {
            case menuEnum::us:
                langs->LoadStrings("en");
                break;
            case menuEnum::kr:
                langs->LoadStrings("ko");
                break;
            case menuEnum::jp:
                langs->LoadStrings("jp");
                break;
            case menuEnum::game :
                menuManager->scene = Scene::game; 
                break;
            case menuEnum::settingScreen : 
                menuManager->scene = Scene::settingScreen; 
                break;
            case menuEnum::exit :
                menuManager->gameExit = true;
                break;

            default : 
                menuManager->scene = Scene::game; 
                break;
          }
    }
}

// 액션키 매핑
bool Menu::IsActionPressed()
{
    if (IsGamepadAvailable(gamepad))
    {    
        return IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);  // A버튼을 눌렀는지 리턴
    }else 
    {
        return  IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_E);
    }
}

// 현재 메뉴 상태에 따라 키보드 모양을 달리 정해줌
void Menu::KeyboardButtonCheck()
{
    for (int i = 0; i < 6; i++)
    {
        if (i == (int)menuState) 
            button[i]->Checked(); 
        else 
            button[i]->UnChecked();
    }
}

void Menu::Draw()
{
    ClearBackground(BLACK);
    DrawText("Flappy Bird Menu!", GetScreenWidth() / 2 - 160, GetScreenHeight() / 2  - 40, 40, DARKBROWN); 

   // 버튼 그리기 
   for (int i = 0; i < 6;i++)
   {
        button[i]->Draw();
   }

   // 게임패드 있는지 확인
    if (IsGamepadAvailable(gamepad)) 
    {
        DrawText(TextFormat("GamePad Detected : %s", GetGamepadName(gamepad)), 50, 40, 20, WHITE);
    }

    // Draw provided text with loaded font, containing all required codepoint glyphs
    DrawTextEx(menuManager->fontStrawberry, (langs->title).c_str(), (Vector2) { 100, 110 }, 32, 5, WHITE);
}

