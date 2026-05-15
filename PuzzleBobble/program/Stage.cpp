#include "Stage.h"
#include <cmath>
#include <vector>

int shotCount = 0;

static Stage stage;

Stage::Stage() {
    Init();
}

void Stage::LoadStage() {
    for (int r = 0; r < STAGE_ROWS; r++) {
        for (int c = 0; c < STAGE_COLS; c++) {
            // 設計図(STAGE_DATA_1)から実際のフィールド(field)へコピー
            field[r][c] = STAGE_DATA_1[r][c];
        }
    }
}

void Stage::Init() {
    LoadStage();
    cannon.Init();
    cannonAngle = CANNON_DEFAULT_DEG;
    cannonX = SCREEN_W / 2.0f;
    cannonY = SCREEN_H - 40.0f;

    shotBubble.isActive = false;

    
}

void Stage::HandleInput() {
    // 1. キャノンの旋回
    if (CheckHitKey(KEY_INPUT_LEFT)) {
        cannon.angle -= CANNON_ROTATE_SPEED;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT)) {
        cannon.angle += CANNON_ROTATE_SPEED;
    }

    // 2. 角度制限（マクロ定数を使用）
    if (cannonAngle < CANNON_MIN_DEG) cannon.angle = CANNON_MIN_DEG;
    if (cannonAngle > CANNON_MAX_DEG) cannon.angle = CANNON_MAX_DEG;

    // 3. 発射処理
    if (CheckHitKey(KEY_INPUT_SPACE) && !shotBubble.isActive) {
        float vx = cosf(TO_RADIAN(cannon.angle)) * 5.0f;
        float vy = sinf(TO_RADIAN(cannon.angle)) * 5.0f;
        shotBubble.Init(cannon.x, cannon.y, vx, vy, cannon.currentColor);
        shotBubble.isActive = true;

        cannon.currentColor = GetRand(MAX_COLOR_NUM - 1) + 1;
    }
}

void Stage::Update() {
    // バブルが飛んでいないときは何もしない
    if (!shotBubble.isActive) return;

    // 1. 移動
    shotBubble.x += shotBubble.vx;
    shotBubble.y += shotBubble.vy;

    // 2. 左右の壁での反射
    // 左端（OFFSET_X）
    if (shotBubble.x < WALL_LEFT + B_RADIUS) {
        shotBubble.x = (float)(WALL_LEFT + B_RADIUS);
        shotBubble.vx *= -1.0f;
    }

    // 右端（OFFSET_X + 8列分の幅）
    float rightLimit = (float)(OFFSET_X + (STAGE_COLS * B_DIAMETER));
    if (shotBubble.x > WALL_RIGHT - B_RADIUS) {
        // 1. 位置を壁のギリギリ内側に強制的に戻す
        shotBubble.x = (float)(WALL_RIGHT - B_RADIUS);

        // 2. 速度を反転
        shotBubble.vx *= -1.0f;
    }

    // 3. 画面外（下）へ消えた場合のリセット（念のため）
    if (shotBubble.y > SCREEN_H) {
        shotBubble.isActive = false;
    }
    if (shotBubble.isActive) {
        for (int r = 0; r < STAGE_ROWS; r++) {
            for (int c = 0; c < STAGE_COLS; c++) {
                // そこにバブルがある場合のみ判定
                if (field[r][c] != 0) {
                    float targetX = (float)GetX(r, c);
                    float targetY = (float)GetY(r);

                    float dx = shotBubble.x - targetX;
                    float dy = shotBubble.y - targetY;
                    float distSq = dx * dx + dy * dy; // 距離の2乗

                    // 半径20なら、直径40。40の2乗である1600より小さければ接触
                    if (distSq < (B_RADIUS * 2) * (B_RADIUS * 2)) {
                        // 当たった！
                        FixBubble(); // 固定処理へ
                        return;
                    }
                }
            }
        }

        // 天井に当たった判定
        if (shotBubble.y <= OFFSET_Y) {
            shotBubble.y = OFFSET_Y; // めり込み防止：天井の高さに固定
            FixBubble();
            return;
        }
    }
}

// 消去候補のリスト（std::vectorなどを使うと便利）
std::vector<std::pair<int, int>> eraseList;
bool checked[STAGE_ROWS][STAGE_COLS];

void Stage::CheckConnect(int r, int c, int color) {
    // 範囲外なら終了
    if (r < 0 || r >= STAGE_ROWS || c < 0 || c >= STAGE_COLS) return;
    // すでにチェック済み、または色が違えば終了
    if (checked[r][c] || field[r][c] != color) return;

    // チェック済みにする
    checked[r][c] = true;
    eraseList.push_back({ r, c }); // 消去候補に追加

    // 隣り合う6方向に対して自分自身を呼び出す（再帰）
    // 偶数行・奇数行で隣の位置が少し変わるので注意！
    int dr[6] = { -1, -1, 0, 0, 1, 1 };
    int dc[6];
    if (r % 2 == 0) {
        int temp[] = { -1, 0, -1, 1, -1, 0 }; // 偶数行の隣
        for (int i = 0; i < 6; i++) dc[i] = temp[i];
    }
    else {
        int temp[] = { 0, 1, -1, 1, 0, 1 };  // 奇数行の隣
        for (int i = 0; i < 6; i++) dc[i] = temp[i];
    }

    for (int i = 0; i < 6; i++) {
        CheckConnect(r + dr[i], c + dc[i], color);
    }
}

void Stage::CheckSafe(int r, int c) {
    if (r < 0 || r >= STAGE_ROWS || c < 0 || c >= STAGE_COLS) return;
    if (isSafe[r][c] || field[r][c] == 0) return;

    // 天井から繋がっている
    isSafe[r][c] = true;

    int dr[6] = { -1, -1, 0, 0, 1, 1 };
    int dc[6];
    if (r % 2 == 0) {
        int temp[] = { -1, 0, -1, 1, -1, 0 };
        for (int i = 0; i < 6; i++) dc[i] = temp[i];
    }
    else {
        int temp[] = { 0, 1, -1, 1, 0, 1 };
        for (int i = 0; i < 6; i++) dc[i] = temp[i];
    }

    for (int i = 0; i < 6; i++) {
        CheckSafe(r + dr[i], c + dc[i]);
    }
}



void Stage::DropFloatingBubbles() {
    // 全てをfalse
    for (int r = 0; r < STAGE_ROWS; r++)
        for (int c = 0; c < STAGE_COLS; c++) isSafe[r][c] = false;

    
    for (int c = 0; c < STAGE_COLS; c++) {
        if (field[0][c] != 0) {
            CheckSafe(0, c);
        }
    }

    // 消去（または落下させる）
    for (int r = 0; r < STAGE_ROWS; r++) {
        for (int c = 0; c < STAGE_COLS; c++) {
            if (field[r][c] != 0 && !isSafe[r][c]) {
                field[r][c] = 0; 
            }
        }
    }
}

void Stage::ScrollDown() {
    ceilingOffset += SCROLL_STEP;

    // もし天井の「棒」や「壁」の画像があるなら、その描画位置もこれに合わせる

}

void Stage::FixBubble() {
    // 1. 少し戻す（これはOK）
    shotBubble.x -= shotBubble.vx;
    shotBubble.y -= shotBubble.vy;

    // 2. 行(r)を計算
    int r = (int)((shotBubble.y - OFFSET_Y + ceilingOffset) / ROW_HEIGHT + 0.5f);

    if (shotBubble.y <= OFFSET_Y + ceilingOffset + B_RADIUS) {
        r = 0;
    }

    // 天井より上に行き過ぎた場合は0行目にする
    if (r < 0) r = 0;
    // 底を突き抜けた場合は固定せずに消去
    if (r >= STAGE_ROWS) {
        shotBubble.isActive = false;
        return;
    }

    // 3. 列(c)を計算
    float currentOffsetX = (r % 2 == 0) ? OFFSET_X : OFFSET_X + B_RADIUS;
    int c = (int)((shotBubble.x - currentOffsetX) / (B_RADIUS * 2) + 0.4f);

    // ★重要：列(c)の範囲外チェックと補正
    if (c < 0) c = 0;
    if (c >= STAGE_COLS) c = STAGE_COLS - 1;

    field[r][c] = shotBubble.color;

    // 消去と落下判定
    ProcessErase(r, c);
    DropFloatingBubbles();

    // 弾を非アクティブにする
    shotBubble.isActive = false;

    shotCount++; // 発射回数をカウント
    if (shotCount >= SHOT_LIMIT) {
        ScrollDown();  // 天井を下げる関数を呼ぶ
        shotCount = 0; // カウントリセット
    }
}

void Stage::ProcessErase(int startR, int startC) {
    // 1. 下準備
    eraseList.clear();
    for (int i = 0; i < STAGE_ROWS; i++)
        for (int j = 0; j < STAGE_COLS; j++) checked[i][j] = false;

    // 2. つながりを調べる
    CheckConnect(startR, startC, field[startR][startC]);

    // 3. 3つ以上なら field を 0（空）にする
    if (eraseList.size() >= 3) {
        for (auto p : eraseList) {
            field[p.first][p.second] = 0;
            // ここで「割れるエフェクト」を出すフラグを立てると最高！
        }
    }
}

bool isSafe[STAGE_ROWS][STAGE_COLS];




int Stage::GetX(int r, int c) {
    int x = OFFSET_X + (c * B_RADIUS * 2);
    if (r % 2 != 0) { // 奇数行なら半分ずらす
        x += B_RADIUS;
    }
    return x;
}

int Stage::GetY(int r) {
    return OFFSET_Y + ceilingOffset + (r * ROW_HEIGHT);
}

void Stage::Draw() {

    DrawGraph(0, 0, stage_1_3_image, TRUE);
    
    for (int r = 0; r < STAGE_ROWS; r++) {
        for (int c = 0; c < STAGE_COLS; c++) {
            int colorNum = field[r][c];
            if (colorNum != 0) {
                int drawX = GetX(r, c);
                int drawY = GetY(r);

                // 仮の円を描画
                // 色番号に応じて色を切り替える
                unsigned int color;
                switch (colorNum) {
                case 1: color = GetColor(255, 0, 0); break; // 赤
                case 2: color = GetColor(0, 255, 0); break; // 緑
                case 3: color = GetColor(0, 0, 255); break; // 青
                case 4: color = GetColor(255, 255, 0); break; // 黄
                default: color = GetColor(255, 255, 255); break;
                }
                DrawCircle(drawX, drawY, B_RADIUS-1, color, TRUE);
            }
        }
    }

    int ceilingImgY = (OFFSET_Y + ceilingOffset) - CEILING_IMAGE_HEIGHT;
    DrawGraph(CEILING_OFFSET_X, ceilingImgY, ceiling_image, TRUE);

    // キャノンを描画
    cannon.Draw();

    if (!shotBubble.isActive) {
        unsigned int cCode;
        switch (cannon.currentColor) {
        case 1: cCode = GetColor(255, 0, 0);   break;
        case 2: cCode = GetColor(0, 255, 0);   break; // フィールドの緑と合わせる
        case 3: cCode = GetColor(0, 0, 255);   break;
        case 4: cCode = GetColor(255, 255, 0); break;
        default: cCode = GetColor(255, 255, 255); break;
        }
        DrawCircle((int)cannon.x, (int)cannon.y, B_RADIUS - 1, cCode, TRUE);
    }
    // 飛んでいるバブルを描画
    shotBubble.Draw();

    // マウスの座標を格納する変数
    int mx, my;
    GetMousePoint(&mx, &my);

    // 画面左上に現在のマウス座標を表示
    DrawFormatString(0, 0, GetColor(255, 255, 255), "X=%d Y=%d", mx, my);
}

// Procedural wrappers
void StageInit() 
{
    stage.Init(); 
}

void StageUpdate()
{ 
	stage.HandleInput();
	stage.Update();
}

void StageRender() 
{
    stage.Draw(); 
}

void StageExit() 
{

}



