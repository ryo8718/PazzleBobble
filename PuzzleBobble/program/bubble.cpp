#include "Bubble.h"
#include "DxLib.h"
#include "Stage.h" 

extern int bubble_images[100];

Bubble::Bubble() : x(0), y(0), vx(0), vy(0), color(0), isActive(false) {}

void Bubble::Init(float startX, float startY, float speedX, float speedY, int col) {
    x = startX;
    y = startY;
    vx = speedX;
    vy = speedY;
    color = col;
    isActive = true;
}

void Bubble::Update() {
    if (!isActive) return;

    x += vx;
    y += vy;

    // 壁の反射ロジックをここに移植
    if (x < OFFSET_X) {
        x = (float)OFFSET_X;
        vx *= -1.0f;
    }
    float rightLimit = (float)(OFFSET_X + (STAGE_COLS * B_DIAMETER));
    if (x > rightLimit) {
        x = rightLimit;
        vx *= -1.0f;
    }
}

void Bubble::Draw() {
    if (!isActive) return;
    unsigned int drawColor;
    switch (color) {
    case 1: drawColor = GetColor(255, 0, 0); break; // 赤
    case 2: drawColor = GetColor(0, 255, 0); break; // 緑
    case 3: drawColor = GetColor(0, 0, 255); break; // 青
    case 4: drawColor = GetColor(255, 255, 0); break; // 黄
    default: drawColor = GetColor(255, 255, 255); break; // 白（エラー防止）
    }
    // 指定の座標に円を描く
    DrawCircle((int)x, (int)y, B_RADIUS, drawColor, TRUE);

    // printfDx("ShotX:%.1f ShotY:%.1f\n", x, y);
}