#pragma once
#include "DxLib.h"

class Cannon {
public:
    float x, y;
    float angle; // 度（Degree）で管理
    int currentColor;

    void Init() {
        x = 320; y = 400; angle = -90.0f;
        currentColor = GetRand(3) + 1; // 最初にランダムで1色決めておく
    }

    Cannon();
    void Init(float startX, float startY);
    void Update(); // 左右キーでの回転処理
    void Draw();   // 砲身の描画
};