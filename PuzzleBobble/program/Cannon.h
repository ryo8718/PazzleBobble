#pragma once
#include "DxLib.h"

class Cannon {
public:
    float x, y;
    float angle; 
    int currentColor;

    void Init() {
        x = 320; y = 400; angle = -90.0f;
        currentColor = GetRand(3) + 1; 
    }

    Cannon();
    void Init(float startX, float startY);
    void Update(); 
    void Draw();  
};