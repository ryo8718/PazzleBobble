#include "Main.h"
#include "Game.h"
#include "Stage.h"
#include <math.h>

// --- 定数 ---
#define BUBBLE_SIZE    32
#define BUBBLE_RADIUS  16
#define GRID_W         8
#define GRID_H         12
#define FIELD_WIDTH    (GRID_W * BUBBLE_SIZE)
#define FIELD_OFFSET_X ((SCREEN_W - FIELD_WIDTH) / 2) 
#define FIELD_TOP      40
#define LAUNCHER_X     (SCREEN_W / 2)
#define LAUNCHER_Y     (SCREEN_H - 60)
#define ROT_SPEED      0.03f 

// --- 外部変数の参照 ---
extern int stage_image;
extern int bubble_images[5];
extern int cannon_image;

// --- ステージ内変数 ---
int Map[GRID_H][GRID_W];

struct {
	float x, y;
	float angle;
	bool  active;
	int   color;
} shot_bubble;

// 角度関連のヘルパー（Stage.cpp の先頭に追加）
static inline float GetLength_RotCos(float rad) { return cosf(rad); }
static inline float GetLength_RotSin(float rad) { return sinf(rad); }
static inline float GetRadian_Atan2(float y, float x) { return atan2f(y, x); }

//---------------------------------------------------------------------------------
//	初期化
//---------------------------------------------------------------------------------
void StageInit() {
	// 盤面の初期化（上4行にランダム配置）
	for (int y = 0; y < GRID_H; y++) {
		for (int x = 0; x < GRID_W; x++) {
			if (y < 4) Map[y][x] = rand() % 4 + 1;
			else       Map[y][x] = 0;
		}
	}
	shot_bubble.active = false;
	shot_bubble.color = rand() % 4 + 1;
	shot_bubble.angle = -3.14159265f / 2.0f; // 真上向き
}

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void StageUpdate() {
	if (!shot_bubble.active) {
		// 1. 角度調整
		if (CheckHitKey(KEY_INPUT_LEFT))  shot_bubble.angle -= ROT_SPEED;
		if (CheckHitKey(KEY_INPUT_RIGHT)) shot_bubble.angle += ROT_SPEED;

		// 角度制限（真横より下に行かないように）
		if (shot_bubble.angle < -3.14159265f + 0.2f) shot_bubble.angle = -3.14159265f + 0.2f;
		if (shot_bubble.angle > -0.2f)               shot_bubble.angle = -0.2f;

		shot_bubble.x = (float)LAUNCHER_X;
		shot_bubble.y = (float)LAUNCHER_Y;

		// 2. 発射
		if (PushHitKey(KEY_INPUT_SPACE)) {
			shot_bubble.active = true;
		}
	}
	else {
		// 3. 移動
		shot_bubble.x += GetLength_RotCos(shot_bubble.angle) * 8.0f;
		shot_bubble.y += GetLength_RotSin(shot_bubble.angle) * 8.0f;

		// 4. 壁反射
		if (shot_bubble.x < FIELD_OFFSET_X + BUBBLE_RADIUS ||
			shot_bubble.x > FIELD_OFFSET_X + FIELD_WIDTH - BUBBLE_RADIUS) {
			float vx = GetLength_RotCos(shot_bubble.angle);
			float vy = GetLength_RotSin(shot_bubble.angle);
			shot_bubble.angle = GetRadian_Atan2(vy, -vx);
		}

		// 5. 当たり判定（盤面のバブルとの衝突）
		bool hit = false;
		for (int y = 0; y < GRID_H; y++) {
			for (int x = 0; x < GRID_W; x++) {
				if (Map[y][x] > 0) {
					float offsetX = (y % 2 == 1) ? (float)BUBBLE_RADIUS : 0.0f;
					float targetX = FIELD_OFFSET_X + x * BUBBLE_SIZE + BUBBLE_RADIUS + offsetX;
					float targetY = FIELD_TOP + y * BUBBLE_SIZE + BUBBLE_RADIUS;

					// 距離の2乗で判定（ルート計算を省いて高速化）
					float dx = shot_bubble.x - targetX;
					float dy = shot_bubble.y - targetY;
					if ((dx * dx + dy * dy) < (BUBBLE_SIZE * BUBBLE_SIZE * 0.9f)) {
						hit = true;
						break;
					}
				}
			}
			if (hit) break;
		}

		// 天井に当たった場合もヒット扱い
		if (shot_bubble.y < FIELD_TOP + BUBBLE_RADIUS) hit = true;

		// 6. 衝突時の固定処理
		if (hit) {
			// 現在の座標からMapの添字(x, y)を逆算
			int mapY = (int)((shot_bubble.y - FIELD_TOP) / BUBBLE_SIZE);
			if (mapY < 0) mapY = 0;
			if (mapY >= GRID_H) mapY = GRID_H - 1;

			float offsetX = (mapY % 2 == 1) ? (float)BUBBLE_RADIUS : 0.0f;
			int mapX = (int)((shot_bubble.x - FIELD_OFFSET_X - offsetX) / BUBBLE_SIZE);
			if (mapX < 0) mapX = 0;
			if (mapX >= GRID_W) mapX = GRID_W - 1;

			// Mapに色を書き込む
			Map[mapY][mapX] = shot_bubble.color;

			// 次の玉を準備
			shot_bubble.active = false;
			shot_bubble.color = rand() % 4 + 1;
		}
	}
}

//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void StageRender() {
	DrawGraph(0, 0, stage_image, TRUE);

	// 盤面描画
	for (int y = 0; y < GRID_H; y++) {
		for (int x = 0; x < GRID_W; x++) {
			if (Map[y][x] > 0) {
				float offsetX = (y % 2 == 1) ? (float)BUBBLE_RADIUS : 0.0f;
				int drawX = (int)(FIELD_OFFSET_X + x * BUBBLE_SIZE + BUBBLE_RADIUS + offsetX);
				int drawY = (int)(FIELD_TOP + y * BUBBLE_SIZE + BUBBLE_RADIUS);

				if (bubble_images[Map[y][x]] > 0)
					DrawGraph(drawX - BUBBLE_RADIUS, drawY - BUBBLE_RADIUS, bubble_images[Map[y][x]], TRUE);
				else
					DrawCircle(drawX, drawY, BUBBLE_RADIUS, GetColor(150, 150, 150), TRUE);
			}
		}
	}

	

	// 砲台
	DrawRotaGraph(LAUNCHER_X, LAUNCHER_Y, 1.0, shot_bubble.angle + 1.5708f, cannon_image, TRUE);

	// 発射バブル
	if (bubble_images[shot_bubble.color] > 0)
		DrawGraph((int)shot_bubble.x - BUBBLE_RADIUS, (int)shot_bubble.y - BUBBLE_RADIUS, bubble_images[shot_bubble.color], TRUE);
	else
		DrawCircle((int)shot_bubble.x, (int)shot_bubble.y, BUBBLE_RADIUS, GetColor(255, 255, 0), TRUE);

	DrawString(20, 20, "左右キー：角度調整 / SPACE：発射", GetColor(255, 255, 255));
}

void StageExit() {}