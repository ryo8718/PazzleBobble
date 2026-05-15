#pragma once
#include "DxLib.h"

class Bubble {
public:
    float x, y;
    float vx, vy;
    int color;
    bool isActive;

    Bubble();
    void Init(float startX, float startY, float speedX, float speedY, int col);
    void Update(); // 移動と壁反射の処理
    void Draw();   // 自身の描画
};