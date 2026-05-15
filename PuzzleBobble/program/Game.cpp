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
int stage_1_3_image;
int result_image;
int button_image;
int cannon_image;      // ★追加：砲台
int bubble_images[5];    // ★追加：玉（配列96個分）

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
	LoadDivGraph("data/red_wait.png", 2, 2, 1, 32, 16, bubble_images);
	LoadDivGraph("data/red_shot.png", 6, 6, 1, 96, 16, bubble_images);
	
	
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