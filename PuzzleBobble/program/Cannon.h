#pragma once
#include "DxLib.h"

class Cannon {
public:
    float x, y;
<<<<<<< HEAD
    float angle; 
=======
    float angle; // 度（Degree）で管理
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    int currentColor;

    void Init() {
        x = 320; y = 400; angle = -90.0f;
<<<<<<< HEAD
        currentColor = GetRand(3) + 1; 
=======
        currentColor = GetRand(3) + 1; // 最初にランダムで1色決めておく
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    }

    Cannon();
    void Init(float startX, float startY);
<<<<<<< HEAD
    void Update(); 
    void Draw();  
=======
    void Update(); // 左右キーでの回転処理
    void Draw();   // 砲身の描画
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
};