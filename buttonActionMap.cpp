// GamePad and Keyboard action mapping Library
// Written by Dongkun Lee. 2023. 10. 24. 

#include "buttonActionMap.h"
#define BUTTONCOUNT 5

bool YAxisMode = false;
bool XAxisMode = false;

struct buttonMap keyMap[BUTTONCOUNT]  = {{"none", GAMEPAD_BUTTON_UNKNOWN, KEY_NULL},
            {"Jump", GAMEPAD_BUTTON_RIGHT_FACE_DOWN, KEY_ENTER}, 
            {"ESCAPE", GAMEPAD_BUTTON_MIDDLE_LEFT, KEY_ESCAPE}, 
            {"Start", GAMEPAD_BUTTON_MIDDLE_RIGHT, KEY_ENTER}, 
            {"Interact", GAMEPAD_BUTTON_RIGHT_FACE_UP, KEY_E}
            };
 
 bool IsButtonPressed(std::string inputName)
 {
    int index = 0;

    for (int i =0; i  < BUTTONCOUNT;i++)
    {
        if (keyMap[i].name == inputName)  // 입력된 버튼이 버튼맵상에서 일치하는지 확인 
        {
            index = i;
            for (int i = 0; i < 4; i++)
            {
                if (IsGamepadAvailable(i))
                return IsGamepadButtonPressed(i, keyMap[index].padButtonName);
            }
            return IsKeyPressed(keyMap[index].keyboardKeyName);

            break;
        }
    }

   return false;
 }




bool IsLeftAxisUpChecked() // 윗방향 스틱 체크 
{
    for (int i =0; i < 4; i++)
    {
        if (IsGamepadAvailable(i))
        {
            float YAxisValue = GetGamepadAxisMovement(i, GAMEPAD_AXIS_LEFT_Y); 

            if (YAxisValue < -0.17 && !YAxisMode)  // 조이스틱 축이 딱 0이 안될 가능성도 있으므로 임의의 숫자보다 큰 값을 주게 하였음
            {   
                YAxisMode = true;
                return true;
            }else 
            {
                if (YAxisValue >= -0.17 && YAxisValue <= 0.17) YAxisMode = false;
            }
            return false;
        }
    }

    return IsKeyPressed(KEY_UP);
    
}

bool IsLeftAxisDownChecked()  // 아래방향 스틱 체크. 왼쪽 스틱
{
    for (int i = 0; i < 4; i++)
    {
        if (IsGamepadAvailable(0))
        {
            float YAxisValue = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y); 

            if (YAxisValue > 0.17 && !YAxisMode)  // 조이스틱 축이 딱 0이 안될 가능성도 있으므로 임의의 숫자보다 큰 값을 주게 하였음
            {   
                YAxisMode = true;
                return true;
            }else 
            {
                if (YAxisValue >= -0.17 && YAxisValue <= 0.17) YAxisMode = false;
            }

            return false;

        }
    }
    return IsKeyPressed(KEY_DOWN);
}

bool IsLeftAxisRightChecked() // 오른쪽 방향 스틱체크. 왼쪽 스틱
{
    for (int i = 0; i < 4; i++)
    {
        if (IsGamepadAvailable(0))
        {
            float XAxisValue = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X); 

            if (XAxisValue > 0.17 && !XAxisMode)  // 조이스틱 축이 딱 0이 안될 가능성도 있으므로 임의의 숫자보다 큰 값을 주게 하였음
            {   
                XAxisMode = true;
                return true;
            }else 
            {
                if (XAxisValue >= -0.17 && XAxisValue <= 0.17) XAxisMode = false;
            }

            return false;

        }
    }
    return IsKeyPressed(KEY_RIGHT);
}

bool IsLeftAxisLeftChecked() // 왼쪽 방향 스틱체크. 왼쪽 스틱
{
    for (int i = 0; i < 4; i++)
    {
        if (IsGamepadAvailable(0))
        {
            float XAxisValue = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X); 

            if (XAxisValue < -0.17 && !XAxisMode)  // 조이스틱 축이 딱 0이 안될 가능성도 있으므로 임의의 숫자보다 큰 값을 주게 하였음
            {   
                XAxisMode = true;
                return true;
            }else 
            {
                if (XAxisValue >= -0.17 && XAxisValue <= 0.17) XAxisMode = false;
            }

            return false;

        }
    }
    return IsKeyPressed(KEY_LEFT);
}