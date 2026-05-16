#include "Bubble.h"
#include "DxLib.h"
#include "Stage.h" 

<<<<<<< HEAD
// Bubble::Bubble
Bubble::Bubble() : x(0), y(0), vx(0), vy(0), color(0), isActive(false),
    animFrame(0), animTimer(0), animState(BUBBLE_WAIT), isAttaching(false), attachR(-1), attachC(-1), attachComplete(false) {}

=======
extern int bubble_images[100];

Bubble::Bubble() : x(0), y(0), vx(0), vy(0), color(0), isActive(false) {}

>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
void Bubble::Init(float startX, float startY, float speedX, float speedY, int col) {
    x = startX;
    y = startY;
    vx = speedX;
    vy = speedY;
    color = col;
    isActive = true;
<<<<<<< HEAD
    // (再)初期化時にアニメーション状態をリセットする
    animFrame = 0;
    animTimer = 0;
    animState = BUBBLE_WAIT; // 待機状態から開始
    isAttaching = false;
    attachComplete = false;
}

void Bubble::StartAttach(int r, int c) {
    isAttaching = true;
    attachComplete = false;
    attachR = r;
    attachC = c;
    animState = BUBBLE_ATTACH;
    animFrame = 0;
    animTimer = 0;
    // 止める
    vx = 0.0f;
    vy = 0.0f;
    // 固定時は描画対象としてアクティブにしておく
    isActive = false;
}

bool Bubble::IsAttachComplete() {
    return attachComplete;
}

int Bubble::GetAttachR() { return attachR; }
int Bubble::GetAttachC() { return attachC; }

=======
}

>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
void Bubble::Update() {
    if (!isActive) return;

    x += vx;
    y += vy;

<<<<<<< HEAD
=======
    // 壁の反射ロジックをここに移植
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    if (x < OFFSET_X) {
        x = (float)OFFSET_X;
        vx *= -1.0f;
    }
    float rightLimit = (float)(OFFSET_X + (STAGE_COLS * B_DIAMETER));
    if (x > rightLimit) {
        x = rightLimit;
        vx *= -1.0f;
<<<<<<< HEAD
    }

    // 現時点ではアニメーションは使わない（静止画像を使用）
}

void Bubble::Draw() {
    if (!isActive) return;

    // 各色ごとの静止画像を描画（状態やアニメーションは無し）
    if (color > 0 && color < BUBBLE_COLOR_COUNT) {
        int img = bubble_images[color][0][0];
        if (img != 0) {
            DrawGraph((int)(x - B_RADIUS), (int)(y - B_RADIUS), img, TRUE);
            return;
        }
=======
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    }

<<<<<<< HEAD
    // スプライトが無ければ従来の塗りつぶし円で描画
    unsigned int drawColor;
    switch (color) {
    case 1: drawColor = GetColor(255, 0, 0); break; 
    case 2: drawColor = GetColor(0, 255, 0); break; 
    case 3: drawColor = GetColor(0, 0, 255); break; 
    case 4: drawColor = GetColor(255, 255, 0); break; 
    default: drawColor = GetColor(255, 255, 255); break; 
    }
=======
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
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    DrawCircle((int)x, (int)y, B_RADIUS, drawColor, TRUE);

    // printfDx("ShotX:%.1f ShotY:%.1f\n", x, y);
}