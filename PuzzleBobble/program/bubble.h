#pragma once
#include "DxLib.h"
<<<<<<< HEAD
#include "Game.h"
=======
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0

class Bubble {
public:
    float x, y;
    float vx, vy;
    int color;
    bool isActive;
<<<<<<< HEAD

    // スプライトベース描画用のアニメーション状態
    int animFrame;       // 現在のフレーム番号
    int animTimer;       // フレーム更新用のタイマー
    BubbleState animState;       // 現在の状態（enum）
    // 固定（くっつき）アニメーション用
    bool isAttaching;    // くっつきアニメーション再生中か
    int attachR, attachC; // 固定先のセル座標
    bool attachComplete;  // くっつきアニメーション再生完了フラグ

    void StartAttach(int r, int c); // 固定アニメ開始
    bool IsAttachComplete();
    int GetAttachR();
    int GetAttachC();

    Bubble();
    void Init(float startX, float startY, float speedX, float speedY, int col);
    void Update(); //
    void Draw();   //
=======

    Bubble();
    void Init(float startX, float startY, float speedX, float speedY, int col);
    void Update(); // 移動と壁反射の処理
    void Draw();   // 自身の描画
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
};