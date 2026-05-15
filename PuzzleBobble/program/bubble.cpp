#include "Main.h"
#include "Game.h"
#include "bubble.h"

// 画像配列は別で定義されているので参照する
extern int bubble_images[100];

// アニメーション配列
int bubble_anim_count[MAX_BUBBLE_COLORS] = {0};
int bubble_anim_frames[MAX_BUBBLE_COLORS][MAX_ANIM_FRAMES] = {{0}};
int bubble_anim_pos[MAX_BUBBLE_COLORS] = {0};
static int anim_tick = 0; // 内部タイマー
// スプライトシートベースのアニメーション
int bubble_anim_sheet[MAX_BUBBLE_COLORS] = {0};
// rects: for each color, up to MAX_ANIM_FRAMES * 4 (x,y,w,h)
int bubble_anim_rects[MAX_BUBBLE_COLORS][MAX_ANIM_FRAMES][4] = {{{0}}};

// バブル用グローバル変数の定義
int bubbleSize = 32;
int bubbleRadius = 16;
int fieldWidth = GRID_W * 32;
int fieldOffsetX = 0;
int fieldTop = 40;
int launcherX = 0;
int launcherY = 0;
int fieldHeight = 0;
int bubbleBaseX = 0;
int bubbleBaseY = 0;

void Bubble_Init()
{
    // 盤面サイズ
    const int targetFieldW = 255;
    const int targetFieldH = 320;
    fieldWidth = targetFieldW;
    fieldHeight = targetFieldH;
    // フィールド配置
    fieldOffsetX = (SCREEN_W - fieldWidth) / 2;
    fieldTop = (SCREEN_H - fieldHeight) / 2;

    // バブルサイズはフィールドに収まる最大の正方セルサイズを使う（幅優先）
    int sizeByWidth = fieldWidth / GRID_W;   // 255/8 = 31
    int sizeByHeight = fieldHeight / GRID_H; // 320/12 = 26
    bubbleSize = sizeByWidth; // prioritize width
    if (bubbleSize < 8) bubbleSize = 8;
    bubbleRadius = bubbleSize / 2;

    // フィールド
    int usedWidth = bubbleSize * GRID_W;   
    int usedHeight = bubbleSize * GRID_H;  
    
    bubbleBaseX = fieldOffsetX + (fieldWidth - usedWidth) / 2;
    bubbleBaseY = fieldTop + (fieldHeight - usedHeight) / 2;

    // 発射台位置
    launcherX = SCREEN_W / 2;
    int proposedLauncherY = bubbleBaseY + usedHeight + 16;
    if (proposedLauncherY > SCREEN_H - 16) proposedLauncherY = SCREEN_H - 16;
    launcherY = proposedLauncherY;
}

void Bubble_SetAnimationFromSheet(int color, int sheetHandle, const int* rects, int count)
{
    if (color <= 0 || color >= MAX_BUBBLE_COLORS) return;
    bubble_anim_sheet[color] = sheetHandle;
    if (count <= 0) {
        bubble_anim_count[color] = 0;
        return;
    }
    if (count > MAX_ANIM_FRAMES) count = MAX_ANIM_FRAMES;
    bubble_anim_count[color] = count;
    for (int i = 0; i < count; ++i) {
        bubble_anim_rects[color][i][0] = rects[i*4 + 0];
        bubble_anim_rects[color][i][1] = rects[i*4 + 1];
        bubble_anim_rects[color][i][2] = rects[i*4 + 2];
        bubble_anim_rects[color][i][3] = rects[i*4 + 3];
    }
    bubble_anim_pos[color] = 0;
}

bool Bubble_GetFrameSprite(int color, int &outSheet, int &outSrcX, int &outSrcY, int &outSrcW, int &outSrcH)
{
    if (color <= 0 || color >= MAX_BUBBLE_COLORS) return false;
    int sheet = bubble_anim_sheet[color];
    int cnt = bubble_anim_count[color];
    if (sheet == 0 || cnt == 0) return false;
    int idx = bubble_anim_pos[color] % cnt;
    outSheet = sheet;
    outSrcX = bubble_anim_rects[color][idx][0];
    outSrcY = bubble_anim_rects[color][idx][1];
    outSrcW = bubble_anim_rects[color][idx][2];
    outSrcH = bubble_anim_rects[color][idx][3];
    return true;
}

int Bubble_GetUsedWidth()
{
    return bubbleSize * GRID_W;
}

int Bubble_GetUsedHeight()
{
    return bubbleSize * GRID_H;
}

void Bubble_SetAnimationFrames(int color, const int* frames, int count)
{
    if (color <= 0 || color >= MAX_BUBBLE_COLORS) return;
    if (count <= 0) {
        bubble_anim_count[color] = 0;
        return;
    }
    if (count > MAX_ANIM_FRAMES) count = MAX_ANIM_FRAMES;
    bubble_anim_count[color] = count;
    for (int i = 0; i < count; ++i) bubble_anim_frames[color][i] = frames[i];
    bubble_anim_pos[color] = 0;
}

void Bubble_UpdateAnimations()
{
    // advance every N ticks
    const int TICKS_PER_FRAME = 6; // adjust speed
    anim_tick = (anim_tick + 1) % TICKS_PER_FRAME;
    if (anim_tick != 0) return;

    for (int c = 0; c < MAX_BUBBLE_COLORS; ++c) {
        int cnt = bubble_anim_count[c];
        if (cnt > 1) {
            bubble_anim_pos[c] = (bubble_anim_pos[c] + 1) % cnt;
        }
    }
}

int Bubble_GetFrameImage(int color)
{
    if (color <= 0 || color >= MAX_BUBBLE_COLORS) return 0;
    int cnt = bubble_anim_count[color];
    if (cnt > 0) {
        int idx = bubble_anim_pos[color] % cnt;
        return bubble_anim_frames[color][idx];
    }
    // fallback to single image
    if (color >= 0 && color < 100) return bubble_images[color];
    return 0;
}
