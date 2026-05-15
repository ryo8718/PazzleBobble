#include "Main.h"
#include "Game.h"
#include "Stage.h"
#include <math.h>
#include <vector>

// --- 定数 ---
#define ROT_SPEED      0.03f 

#include "bubble.h"

// バブル関連は bubble.h / bubble.cpp に移動しています

// --- 外部変数の参照 ---
extern int stage_1_3_image;
extern int bubble_images[100];
extern int cannon_image;

// --- ステージ内変数 ---
int Map[GRID_H][GRID_W];

struct {
	float x, y;
	float angle;
	bool  active;
	int   color;
} shot_bubble;

// --- ステージ定義 (ここに配列で配置を記述します) ---
// 値: 0=空, 1..4=色番号
static const int Stage1[GRID_H][GRID_W] = {
    {1,2,3,4,1,2,3,4},
    {2,1,2,1,2,1,2,1},
    {3,0,3,0,3,0,3,0},
    {4,0,0,0,4,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};

// 現在読み込むステージを指定 (必要なら複数のステージを定義して切り替えられます)
static const int (*CurrentStage)[GRID_W] = Stage1;

// 角度関連のヘルパー（Stage.cpp の先頭に追加）
static inline float GetLength_RotCos(float rad) { return cosf(rad); }
static inline float GetLength_RotSin(float rad) { return sinf(rad); }
static inline float GetRadian_Atan2(float y, float x) { return atan2f(y, x); }

// 仮のバブル色マップ（画像未設定時に使う）
static int GetBubbleColor(int id)
{
    switch (id) {
    case 1: return GetColor(220, 60, 60);   // 赤
    case 2: return GetColor(60, 120, 220);  // 青
    case 3: return GetColor(80, 200, 80);   // 緑
    case 4: return GetColor(220, 200, 60);  // 黄
    default: return GetColor(150, 150, 150); // グレー
    }
}

// 指定セルから同色の連結領域を集めて、3つ以上なら消去する
static void RemoveConnectedSameColor(int startY, int startX)
{
    int color = Map[startY][startX];
    if (color == 0) return;

    bool visited[GRID_H][GRID_W] = { false };
    std::vector<std::pair<int,int>> stack;
    std::vector<std::pair<int,int>> group;

    stack.emplace_back(startY, startX);
    visited[startY][startX] = true;

    while (!stack.empty()) {
        auto p = stack.back(); stack.pop_back();
        int y = p.first;
        int x = p.second;
        group.emplace_back(y, x);

        // 6方向の隣接セルをチェック（奇数行が右にオフセット）
        const int dx_lr[2] = {-1, 1};
        for (int i = 0; i < 2; ++i) {
            int nx = x + dx_lr[i];
            int ny = y;
            if (nx >= 0 && nx < GRID_W && !visited[ny][nx] && Map[ny][nx] == color) {
                visited[ny][nx] = true;
                stack.emplace_back(ny, nx);
            }
        }

        // 上下斜め（行によって左右が変わる）
        if (y - 1 >= 0) {
            if (y % 2 == 0) {
                // even row
                int nx1 = x - 1; int nx2 = x;
                int ny = y - 1;
                if (nx1 >= 0 && !visited[ny][nx1] && Map[ny][nx1] == color) { visited[ny][nx1] = true; stack.emplace_back(ny, nx1); }
                if (nx2 >= 0 && nx2 < GRID_W && !visited[ny][nx2] && Map[ny][nx2] == color) { visited[ny][nx2] = true; stack.emplace_back(ny, nx2); }
            }
            else {
                // odd row
                int nx1 = x; int nx2 = x + 1;
                int ny = y - 1;
                if (nx1 >= 0 && nx1 < GRID_W && !visited[ny][nx1] && Map[ny][nx1] == color) { visited[ny][nx1] = true; stack.emplace_back(ny, nx1); }
                if (nx2 >= 0 && nx2 < GRID_W && !visited[ny][nx2] && Map[ny][nx2] == color) { visited[ny][nx2] = true; stack.emplace_back(ny, nx2); }
            }
        }
        if (y + 1 < GRID_H) {
            if (y % 2 == 0) {
                // even row
                int nx1 = x - 1; int nx2 = x;
                int ny = y + 1;
                if (nx1 >= 0 && !visited[ny][nx1] && Map[ny][nx1] == color) { visited[ny][nx1] = true; stack.emplace_back(ny, nx1); }
                if (nx2 >= 0 && nx2 < GRID_W && !visited[ny][nx2] && Map[ny][nx2] == color) { visited[ny][nx2] = true; stack.emplace_back(ny, nx2); }
            }
            else {
                // odd row
                int nx1 = x; int nx2 = x + 1;
                int ny = y + 1;
                if (nx1 >= 0 && nx1 < GRID_W && !visited[ny][nx1] && Map[ny][nx1] == color) { visited[ny][nx1] = true; stack.emplace_back(ny, nx1); }
                if (nx2 >= 0 && nx2 < GRID_W && !visited[ny][nx2] && Map[ny][nx2] == color) { visited[ny][nx2] = true; stack.emplace_back(ny, nx2); }
            }
        }
    }

    // 3つ以上なら消去
    if (group.size() >= 3) {
        for (auto &q : group) {
            Map[q.first][q.second] = 0;
        }
    }
}

// 天井（最上行）とつながっていないバブルを落とす（消去する）
static void RemoveFloatingBubbles()
{
    bool visited[GRID_H][GRID_W] = { false };
    std::vector<std::pair<int,int>> stack;

    // 最上行から非ゼロセルを始点にして到達可能なバブルをマーク
    for (int x = 0; x < GRID_W; ++x) {
        if (Map[0][x] != 0 && !visited[0][x]) {
            visited[0][x] = true;
            stack.emplace_back(0, x);

            while (!stack.empty()) {
                auto p = stack.back(); stack.pop_back();
                int y = p.first; int x2 = p.second;

                // 左右
                const int dx_lr[2] = {-1, 1};
                for (int i = 0; i < 2; ++i) {
                    int nx = x2 + dx_lr[i];
                    int ny = y;
                    if (nx >= 0 && nx < GRID_W && !visited[ny][nx] && Map[ny][nx] != 0) {
                        visited[ny][nx] = true;
                        stack.emplace_back(ny, nx);
                    }
                }

                // 上下の隣接（行によって左右が変わる）
                if (y - 1 >= 0) {
                    int ny = y - 1;
                    if (y % 2 == 0) {
                        int nx1 = x2 - 1; int nx2 = x2;
                        if (nx1 >= 0 && !visited[ny][nx1] && Map[ny][nx1] != 0) { visited[ny][nx1] = true; stack.emplace_back(ny, nx1); }
                        if (nx2 >= 0 && nx2 < GRID_W && !visited[ny][nx2] && Map[ny][nx2] != 0) { visited[ny][nx2] = true; stack.emplace_back(ny, nx2); }
                    } else {
                        int nx1 = x2; int nx2 = x2 + 1;
                        if (nx1 >= 0 && nx1 < GRID_W && !visited[ny][nx1] && Map[ny][nx1] != 0) { visited[ny][nx1] = true; stack.emplace_back(ny, nx1); }
                        if (nx2 >= 0 && nx2 < GRID_W && !visited[ny][nx2] && Map[ny][nx2] != 0) { visited[ny][nx2] = true; stack.emplace_back(ny, nx2); }
                    }
                }
                if (y + 1 < GRID_H) {
                    int ny = y + 1;
                    if (y % 2 == 0) {
                        int nx1 = x2 - 1; int nx2 = x2;
                        if (nx1 >= 0 && !visited[ny][nx1] && Map[ny][nx1] != 0) { visited[ny][nx1] = true; stack.emplace_back(ny, nx1); }
                        if (nx2 >= 0 && nx2 < GRID_W && !visited[ny][nx2] && Map[ny][nx2] != 0) { visited[ny][nx2] = true; stack.emplace_back(ny, nx2); }
                    } else {
                        int nx1 = x2; int nx2 = x2 + 1;
                        if (nx1 >= 0 && nx1 < GRID_W && !visited[ny][nx1] && Map[ny][nx1] != 0) { visited[ny][nx1] = true; stack.emplace_back(ny, nx1); }
                        if (nx2 >= 0 && nx2 < GRID_W && !visited[ny][nx2] && Map[ny][nx2] != 0) { visited[ny][nx2] = true; stack.emplace_back(ny, nx2); }
                    }
                }
            }
        }
    }

    // 到達不可のバブルは落とす（消去）
    for (int y = 0; y < GRID_H; ++y) {
        for (int x = 0; x < GRID_W; ++x) {
            if (Map[y][x] != 0 && !visited[y][x]) {
                Map[y][x] = 0;
            }
        }
    }
}

//---------------------------------------------------------------------------------
//	初期化
//---------------------------------------------------------------------------------
void StageInit() {
    // 盤面の初期化（配列で定義したステージを読み込む）
    for (int y = 0; y < GRID_H; y++) {
        for (int x = 0; x < GRID_W; x++) {
            Map[y][x] = CurrentStage[y][x];
        }
    }
    // バブル初期化（フィールドサイズ・バブルサイズ・基準位置等）
    Bubble_Init();

    const int targetFieldW = 255;
    const int targetFieldH = 320;
    fieldWidth = targetFieldW;
    fieldHeight = targetFieldH;

    // フィールドを画面中央に配置
    fieldOffsetX = (SCREEN_W - fieldWidth) / 2;
    fieldTop = (SCREEN_H - fieldHeight) / 2;

    // バブルは幅優先で合わせる（縦は犠牲にしてもよい）
    int sizeByWidth = fieldWidth / GRID_W;   // 255/8 = 31
    int sizeByHeight = fieldHeight / GRID_H; // 320/12 = 26
    // 幅に合わせて大きくする（非正方セルや縦はみ出しを許容）
    bubbleSize = sizeByWidth; // prioritize width
    if (bubbleSize < 8) bubbleSize = 8;
    bubbleRadius = bubbleSize / 2;

    // フィールド内で実際にバブルが描かれる矩形（幅優先で大きくなるため縦がはみ出す可能性あり）
    int usedWidth = bubbleSize * GRID_W;   
    int usedHeight = bubbleSize * GRID_H;  
    bubbleBaseX = fieldOffsetX + (fieldWidth - usedWidth) / 2;
    bubbleBaseY = fieldTop + (fieldHeight - usedHeight) / 2;

    // 発射台位置
    launcherX = SCREEN_W / 2;
    int proposedLauncherY = bubbleBaseY + usedHeight + 16;
    if (proposedLauncherY > SCREEN_H - 16) proposedLauncherY = SCREEN_H - 16;
    launcherY = proposedLauncherY;
	shot_bubble.active = false;
	shot_bubble.color = rand() % 4 + 1;
	shot_bubble.angle = -3.14159265f / 2.0f; // 真上向き
}

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void StageUpdate() {
    // 更新時にバブルアニメーションを進める
    Bubble_UpdateAnimations();
	if (!shot_bubble.active) {
		// 1. 角度調整
		if (CheckHitKey(KEY_INPUT_LEFT))  shot_bubble.angle -= ROT_SPEED;
		if (CheckHitKey(KEY_INPUT_RIGHT)) shot_bubble.angle += ROT_SPEED;

		// 角度制限（真横より下に行かないように）
		if (shot_bubble.angle < -3.14159265f + 0.2f) shot_bubble.angle = -3.14159265f + 0.2f;
		if (shot_bubble.angle > -0.2f)               shot_bubble.angle = -0.2f;

		shot_bubble.x = (float)launcherX;
		shot_bubble.y = (float)launcherY;

		// 2. 発射
		if (PushHitKey(KEY_INPUT_SPACE)) {
			shot_bubble.active = true;
		}
	}
	else {
		// 3. 移動
		shot_bubble.x += GetLength_RotCos(shot_bubble.angle) * 8.0f;
		shot_bubble.y += GetLength_RotSin(shot_bubble.angle) * 8.0f;

        // 4. 壁反射（実際にバブルが描かれる領域での反射）
        int usedWidth = bubbleSize * GRID_W;
        if (shot_bubble.x < bubbleBaseX + bubbleRadius ||
            shot_bubble.x > bubbleBaseX + usedWidth - bubbleRadius) {
			float vx = GetLength_RotCos(shot_bubble.angle);
			float vy = GetLength_RotSin(shot_bubble.angle);
			shot_bubble.angle = GetRadian_Atan2(vy, -vx);
		}

		// 5. 当たり判定（盤面のバブルとの衝突）
		bool hit = false;
		for (int y = 0; y < GRID_H; y++) {
			for (int x = 0; x < GRID_W; x++) {
                if (Map[y][x] > 0) {
            float offsetX = (y % 2 == 1) ? (float)bubbleRadius : 0.0f;
                float targetX = bubbleBaseX + x * bubbleSize + bubbleRadius + offsetX;
                float targetY = bubbleBaseY + y * bubbleSize + bubbleRadius;

					// 距離の2乗で判定（ルート計算を省いて高速化）
					float dx = shot_bubble.x - targetX;
					float dy = shot_bubble.y - targetY;
				if ((dx * dx + dy * dy) < (bubbleSize * bubbleSize * 0.9f)) {
						hit = true;
						break;
					}
				}
			}
			if (hit) break;
		}

        // 天井に当たった場合もヒット扱い
        if (shot_bubble.y < bubbleBaseY + bubbleRadius) hit = true;

		// 6. 衝突時の固定処理
		if (hit) {
			// 現在の座標からMapの添字(x, y)を逆算
            int mapY = (int)((shot_bubble.y - bubbleBaseY) / bubbleSize);
			if (mapY < 0) mapY = 0;
			if (mapY >= GRID_H) mapY = GRID_H - 1;

            float offsetX = (mapY % 2 == 1) ? (float)bubbleRadius : 0.0f;
            int mapX = (int)((shot_bubble.x - bubbleBaseX - offsetX) / bubbleSize);
			if (mapX < 0) mapX = 0;
			if (mapX >= GRID_W) mapX = GRID_W - 1;

			// Mapに色を書き込む
			Map[mapY][mapX] = shot_bubble.color;
			// 同色が3つ以上つながっていたら消す
			RemoveConnectedSameColor(mapY, mapX);
			// 連結削除の後、天井と繋がっていないバブルを落とす
			RemoveFloatingBubbles();

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
	DrawGraph(0, 0, stage_1_3_image, TRUE);

    // 盤面描画
    for (int y = 0; y < GRID_H; y++) {
        for (int x = 0; x < GRID_W; x++) {
                if (Map[y][x] > 0) {
                float offsetX = (y % 2 == 1) ? (float)bubbleRadius : 0.0f;
                int drawX = (int)(bubbleBaseX + x * bubbleSize + bubbleRadius + offsetX);
                int drawY = (int)(bubbleBaseY + y * bubbleSize + bubbleRadius);

                int frameImg = Bubble_GetFrameImage(Map[y][x]);
                if (frameImg > 0) {
                    DrawGraph(drawX - bubbleRadius, drawY - bubbleRadius, frameImg, TRUE);
                }
                else {
                    int sheet, sx, sy, sw, sh;
                    if (Bubble_GetFrameSprite(Map[y][x], sheet, sx, sy, sw, sh)) {
                        DrawRectGraph(drawX - bubbleRadius, drawY - bubbleRadius, sx, sy, sw, sh, sheet, TRUE);
                    }
                    else {
                        DrawCircle(drawX, drawY, bubbleRadius, GetBubbleColor(Map[y][x]), TRUE);
                    }
                }
            }
        }
    }


    // 砲台
    DrawRotaGraph(launcherX, launcherY, 1.0, shot_bubble.angle + 1.5708f, cannon_image, TRUE);

    // 発射バブル
    {
        int frameImg = Bubble_GetFrameImage(shot_bubble.color);
        if (frameImg > 0) {
            DrawGraph((int)shot_bubble.x - bubbleRadius, (int)shot_bubble.y - bubbleRadius, frameImg, TRUE);
        } else {
            int sheet, sx, sy, sw, sh;
            if (Bubble_GetFrameSprite(shot_bubble.color, sheet, sx, sy, sw, sh)) {
                DrawRectGraph((int)shot_bubble.x - bubbleRadius, (int)shot_bubble.y - bubbleRadius, sx, sy, sw, sh, sheet, TRUE);
            } else {
                DrawCircle((int)shot_bubble.x, (int)shot_bubble.y, bubbleRadius, GetBubbleColor(shot_bubble.color), TRUE);
            }
        }
    }

	DrawString(20, 20, "左右キー：角度調整 / SPACE：発射", GetColor(255, 255, 255));
}

void StageExit() {}