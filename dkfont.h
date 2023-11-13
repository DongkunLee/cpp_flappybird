#pragma once
#ifndef __DKFONT__
#define __DKFONT__
#include <stdlib.h>
#include "raylib.h"
#include "string.h"
#include <iostream>

Font LoadBMFontEX(const char *fileName);
int GetLine(const char *origin, char *buffer, int maxLength);

#endif