#include "game.h"

SceneManager* Manager = SceneManager::GetInstance(); 
Gamestate gamestate;


// 게임 초기화
void Game::Init(int width, int height, std::string title) 
{
    SetWindowSize(width, height);
    SetWindowTitle(title.c_str());


    gamestate = Gamestate::game;  

    bird.Init();  // 플레이어 초기화

    // 장애물 초기화하기 
    // 파이프 이미지
    DownPipeImage = LoadTexture("Assets/Pipe-up350.png");      // 아래쪽에 있는 파이프이다. 에셋의 파일명은 위쪽을 바라보는 의미에서 pipe-up이다. 
    UpPipeImage = LoadTexture("Assets/Pipe-down350.png");      // 위쪽에 있는 파이프이다. 에셋의 파일명은 아래쪽을 바라보는 의미에서 pipe-up이다. 

    pipes.clear();
    Obstacle pipe;
    pipe.Init(&UpPipeImage, &DownPipeImage);     
    pipes.push_back(pipe); 
    maxTimer = GetRandomValue(120, 240); 

    // 배경화면 부르기 
    backgroundImage = LoadTexture("Assets/background.png");

    // 배경음악 플레이 할당하기
   // music = LoadMusicStream("Assets/country.mp3");
    PlayMusicStream(Manager->music);
    SetMusicVolume(Manager->music, Manager->volume);
    // 아이템 에이전트 인스턴스 및 초기화
    items = Items::GetInstance();
    items->Init();
}

Game::~Game()
{
    UnloadTexture(DownPipeImage);       // Texture unloading
    UnloadTexture(UpPipeImage);       // Texture unloading
    UnloadTexture(backgroundImage); // Texture unloading
//    UnloadMusicStream(music);   // Unload music stream buffers from RAM
    pipes.clear();
} 

void Game::Tick()
{
    BeginDrawing();
    Update();
    Draw();
    EndDrawing(); 

}

void Game::Update()
{
    // Update
    UpdateMusicStream(Manager->music);   // Update music buffer with new stream data

    // 각 게임스테이트마다 상황 설정
    switch (gamestate)
    {   

        case Gamestate::pause :    // 정지로직  
             if (IsButtonPressed("Jump"))
            {
                gamestate = Gamestate::game;    // 게임으로 돌아가기 
                ResumeMusicStream(Manager->music);
            }

            if (gamestate == Gamestate::pause && IsButtonPressed("ESCAPE")) Manager->gameExit = true;   // 정지상태일때, ESC 누르면 종료

            break;

        case Gamestate::game :  // 게임로직

            // if (IsButtonJumpPressed()) bird.Jump();  // 플레이어 점프
            if (IsButtonPressed("Jump")) bird.Jump();  // 플레이어 점프

            // if (IsButtonESCPressed()) 
            if (IsButtonPressed("ESCAPE"))
            {
                gamestate = Gamestate::pause;  // 게임정지로 바꾸기 
                PauseMusicStream(Manager->music);
            }

            bird.Update(); // 플레이어 업데이트 로직

            ObstacleLogic(); // 장애물 로직 부르기

            items->Update(&bird);  // 코인이나 하트 등 아이템 업데이트 로직

            // 게임 리셋
            if (bird.Life <= 0) Reset();  // 생명력이 0이하면 게임 리셋 

            break; 
        
        default: 
            break;
    }
}

// 액션키 매핑
// bool SettingScreen::IsActionPressed()
// {
//     if (IsGamepadAvailable(gamepad))
//     {    
//         return IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);  // A버튼을 눌렀는지 리턴
//     }else 
//     {
//         return  IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_E);
//     }
// }

// 장애물 로직
void Game::ObstacleLogic()
{
            // 장애물 로직 시작 
            // 타이머를 만족하면 새로운 파이프 장애물을 만든다. 
            timer++;
            if (timer >= maxTimer) 
            {
                timer = 0; 
                maxTimer = GetRandomValue(120, 240); 
                Obstacle newPipe;
                newPipe.Init(&UpPipeImage, &DownPipeImage); 
                pipes.push_back(newPipe);
                items->SetTimer();
            }

            // 전체 파이프를 루프 돌려서 업데이트 메서드 실행
            for (unsigned int i =0; i < pipes.size(); i++)
            {
                pipes[i].Update();

                // 장애물에 부딪히는지 여부 
                if (!bird.GetInvincible())
                {
                    if (pipes[i].CheckCollide(bird.GetPosition())) 
                    {
                        bird.Hurt();
                    }
                }
                // 장애물을 패스해서 점수획득 
                if (pipes[i].checkPassing(bird.GetPosition())) bird.Score++;


                // 장애물이 화면 밖으로 나가면 배열에서 제거
                if (pipes[i].GetPipePosition() <= 0) 
                {
                    // pipes[i].UnloadPipeTexture();
                    pipes.erase(pipes.begin() + i);   // 장애물이 왼쪽 끝에 가면 배열에서 제거 
                }
            }  
            // 장애물 로직 끝
}

// 게임 리셋하기
void Game::Reset()
{
    bird.Init();
    pipes.clear();

    // 장애물 초기화하기 
    Obstacle pipe = Obstacle();  
    pipe.Init(&UpPipeImage, &DownPipeImage);
    maxTimer = GetRandomValue(120, 240);
    pipes.push_back(pipe);
}

void Game::Draw()
{ 
    // Draw
    switch(gamestate)
    {
        case Gamestate::pause :   // 정지화면 그리기 
            DrawBackground(); // 배경그리기 

            // 정지화면 
            DrawRectangle(GetScreenWidth() / 2 - 180, GetScreenHeight() / 2 - 60, 360, 120, DARKBROWN);
            DrawText("Press Arrow Up  if you continue", GetScreenWidth() / 2 - 160, GetScreenHeight() / 2 -20, 20, MAGENTA);
            DrawText("Press ESC to Exit Game", GetScreenWidth() / 2 - 160, GetScreenHeight() / 2 + 10, 20, MAGENTA);
            break;

        case Gamestate::game:  // 게임화면 그리기 
            DrawBackground(); // 배경그리기 

            // 게임 UI  
            if (IsGamepadAvailable(gamepad)) 
            {
                DrawText("Pause : Press ESC", GetScreenWidth() - 200, 20, 20, DARKGRAY);
                DrawText(TextFormat("Pipes : %d", pipes.size()), GetScreenWidth() - 200, 40, 20, DARKGRAY);
                DrawText(TextFormat("Score : %d", bird.Score), GetScreenWidth() - 200, 60, 20, DARKGRAY);
                DrawText(TextFormat("Lifes : %d", bird.Life), GetScreenWidth() - 200, 80, 20, DARKGRAY);
                DrawText(TextFormat("GP%d: %s", gamepad, GetGamepadName(gamepad)), GetScreenWidth() - 200, 100, 20, BLACK);

            }else
            {
                DrawText("Pause : Select button", GetScreenWidth() - 200, 20, 20, DARKGRAY);
                DrawText(TextFormat("Pipes : %d", pipes.size()), GetScreenWidth() - 200, 40, 20, DARKGRAY);
                DrawText(TextFormat("Score : %d", bird.Score), GetScreenWidth() - 200, 60, 20, DARKGRAY);
                DrawText(TextFormat("Lifes : %d", bird.Life), GetScreenWidth() - 200, 80, 20, DARKGRAY);
            };
            break;
    }
}

// 공통되는 배경그리기 함수 
void Game::DrawBackground()
{
    // 배경그리기
    ClearBackground(BLACK); 
    DrawTexturePro(backgroundImage, Rectangle{0, 0, 800, 600}, Rectangle{0, 0, 1200, 800}, Vector2{0, 0}, 0, WHITE);

    // 전체 파이프를 루프 돌려서 드로우 메서드 실행
    for (unsigned int j =0; j < pipes.size();j++)
    {
        pipes[j].Draw();
    }
    // 아이템들 그리기
    items->Draw();
    // 플레이어 그리기
    bird.Draw();
}
