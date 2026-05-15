#pragma once

#include "Main.h"

// バブル関連のグリッド定義
#define GRID_W 8
#define GRID_H 12

// 描画・配置用のグローバル変数（定義は bubble.cpp）
extern int bubbleSize;
extern int bubbleRadius;
extern int fieldWidth;
extern int fieldOffsetX;
extern int fieldTop;
extern int launcherX;
extern int launcherY;
extern int fieldHeight;
extern int bubbleBaseX;
extern int bubbleBaseY;

// 初期化（スクリーンサイズに基づいてフィールドとバブルサイズを設定）
void Bubble_Init();

// ユーティリティ
int Bubble_GetUsedWidth();
int Bubble_GetUsedHeight();

// アニメーション関連
#define MAX_BUBBLE_COLORS 100
#define MAX_ANIM_FRAMES 8
extern int bubble_anim_count[MAX_BUBBLE_COLORS];
extern int bubble_anim_frames[MAX_BUBBLE_COLORS][MAX_ANIM_FRAMES];
extern int bubble_anim_pos[MAX_BUBBLE_COLORS];

// color に対してフレーム配列を設定（frames 配列は呼び出し側で管理してよい）
void Bubble_SetAnimationFrames(int color, const int* frames, int count);
// 毎フレーム呼ぶ（内部で一定フレームごとにアニメを進める）
void Bubble_UpdateAnimations();
// 指定色の表示画像を返す（アニメが設定されていれば現在フレーム、なければ bubble_images[color]）
int Bubble_GetFrameImage(int color);

// スプライトシートからアニメを設定する（rects は count*4 の int 配列: x,y,w,h の順）
void Bubble_SetAnimationFromSheet(int color, int sheetHandle, const int* rects, int count);
// 指定色の現在フレームとしてスプライトシート情報を取得する
// 戻り値: sheetHandle (>0) がある場合 true を返し、出力引数に値を設定する
bool Bubble_GetFrameSprite(int color, int &outSheet, int &outSrcX, int &outSrcY, int &outSrcW, int &outSrcH);

