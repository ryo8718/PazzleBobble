#include "Main.h"
#include "Game.h"
#include "Title.h"
#include "Stage.h"
#include "Result.h"

// --- シーン管理用変数 ---
int scene_num;
int scene_next;

// --- 画像用変数の「実体」定義 ---
int title_image;
int stage_image;
int result_image;
int button_image;
int cannon_image;      // ★追加：砲台
int bubble_images[5];    // ★追加：玉（配列5個分）

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	scene_num = SCENE_TITLE;
	scene_next = SCENE_TITLE;

	// --- 画像の読み込み ---
	// ※注意：ファイルがないと -1 が返りますが、プログラムは動きます
	stage_image = LoadGraph("data/background.png");
	cannon_image = LoadGraph("data/cannon.png");
	bubble_images[1] = LoadGraph("data/bubble_red.png");
	bubble_images[2] = LoadGraph("data/bubble_green.png");
	bubble_images[3] = LoadGraph("data/bubble_blue.png");
	bubble_images[4] = LoadGraph("data/bubble_yellow.png");

	// タイトル画面などで使う画像があればここに追加
	// title_image = LoadGraph("data/title.png");

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