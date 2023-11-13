// GamePad and Keyboard action mapping Library
// Written by Dongkun Lee. 2023. 10. 24. 

#pragma once
#include "raylib.h"
#include <string>

struct buttonMap
{
    std::string name;
    GamepadButton padButtonName;
    KeyboardKey keyboardKeyName;
};


bool IsButtonPressed(std::string inputName); 

bool IsLeftAxisUpChecked();

bool IsLeftAxisDownChecked();

bool IsLeftAxisRightChecked();

bool IsLeftAxisLeftChecked();