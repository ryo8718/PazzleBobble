#pragma once
#include "DxLib.h"
#include "Cannon.h"
#include "Bubble.h"

float TO_RADIAN(float degree);
float TO_DEGREE(float radian);
float GetLength_Rotcos(float rot);
float GetLength_Rotsin(float rot);
float GetRadian_Lengthatan2f(float sin, float cos);

extern int stage_1_3_image;
extern int cannon_image;

extern int ceilingOffset; // 天井が下がったピクセル数
#define SCROLL_STEP  15 

#define MAX_COLOR_NUM 4  // 赤、青、緑、黄

#define STAGE_ROWS 12
#define STAGE_COLS 8
#define B_RADIUS   15
#define ROW_HEIGHT ( (int)(B_RADIUS * 2 * 0.866f) ) 
#define B_DIAMETER (B_RADIUS * 2)

#define SCREEN_W 640
#define SCREEN_H 480
#define OFFSET_X 205
#define OFFSET_Y 60

#define WALL_LEFT 190   
#define WALL_RIGHT 446 

#define CEILING_OFFSET_X  190
#define CEILING_IMAGE_HEIGHT  40

#define CANNON_DEFAULT_DEG  -90.0f // 真上
#define CANNON_MIN_DEG  -170.0f     // 左
#define CANNON_MAX_DEG  -10.0f      // 右
#define CANNON_ROTATE_SPEED  2.0f  // 1フレームに動く度数

#define SHOT_LIMIT 8

const int STAGE_DATA_1[STAGE_ROWS][STAGE_COLS] = {
    {1, 2, 2, 2, 2, 4, 4, 0}, // 0行目
    {2, 0, 2, 1, 0, 0, 2, 0}, // 1行目（奇数行）
    {0, 2, 0, 0, 0, 0, 0, 0}, // 2行目
    {1, 0, 0, 0, 0, 0, 0, 0}, // 3行目...
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};




// Bubble speed
#define B_SPEED 8.0f

struct MovingBubble {
    float x, y;    // 現在の座標（壁反射や移動の計算に使うので float）
    float vx, vy;  // 移動速度（1フレームごとに x, y に加算する値）
    int color;     // バブルの色（DxLibの GetColor で取得した値）
    bool isActive; // 今、画面内を飛んでいるかどうか

    void Draw() {
        if (!isActive) return;
        // DxLibの関数で描画
        DrawCircle((int)x, (int)y, B_RADIUS, color, TRUE);
        // 輪郭線（白）を描くとバブルらしくなります
        DrawCircle((int)x, (int)y, B_RADIUS, GetColor(255, 255, 255), FALSE);
    }
};

class Stage {
private:
    Cannon cannon;      // キャノン実体
    Bubble shotBubble;  // ショット用バブル実体
    int field[STAGE_ROWS][STAGE_COLS];
    bool isSafe[STAGE_ROWS][STAGE_COLS];

    float cannonAngle; // 角度（ラジアン）
    float cannonX;     // キャノンの中心座標X
    float cannonY;     // キャノンの中心座標Y

public:
    Stage();
    void Init();
    void LoadStage();
    void HandleInput();
    void Update();
    void ScrollDown();
    void CheckConnect(int r, int c, int color);
    void ProcessErase(int startR, int startC);
    void DropFloatingBubbles();
    void CheckSafe(int r, int c);
    void Draw();
    void FixBubble();
    int GetX(int r, int c);
    int GetY(int r);
};

// Procedural wrappers used by Game.cpp
void StageInit();
void StageUpdate();
void StageRender();
void StageExit();