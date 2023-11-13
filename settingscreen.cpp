#include "settingscreen.h"
#include "raylib.h"


SettingScreen::SettingScreen()   // 생성자
{

}

void SettingScreen::Init(int width, int height, std::string title)  // 세팅스크린을 초기화한다.
{
    langs = LangManager::GetInstance();
    menuManager = SceneManager::GetInstance();  

  //  font = LoadBMFontEX("Assets/font/gukdae.fnt");
    // 창의 사이즈 및 이름을 설정하기 
    SetWindowSize(width, height);
    SetWindowTitle(title.c_str());

    PlayMusicStream(menuManager->music);
    SetMusicVolume(menuManager->music, menuManager->volume);

    // 텍스쳐 로드
    img[0] = LoadTexture("Assets/slide.png");   // 0은 슬라이드 
    img[1] = LoadTexture("Assets/slidebar.png"); // 1은 슬라이드 바 
    img[2] = LoadTexture("Assets/minusenabled.png"); // 2는 왼쪽 활성
    img[3] = LoadTexture("Assets/plusenabled.png");  // 3은 오른쪽 활성
    img[4] = LoadTexture("Assets/minusdisabled.png");  // 4는 왼쪽 비활성
    img[5] = LoadTexture("Assets/plusdisabled.png");  // 5는 오른쪽 비활성

    boximg[0] = LoadTexture("Assets/boxenabled.png");  // 0은 박스 활성화 체크 해제 
    boximg[1] = LoadTexture("Assets/boxdisabled.png");  //  1은 박스 비활성화 체크해제 
    boximg[2] = LoadTexture("Assets/boxenabledchecked.png");  //  2는 박스 활성화 체크
    boximg[3] = LoadTexture("Assets/boxdisabledchecked.png");  //  3는 박스 비활성화 체크

    // 버튼 설정하기
    gui[0] = new GUISliderImg(240, 140, 400, 40, "", &menuManager->fontGukdae, &menuManager->volume, img);   // 슬라이더 
    gui[1] = new GUICheckBox(250, 180, &menuManager->isLog, boximg);
    gui[2] = new ButtonPointer(GetScreenWidth() - 200, GetScreenHeight() - 200, 180, 40, &langs->save, &menuManager->fontGukdae);   // 저장 버튼
    gui[3] = new ButtonPointer(GetScreenWidth() - 200, GetScreenHeight() - 150, 180, 40, &langs->load, &menuManager->fontGukdae);  // 불러오기 버튼
    gui[4] = new ButtonPointer(GetScreenWidth() - 200, GetScreenHeight() - 100, 180, 40, &langs->mainMenu, &menuManager->fontGukdae);  // 메뉴 버튼
    gui[5] = new ButtonPointer(GetScreenWidth() - 200, GetScreenHeight() - 50, 180, 40, &langs->exit,&menuManager->fontGukdae);  // 종료 버튼

    // 메뉴 스테이트 선언
   menuState = settingMenuEnum::volume;

    KeyboardButtonCheck();  // 키보드 상태를 현재 메뉴스테이트에 따라 달리 설정해 주기 
}

void SettingScreen::Tick()   // 기본적인 루프
{
    BeginDrawing();    // 레이라이브 기본 함수이다. 
    Update();
    Draw();
    EndDrawing();  // 레이라이브 기본 함수이다. 
}


SettingScreen::~SettingScreen() // 소멸자
{
}

void SettingScreen::Update()
{
    UpdateMusicStream(menuManager->music);   // Update music buffer with new stream data

    // 각 GUI의 로직을 실행한다. 
    for (int i =0; i<6; i++)
    {
        if (gui[i]->Update())   // gui[0]는 guiSlider이고, 나머지는 gui이다. 
        {
            SetMusicVolume(menuManager->music, menuManager->volume);
        }
    }

    // 세이브 로드 타이머
    if (isDisplayTimer)
    {
        DisplayTimer--;
        if (DisplayTimer <0)
        {
            DisplayTimer = 0;
            isDisplayTimer = false;
        }
    }

    // 버튼 선택하고 마우스 입력한 신호 받기 
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gui[2]->GetChecked()) Save(); 

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gui[3]->GetChecked()) Load();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gui[4]->GetChecked())  menuManager->scene = Scene::titleMenu; 

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gui[5]->GetChecked())  menuManager->gameExit = true;
    
    KeyboardInputCheck();
}

// 키보드 인풋
void SettingScreen::KeyboardInputCheck()
{

    if (IsLeftAxisUpChecked() )
    {
        int mI = (int)menuState;  
        mI--; 
        if (mI < 0) mI = 5; 
        menuState = settingMenuEnum(mI); 

        KeyboardButtonCheck();
    }

    if (IsLeftAxisDownChecked())
    {
        int mI = (int)menuState;  
        mI++; 
        if (mI > 5) mI = 0; 
        menuState = settingMenuEnum(mI); 

        KeyboardButtonCheck();
    }

    // 선택 키를 눌렀을 때 로직, (엔터키, 키보드 B키)
    if (IsButtonPressed("Jump"))
    {
          switch (menuState) 
          {
            case settingMenuEnum::save :
                Save();
                break;
            case settingMenuEnum::load :
                Load();
                break;
            case settingMenuEnum::log :
                //  
                break;
            case settingMenuEnum::menu : 
                menuManager->scene = Scene::titleMenu; 
                break;
            case settingMenuEnum::exit :
                menuManager->gameExit = true;
                break; 
            default : 
                // menuManager->scene = Scene::game; 
                break;
          }
    }
}


// Save Settings
void SettingScreen::Save()
{
    if(menuManager->SaveJson())
    {
        isDisplayTimer = true;
        DisplayTimer = 180;
        DisplayString = "Successfully Saved!\n" ;
    }else
    {
        isDisplayTimer = true;
        DisplayTimer = 180;
        DisplayString = "Save Failed!\n";
    }
}

// Load Settings
void SettingScreen::Load()
{
    if(menuManager->LoadJson())
    {
        isDisplayTimer = true;
        DisplayTimer = 180;
        DisplayString = "Successfully Loaded!\n";
    }else 
    {
        isDisplayTimer = true;
        DisplayTimer = 180;
        DisplayString = "Load Failed!\n";
    }
}


// 현재 메뉴 상태에 따라 키보드 모양을 달리 정해줌
void SettingScreen::KeyboardButtonCheck()
{
    // gui가 선택된 것인지 확인해 줌
    for (int i =0; i < 6; i++)
    {
        if (i == (int)menuState) 
            gui[i]->Checked();
        else 
            gui[i]->UnChecked();
    }

}

void SettingScreen::Draw()  // Draw메서드 
{
     ClearBackground(BLACK);

    DrawTextEx(menuManager->fontGukdae, (langs->settingsScreen).c_str(), (Vector2) { 100, 60 }, 40, 5, DARKBROWN);
    DrawTextEx(menuManager->fontGukdae, langs->volume.c_str(), (Vector2) { 50, 144 }, 32, 5, RAYWHITE);
    DrawTextEx(menuManager->fontGukdae, langs->log.c_str(), (Vector2) { 50, 184 }, 32, 5, RAYWHITE);

    // gui 그리기
    for (int i =0; i < 6; i++)
    {
        gui[i]->Draw(); 
    }

    // 저장 및 로드 성공 여부 알려주기
    if (isDisplayTimer)
    {
        DrawText(TextFormat(DisplayString), 100, GetScreenHeight() - 100, 20, WHITE);
    }
    

   // 게임패드 있는지 확인
    if (IsGamepadAvailable(gamepad)) 
    {
        DrawText(TextFormat("GamePad Detected : %s", GetGamepadName(gamepad)), 20, 20, 20, WHITE);
        DrawText("Confirm : B", GetScreenWidth() - 200, GetScreenHeight() - 50, 20, RAYWHITE);
    }else
    {
        DrawText("Confirm : Enter", 100, GetScreenHeight() - 50, 20, RAYWHITE);
    }
}
