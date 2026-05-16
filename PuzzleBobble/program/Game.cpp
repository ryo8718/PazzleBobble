#include "Main.h"
#include "Game.h"
#include "Title.h"
#include "Stage.h"
#include "Result.h"

// --- シーン管理用変数 ---
int scene_num;
int scene_next;

// --- 画像用変数 ---
int title_image;
int stage_1_3_image;
int result_image;
int button_image;
int cannon_image;
// バブル画像：色 x 状態 x フレーム
int bubble_images[BUBBLE_COLOR_COUNT][BUBBLE_STATE_COUNT][BUBBLE_MAX_FRAMES];
// 各色・状態ごとの実際のフレーム数
int bubble_frame_counts[BUBBLE_COLOR_COUNT][BUBBLE_STATE_COUNT];
int ceiling_image;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	scene_num = SCENE_TITLE;
	scene_next = SCENE_TITLE;

	// --- 画像の読み込み ---
	stage_1_3_image = LoadGraph("data/stage_1_3.png");
	cannon_image = LoadGraph("data/cannon.png");
	// LoadDivGraph(ファイル名, 枚数, 横の分割数, 縦の分割数, 1枚の幅, 1枚の高さ, 保存先配列)
	//LoadDivGraph("data/cannon_anim.png", 8, 8, 1, 64, 64, cannon_images);
    // バッファを初期化
    for (int i = 0; i < BUBBLE_COLOR_COUNT; i++) {
        for (int j = 0; j < BUBBLE_STATE_COUNT; j++) {
            bubble_frame_counts[i][j] = 0;
            for (int k = 0; k < BUBBLE_MAX_FRAMES; k++) bubble_images[i][j][k] = 0;
        }
    }

    // 赤 (color = 1) のアニメーションを読み込む
    // 待機アニメーション（2フレーム）を bubble_images[1][BUBBLE_WAIT][0..1] に読み込む
    LoadDivGraph("data/red_wait.png", 2, 2, 1, 32, 16, &bubble_images[1][BUBBLE_WAIT][0]);
    bubble_frame_counts[1][BUBBLE_WAIT] = 2;
    // 発射状態は1枚画像なので LoadGraph で読み込み（アニメーションしない）
    bubble_images[1][BUBBLE_SHOT][0] = LoadGraph("data/red_shot.png");
    bubble_frame_counts[1][BUBBLE_SHOT] = 1;


	title_image = LoadGraph("data/title.png");

	TitleInit();
}

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	if (scene_num != scene_next) {
		scene_num = scene_next;
		switch (scene_num) {
		case SCENE_TITLE:
			TitleInit();
			break;

		case SCENE_STAGE:
			StageInit();
			break;

		case SCENE_RESULT:
			ResultInit();
			break;
		}
	}

	switch (scene_num) {
	case SCENE_TITLE:
		TitleUpdate();
		break;

	case SCENE_STAGE:
		StageUpdate();
		break;

	case SCENE_RESULT:
		ResultUpdate();
		break;
	}
}

//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	switch (scene_num) {
	case SCENE_TITLE:
		TitleRender();
		break;

	case SCENE_STAGE:
		StageRender();
		break;

	case SCENE_RESULT:
		ResultRender();
		break;
	}
}

//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	TitleExit();
	StageExit();
	ResultExit();
}