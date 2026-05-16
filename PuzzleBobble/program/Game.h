#pragma once

#define SCREEN_W	640
#define SCREEN_H	464

void GameInit();	//	初期化処理
void GameUpdate();	//	更新処理
void GameRender();	//	描画処理
void GameExit();	//	終了処理

//	各シーンの番号
enum {
	SCENE_TITLE,	//	０：タイトル
	SCENE_STAGE,	//	１：ステージ
	SCENE_RESULT,	//	２：リザルト（結果表示画面）
};

//	いろんなファイルで使う変数なので外部参照宣言しています
extern int scene_next;

// バブル用の定数（色数・状態数・最大フレーム数）
#define BUBBLE_COLOR_COUNT 5  // 0:未使用, 1..4 を使用
#define BUBBLE_STATE_COUNT 4  // WAIT, SHOT, BREAK, ATTACH
#define BUBBLE_MAX_FRAMES 8

// バブルの状態（インデックス）
enum BubbleState {
    BUBBLE_WAIT = 0,
    BUBBLE_SHOT = 1,
    BUBBLE_BREAK = 2,
    BUBBLE_ATTACH = 3,
};

// 画像データ配列とフレーム数テーブル（他ファイルから参照可能）
extern int bubble_images[BUBBLE_COLOR_COUNT][BUBBLE_STATE_COUNT][BUBBLE_MAX_FRAMES];
extern int bubble_frame_counts[BUBBLE_COLOR_COUNT][BUBBLE_STATE_COUNT];