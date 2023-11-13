#include "gui.h"
#include <stdio.h>

Vector2 mousePoint = { 0.0f, 0.0f };

GUI::GUI()
{}

GUI::GUI(int button_x, int button_y, int button_width, int button_height, const char* button_title, Font*  _font)
{
    x = button_x;
    y = button_y;
    width = button_width;
    height = button_height;
    title = button_title;
    rect = Rectangle{float(x), float(y), float(width), float(height)};
    font = _font;
}

bool GUI::GetChecked()   
{
    return isChecked;
}

void GUI::Checked()    // 현재 버튼이 체크된 상태로 하기 
{
    isChecked = true;
    SetMousePosition(x + width / 2, y+height/2);  // 마우스 커서를 현재 버튼의 정중앙에 넣기 
}

void GUI::SetText(const char* button_title)
{
    title = button_title;
}

void GUI::UnChecked()  // 현재 버튼이 체크 해제된 상태로 하기 
{
    isChecked = false;
}

bool GUI::Update()  // 마우스가 버튼 위에 위치해 있는지를 체크
{
    mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, rect)) isChecked = true;
     else isChecked = false; 

    return false;
}

void GUI::Draw()  // 버튼 그리기
{
    DrawRectangle(x, y, width, height, DARKGREEN);   // 버튼을 그린다. 
    
    Vector2 length = MeasureTextEx(*font, title, 32, 5); // 글자의 포인트는 32으로 가정할 것이다.  32으로 가정한 글자의 가로 픽셀 크기를 구한다. 

    // 텍스트 출력
    Vector2 pos = {(float)x  + (width / 2) - (length.x / 2), (float)y + (height /2) - (length.y / 2)};     // 글자를 가로 및 세로 가운데 정렬한다. 
    DrawTextEx(*font, title, pos, 32, 5, DARKBROWN);  

    if (isChecked)
    {
        DrawRectangle(x, y, width, height, Color{255, 255, 255, 85});   // 버튼을 그린다. 
        DrawRectangleLinesEx(rect, 4, Fade(BLACK, 0.3f));         // 버튼 꾸미기
    }
}

void GUI::Tick()
{
    BeginDrawing();    
    Update();
    Draw();
    EndDrawing(); 
}

ButtonPointer::ButtonPointer() {}

ButtonPointer::ButtonPointer(int button_x, int button_y, int button_width, int button_height, std::string* button_title, Font*  _font)
{
    x = button_x;
    y = button_y;
    width = button_width;
    height = button_height;
    titlePointer = button_title;   // 포인터를 대입한다. 버튼 자체는 문자열을 가지고 있지 않고 문자열에 대한 주소만 저장한다.
    rect = Rectangle{float(x), float(y), float(width), float(height)};
    font = _font;    
}

void ButtonPointer::Draw()
{
    DrawRectangle(x, y, width, height, DARKGREEN);   // 버튼을 그린다. 
    
    Vector2 length = MeasureTextEx(*font, (*titlePointer).c_str(), 32, 5); // 글자의 포인트는 32으로 가정할 것이다.  32으로 가정한 글자의 가로 픽셀 크기를 구한다. 

    // 텍스트 출력
    Vector2 pos = {(float)x  + (width / 2) - (length.x / 2), (float)y + (height /2) - (length.y / 2)};     // 글자를 가로 및 세로 가운데 정렬한다. 
    DrawTextEx(*font, (*titlePointer).c_str(), pos, 32, 5, DARKBROWN);  

    if (isChecked)  // 선택된 경우
    {
        DrawRectangle(x, y, width, height, Color{255, 255, 255, 85});   // 버튼을 그린다. 
        DrawRectangleLinesEx(rect, 4, Fade(BLACK, 0.3f));         // 버튼 꾸미기
    }
}


// Image Button 
ImgButton::ImgButton() {}

ImgButton::ImgButton(int button_x, int button_y, int button_width, int button_height, Texture2D* _image)
{
    x = button_x;
    y = button_y;
    width = button_width;
    height = button_height;
    boxImage = _image;    
    rect = Rectangle{float(x), float(y), float(width), float(height)};
}

void ImgButton::Draw()
{
    DrawTexture(*boxImage, x, y, WHITE);

    if (isChecked) DrawRectangleLinesEx(rect, 4, Fade(BLACK, 0.3f));         // 버튼 꾸미기
}

/* =========================================
    GUI CheckBox   made by Dongkun Lee  
    2023. 10. 30. 
    ========================================= */
GUICheckBox::GUICheckBox() {} 

GUICheckBox::GUICheckBox(int box_x, int box_y, bool *isValue, Texture2D _box[])
{
    boxenabled = &_box[0]; 
    boxdisabled = &_box[1];
    boxenalbedChecked = &_box[2];
    boxdisabledChecked = &_box[3];

    x = box_x;
    y = box_y;
    width = boxenabled->width;
    height = boxenabled->height;
    rect = Rectangle{float(x), float(y), float(width), float(height)}; 

    isHasValue = isValue;
}

bool GUICheckBox::Update()
{
    mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, rect)) isChecked = true;
     else isChecked = false; 

    if (isChecked && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) *isHasValue = !*isHasValue;

    if (isChecked && IsButtonPressed("Jump")) *isHasValue = !*isHasValue;


    return false;
}

void GUICheckBox::Draw()
{
    if(isChecked)  //  마우스가 위에 있어서 활성화된 상태 
    {
        if (*isHasValue)  //  체크박스가 선택된 상태
            DrawTexture(*boxenalbedChecked, x, y, WHITE);
        else DrawTexture(*boxenabled, x, y, WHITE);  //  체크박스 선택 없음 
    }else //  마우스가 없어서  GUI가 비활성화된 상태 
    {
        if (*isHasValue) // 체크박스가 선택된 상태 
            DrawTexture(*boxdisabledChecked, x, y, WHITE);
        else DrawTexture(*boxdisabled, x, y, WHITE);
    }
}


/* =========================================
    GUI Slider   made by Dongkun Lee 
    2023. 10. 29. 
    ========================================= */

GUISlider::GUISlider() {}

GUISlider::GUISlider(int slider_x, int slider_y, int slider_width, int slider_height, const char* slider_title, Font* _font, float *value)
{
    x = slider_x;
    y = slider_y;
    width = slider_width;
    height = slider_height;
    title = slider_title;
    rect = Rectangle{float(x), float(y), float(width), float(height)};
    font = _font; 
    padding = 20.0f;
    leftButton = Rectangle{float(x) - padding -float(height), float(y), float(height), float(height) };
    rightButton = Rectangle{float(x) + float(width) + padding, float(y), float(height), float(height)};
    sliderValue = value;  // 슬라이더 값은 주소로 가져온다. 호출하는 쪽에서 값이 바뀌면 슬라이더 내부의 값도 바뀐다. 
}

bool GUISlider::Update()   // 슬라이더 조절 로직
{
    mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, leftButton)) arrow = arrowCheck::left;  // 슬라이더의 왼쪽 버튼 체크 상태 확인
     else if (CheckCollisionPointRec(mousePoint, rightButton)) arrow = arrowCheck::right;  // 슬라이더의 오른쪽 버튼 체크 상태 확인
     else if (CheckCollisionPointRec(mousePoint, rect)) arrow = arrowCheck::slider;  // 마우스가 슬라이더를 가리키는지 확인
     else arrow = arrowCheck::none; 

    // 슬라이더의 왼쪽 버튼 
    if (arrow == arrowCheck::left && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        ValueDown();
        return true;
    }

    // 슬라이더의 오른쪽 버튼 
    if (arrow == arrowCheck::right && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        ValueUp();
        return true;
    }

    // 슬라이더가 선택된 상태에서는  좌우 키 조작이 가능하게 한다
    if (isChecked)
    {
        if (IsLeftAxisLeftChecked()) {ValueDown(); return true; } 

        if (IsLeftAxisRightChecked()) {ValueUp(); return true; }
    }

    return MouseSliding();
}

// 슬라이더의 값을 올리는 함수 
void GUISlider::ValueUp()
{
    *sliderValue += 0.1;
    if (*sliderValue >= 1.0f) *sliderValue = 1.0f;
}

// 슬라이더의 값을 내리는 함수
void GUISlider::ValueDown()
{
    *sliderValue -= 0.1;
    if (*sliderValue <= 0.0f) *sliderValue = 0.0f;
}

// 슬라이더 그리기
void GUISlider::Draw()
{
   // DrawRectangle(x, y, width, height, DARKGREEN);   // 버튼을 그린다. 
  
    // 슬라이더 그리기 
    if (isChecked)
    {
        DrawRectangle(x, y, width, height, Color{255, 255, 255, 85});   // 버튼을 그린다. 
        DrawRectangleLinesEx(rect, 4, Fade(BLACK, 0.3f));         // 버튼 꾸미기
    }else 
    {
        DrawRectangle(x, y, width, height, Color{255, 255, 255, 85});   // 버튼을 그린다. 
    }

    // 양옆에 화살표
    DrawRectangleRec(leftButton,  ORANGE );
    DrawRectangleRec(rightButton, ORANGE );
    DrawRectangle(x, y, width *  *(sliderValue), height, RAYWHITE);   // 버튼을 그린다. 슬라이더 값이 포인터형이므로 역참조로 해야 한다. 

    // 텍스트 출력
    // Vector2 length = MeasureTextEx(*font, title.c_str(), 32, 5); // 글자의 포인트는 32으로 가정할 것이다.  32으로 가정한 글자의 가로 픽셀 크기를 구한다. 
    // Vector2 pos = {(float)x  + (width / 2) - (length.x / 2), (float)y + (height /2) - (length.y / 2)};     // 글자를 가로 및 세로 가운데 정렬한다. 
    // DrawTextEx(*font, title.c_str(), pos, 32, 5, DARKBROWN);  
    DrawText(TextFormat("%.2f", *sliderValue),  x + width/2 - 16,  y + height/2 - 16, 32, WHITE); // 글자를 가로 및 세로 가운데 정렬한다. 

    // 화살표 선택했는지 여부 
    if (arrow == arrowCheck::left)
    {
        DrawRectangleLinesEx(leftButton, 4, Fade(BLACK, 0.3f));
    }else if (arrow == arrowCheck::right)
    {
        DrawRectangleLinesEx(rightButton, 4, Fade(BLACK, 0.3f));
    }else if (arrow == arrowCheck::slider)
    {
        DrawRectangleLinesEx(rect, 4, Fade(BLACK, 0.3f));
    }
}

// 마우스로 슬라이딩
bool GUISlider::MouseSliding()
{
        // 슬라이더의 가운데를 누른 상태 체크 
    if (arrow == arrowCheck::slider && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) changeValueMode = true;  // 마우스로 슬라이더 값을 조절 할 수 있음

    // 슬라이더 값을 조절할 수 있는 상태에서
    if (changeValueMode)
    {
        if (GetMousePosition().x >= rect.x + rect.width) SetMousePosition(rect.x + rect.width, rect.y + rect.height / 2);  // 마우스 범위 제한
        if (GetMousePosition().x <= rect.x) SetMousePosition(rect.x, rect.y + rect.height / 2);  // 마우스 범위 제한 
        
        float rawValue = GetMousePosition().x - rect.x;   // 현재 마우스의 위치를 통해 가로 값을 정하기

        if (rawValue <= 0) rawValue = 0;    // 슬라이더 가로 값의 좌측 한계 
        if (rawValue >= rect.width) rawValue = rect.width;  // 슬라이더 가로 값의 우측 한계 

        float perValue = rawValue / rect.width;  // 슬라이더 가로 값을 퍼센트로 만들기 
        *sliderValue = perValue;  // 슬라이더 값으로 넘겨주기

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))   // 마우스 왼쪽 버튼을 떼면 볼륨 설정하고, 변환 모드를 해제함
        {
            changeValueMode = false;
            return true;   // 볼륨이 바뀌면 호출한 쪽에 true를 리턴해 준다
        }

        return false;
    }
    return false;
}

/* =========================================
    GUI SliderImg   made by Dongkun Lee 
    2023. 10. 30.
    Image Slider need 6 images 
    imgSlider = &_img[0];
    imgSliderBar = &_img[1];
    imgSliderLeftEnabled = &_img[2];
    imgSliderRightEnabled = &_img[3];
    imgSliderLeftDisabled = &_img[4];
    imgSliderRightDisabled = &_img[5];
     ========================================= */

GUISliderImg::GUISliderImg() {}

GUISliderImg::GUISliderImg(int slider_x, int slider_y, int slider_width, int slider_height, const char* slider_title, Font *_font, float *value, Texture2D _img[])
{
    x = slider_x;
    y = slider_y;
    width = slider_width;
    height = slider_height;
    title = slider_title;
    rect = Rectangle{float(x), float(y), float(width), float(height)};
    font = _font; 
    padding = 20.0f;

    sliderValue = value;  // 슬라이더 값은 주소로 가져온다. 호출하는 쪽에서 값이 바뀌면 슬라이더 내부의 값도 바뀐다.     
    imgSlider = &_img[0];
    imgSliderBar = &_img[1];
    imgSliderLeftEnabled = &_img[2];
    imgSliderRightEnabled = &_img[3];
    imgSliderLeftDisabled = &_img[4];
    imgSliderRightDisabled = &_img[5];

    leftButton = Rectangle{float(x) - padding -float(imgSliderLeftEnabled->width), float(y), float(imgSliderLeftEnabled->width), float(height) };
    rightButton = Rectangle{float(x) + float(width) + padding, float(y), float(imgSliderRightEnabled->width), float(height)};
    
}

void GUISliderImg::Draw()
{
    // 슬라이더 그리기 
    DrawTextureV(*imgSlider, Vector2{rect.x, rect.y}, WHITE); 
    if (isChecked) DrawRectangleLinesEx(rect, 4, Fade(RAYWHITE, 0.3f));         // 슬라이더 활성화 상태 그리기

    // 양옆에 화살표 그리기
    if (arrow == arrowCheck::left)
    {
        DrawTextureV(*imgSliderLeftEnabled, Vector2{leftButton.x, leftButton.y}, WHITE);
        DrawTextureV(*imgSliderRightDisabled, Vector2{rightButton.x, rightButton.y}, WHITE);
    }else if (arrow == arrowCheck::right)
    {
        DrawTextureV(*imgSliderLeftDisabled, Vector2{leftButton.x, leftButton.y}, WHITE);
        DrawTextureV(*imgSliderRightEnabled, Vector2{rightButton.x, rightButton.y}, WHITE);
    }else 
    {
        DrawTextureV(*imgSliderLeftDisabled, Vector2{leftButton.x, leftButton.y}, WHITE);
        DrawTextureV(*imgSliderRightDisabled, Vector2{rightButton.x, rightButton.y}, WHITE);
    }
     
    DrawTextureV(*imgSliderBar, Vector2{rect.x + rect.width * *(sliderValue) - imgSliderBar->width / 2 ,rect.y}, WHITE);
  //  DrawRectangle(x, y, width *  *(sliderValue), height, RAYWHITE);   // 슬라이더를 그린다. 슬라이더 값이 포인터형이므로 역참조로 해야 한다. 

    // 텍스트 출력
    DrawText(TextFormat("%.2f", *sliderValue),  x + width/2 - 16,  y + height/2 - 16, 32, WHITE); // 글자를 가로 및 세로 가운데 정렬한다.  
}