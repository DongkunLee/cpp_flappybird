#include "items.h"
#include <stdio.h>

Items* Items::instance;

void Items::Init()
{
    menuManager = SceneManager::GetInstance();  
    // 코인 
    CoinSprite = LoadTexture("Assets/coinspritesheets.png");        // Texture loading
    fxCoin = LoadSound("Assets/Coin01.wav");
    SetSoundVolume(fxCoin, menuManager->volume);
    coins.clear();

    // 생명
    LifeSprite = LoadTexture("Assets/health.png");  
    fxLife = LoadSound("Assets/chipquest.wav");
    SetSoundVolume(fxLife, menuManager->volume);
    lifes.clear();
    // 스폰 변수
    canSpawn = true;
    timer = 0;
}

void Items::SetTimer()
{
    canSpawn = false;
    timer = 0;
}

void Items::Update(Bird* _player)
{
    // 파이프를 지나갈 떄 까지는 코인 스폰을 시키지 않는다. 
    if (!canSpawn) 
    {
        timer++;
        if (timer > 55)   // 파이프가 100픽셀이고 스피드가 2이므로 50프레임이 지나야 파이프와 겹치지 않는다. 넉넉하게 55프레임으로 하였다.
        {
            canSpawn = true;
            timer = 0;
        }
    }else
    {
        int spawn = GetRandomValue(0, 1000); // 코인이 발생할 확률 
        if (spawn < 2 && canSpawn == true) // 코인이 발생할 확률을 1000분의 10 즉 1%로 설정함
        {
            Coin* coin = new Coin(&CoinSprite);           
            coins.push_back(*coin);
            delete coin;
        }

        int spawnlife = GetRandomValue(0, 1000); // 코인이 발생할 확률 
        if (spawnlife < 1 && canSpawn == true) // 코인이 발생할 확률을 1000분의 10 즉 1%로 설정함
        {
            Life* life = new Life(&LifeSprite, 8, 3, 1);
            lifes.push_back(*life);
            delete life;
        }
    }


    // 각 코인별로 로직을 실행한다.  
    if (coins.size() > 0)
    {
        for (unsigned int i = 0;i < coins.size();i++)
        {
            coins[i].Update();  // 개별 코인 업데이트 함수 

            // 코인과 플레이어간의 상호작용
            Rectangle birdRect = _player->GetPosition(); // 플레이어 위치 확인
            
            if (coins[i].GetCollision(birdRect))  // 코인과 플레이어가 부딪히는지 확인
            {
                _player->SetAddScore(coins[i].GetAddValue());  // 플레이어 점수를 올림. 여기에서는 3점을 올리기로 함 
                PlaySound(fxCoin);  // 코인 획득 사운드
                coins.erase(coins.begin() + i);   // 코인이 플레이어와 부딪히면  배열에서 제거 
            }else {
                // 코인을 배열에서 제거하기
                if (coins[i].GetPosition() <= 0) 
                    coins.erase(coins.begin() + i);   // 코인이 왼쪽 끝에 가면 배열에서 제거 
            }
        }   
    }

    // 각 생명별로 로직을 실행한다.  
    if (lifes.size() > 0)
    {
        for (unsigned int i = 0;i < lifes.size();i++)
        {
            lifes[i].Update();  // 개별 코인 업데이트 함수 

            // 생명 아이템과 플레이어간의 상호작용
            Rectangle birdRect = _player->GetPosition(); // 플레이어 위치 확인
            
            if (lifes[i].GetCollision(birdRect))  // 생명아이템과 플레이어가 부딪히는지 확인
            {
                _player->SetAddLife(lifes[i].GetAddValue());  // 플레이어 생명력을 올림. 여기에서는 1점을 올리기로 함 
                PlaySound(fxLife);  // 코인 획득 사운드
                lifes.erase(lifes.begin() + i);   // 생명아이템이 플레이어와 부딪히면  배열에서 제거 
            }else {
                // 생명아이템을 배열에서 제거하기
                if (lifes[i].GetPosition() <= 0) 
                    lifes.erase(lifes.begin() + i);   // 생명아이템이 왼쪽 끝에 가면 배열에서 제거 
            }
        }   
    }
}

void Items::Draw()
{
     if (coins.size() >0 ) 
     {
        for (unsigned int i = 0;i< coins.size();i++)
        {
            coins[i].Draw();
        }
     }

     if (lifes.size() >0 ) 
     {
        for (unsigned int i = 0;i< lifes.size();i++)
        {
            lifes[i].Draw();
        }
     }
}

Items::~Items()
{
    UnloadTexture(CoinSprite);       // Texture unloading
    UnloadSound(fxCoin);  // Sound unloading

    UnloadTexture(LifeSprite);       // Texture unloading
    UnloadSound(fxLife);  // Sound unloading
}