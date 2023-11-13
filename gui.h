/*  =========================================
Raylib GUI Libary 
Ver. 1.1   2023. 11. 5. Pointer Button
Ver. 1.0   2023. 10. 30.  Button. Slider, Image Slider 
Created by Dongkun Lee. 
    ==========================================
*/ 



#pragma once
#include <string>
#include "raylib.h"
#include "config.h"
#include "buttonActionMap.h"

class GUI
{
    public:
        GUI();
        GUI(int button_x, int button_y, int button_width, int button_height, const char* button_title, Font*  _font);
        virtual bool Update(); 
        virtual void Draw();
        void Tick();
        bool GetChecked();
        void Checked();
        void UnChecked();
        void SetText(const char* button_title);

    protected:
        int x, y, width, height;
        const char* title;
        bool isChecked = false;
        Rectangle rect;
        Font* font;
};

// Button Pinter. It has pointer to title string

class ButtonPointer : public GUI
{
    private: 
        std::string* titlePointer;
    public :
        ButtonPointer();
        ButtonPointer(int button_x, int button_y, int button_width, int button_height, std::string* button_title, Font*  _font);
        virtual void Draw();
};

class ImgButton : public GUI
{
    private : 
        Texture2D* boxImage;

    public:
        ImgButton();
        ImgButton(int button_x, int button_y, int button_width, int button_height, Texture2D* _image);
        virtual void Draw();
};

/*===============================
    GUI CheckBox
    boxenabled = _box[0]; 
    boxdisabled = _box[1];
    boxenalbedChecked = _box[2];
    boxdisabledChecked = _box[3];
    ===============================
*/

class GUICheckBox : public GUI
{
    private : 
        bool* isHasValue; 

        Texture2D* boxenabled;
        Texture2D* boxenalbedChecked;
        Texture2D* boxdisabled; 
        Texture2D* boxdisabledChecked;

    public :
        GUICheckBox();
        GUICheckBox(int box_x, int box_y, bool *isValue, Texture2D _box[]);
        virtual bool Update();
        virtual void Draw();
};


class GUISlider : public GUI
{
    protected:
        float padding;
        Rectangle leftButton;
        Rectangle rightButton;

        float *sliderValue;
        bool changeValueMode = false;
        void ValueUp();
        void ValueDown();

    public:
        enum class arrowCheck {
            none = 0, left, right, slider
        }; 
        GUISlider();
        GUISlider(int slider_x, int slider_y, int slider_width, int slider_height, const char* slider_title, Font *_font, float *value);
        virtual bool Update(); 
        virtual void Draw();
        bool MouseSliding();
        
        arrowCheck arrow = arrowCheck::none;
};

/* ===================================
Image Slider need 6 images 
    imgSlider = &_img[0];
    imgSliderBar = &_img[1];
    imgSliderLeftEnabled = &_img[2];
    imgSliderRightEnabled = &_img[3];
    imgSliderLeftDisabled = &_img[4];
    imgSliderRightDisabled = &_img[5];
    ===================================
*/

class GUISliderImg : public GUISlider
{
    private : 
        Texture2D* imgSlider;
        Texture2D* imgSliderBar;
        Texture2D* imgSliderLeftEnabled;
        Texture2D* imgSliderRightEnabled;
        Texture2D* imgSliderLeftDisabled;
        Texture2D* imgSliderRightDisabled;

    public : 
        GUISliderImg();
        GUISliderImg(int slider_x, int slider_y, int slider_width, int slider_height, const char* slider_title, Font *_font, float *value, Texture2D _img[]);
        virtual void Draw();
};

