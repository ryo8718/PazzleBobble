<<<<<<< HEAD
#include "Stage.h"
#include <cmath>
#include <vector>

int ceilingOffset = 0;
=======
ï»¿#include "Stage.h"
#include <cmath>
#include <vector>

>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
int shotCount = 0;

static Stage stage;

Stage::Stage() {
    Init();
}

void Stage::LoadStage() {
    for (int r = 0; r < STAGE_ROWS; r++) {
        for (int c = 0; c < STAGE_COLS; c++) {
<<<<<<< HEAD
            // İŒv}(STAGE_DATA_1)‚©‚çÀÛ‚ÌƒtƒB[ƒ‹ƒh(field)‚ÖƒRƒs[
=======
            // è¨­è¨ˆå›³(STAGE_DATA_1)ã‹ã‚‰å®Ÿéš›ã®ãƒ•ã‚£ãƒ¼ãƒ«ãƒ‰(field)ã¸ã‚³ãƒ”ãƒ¼
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
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

<<<<<<< HEAD

}

void Stage::HandleInput() {
    // 1. ƒLƒƒƒmƒ“‚Ìù‰ñ
    if (CheckHitKey(KEY_INPUT_LEFT)) {
        cannon.angle -= CANNON_ROTATE_SPEED;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT)) {
        cannon.angle += CANNON_ROTATE_SPEED;
    }

    // 2. Šp“x§ŒÀiƒ}ƒNƒ’è”‚ğg—pj
    if (cannonAngle < CANNON_MIN_DEG) cannon.angle = CANNON_MIN_DEG;
    if (cannonAngle > CANNON_MAX_DEG) cannon.angle = CANNON_MAX_DEG;

    // 3. ”­Ëˆ—
=======
    
}

void Stage::HandleInput() {
    // 1. ã‚­ãƒ£ãƒãƒ³ã®æ—‹å›
    if (CheckHitKey(KEY_INPUT_LEFT)) {
        cannon.angle -= CANNON_ROTATE_SPEED;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT)) {
        cannon.angle += CANNON_ROTATE_SPEED;
    }

    // 2. è§’åº¦åˆ¶é™ï¼ˆãƒã‚¯ãƒ­å®šæ•°ã‚’ä½¿ç”¨ï¼‰
    if (cannonAngle < CANNON_MIN_DEG) cannon.angle = CANNON_MIN_DEG;
    if (cannonAngle > CANNON_MAX_DEG) cannon.angle = CANNON_MAX_DEG;

    // 3. ç™ºå°„å‡¦ç†
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    if (CheckHitKey(KEY_INPUT_SPACE) && !shotBubble.isActive) {
        float vx = cosf(TO_RADIAN(cannon.angle)) * 5.0f;
        float vy = sinf(TO_RADIAN(cannon.angle)) * 5.0f;
        shotBubble.Init(cannon.x, cannon.y, vx, vy, cannon.currentColor);
        shotBubble.isActive = true;

        cannon.currentColor = GetRand(MAX_COLOR_NUM - 1) + 1;
    }
}

void Stage::Update() {
<<<<<<< HEAD
    // ƒoƒuƒ‹‚ª”ò‚ñ‚Å‚¢‚È‚¢‚Æ‚«‚Í‰½‚à‚µ‚È‚¢
    if (!shotBubble.isActive) return;

    // 1. ˆÚ“®
    shotBubble.x += shotBubble.vx;
    shotBubble.y += shotBubble.vy;

    // 2. ¶‰E‚Ì•Ç‚Å‚Ì”½Ë
    // ¶’[iOFFSET_Xj
=======
    // ãƒãƒ–ãƒ«ãŒé£›ã‚“ã§ã„ãªã„ã¨ãã¯ä½•ã‚‚ã—ãªã„
    if (!shotBubble.isActive) return;

    // 1. ç§»å‹•
    shotBubble.x += shotBubble.vx;
    shotBubble.y += shotBubble.vy;

    // 2. å·¦å³ã®å£ã§ã®åå°„
    // å·¦ç«¯ï¼ˆOFFSET_Xï¼‰
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    if (shotBubble.x < WALL_LEFT + B_RADIUS) {
        shotBubble.x = (float)(WALL_LEFT + B_RADIUS);
        shotBubble.vx *= -1.0f;
    }

<<<<<<< HEAD
    // ‰E’[iOFFSET_X + 8—ñ•ª‚Ì•j
    float rightLimit = (float)(OFFSET_X + (STAGE_COLS * B_DIAMETER));
    if (shotBubble.x > WALL_RIGHT - B_RADIUS) {
        // 1. ˆÊ’u‚ğ•Ç‚ÌƒMƒŠƒMƒŠ“à‘¤‚É‹­§“I‚É–ß‚·
        shotBubble.x = (float)(WALL_RIGHT - B_RADIUS);

        // 2. ‘¬“x‚ğ”½“]
        shotBubble.vx *= -1.0f;
    }

    // 3. ‰æ–ÊŠOi‰ºj‚ÖÁ‚¦‚½ê‡‚ÌƒŠƒZƒbƒgi”O‚Ì‚½‚ßj
=======
    // å³ç«¯ï¼ˆOFFSET_X + 8åˆ—åˆ†ã®å¹…ï¼‰
    float rightLimit = (float)(OFFSET_X + (STAGE_COLS * B_DIAMETER));
    if (shotBubble.x > WALL_RIGHT - B_RADIUS) {
        // 1. ä½ç½®ã‚’å£ã®ã‚®ãƒªã‚®ãƒªå†…å´ã«å¼·åˆ¶çš„ã«æˆ»ã™
        shotBubble.x = (float)(WALL_RIGHT - B_RADIUS);

        // 2. é€Ÿåº¦ã‚’åè»¢
        shotBubble.vx *= -1.0f;
    }

    // 3. ç”»é¢å¤–ï¼ˆä¸‹ï¼‰ã¸æ¶ˆãˆãŸå ´åˆã®ãƒªã‚»ãƒƒãƒˆï¼ˆå¿µã®ãŸã‚ï¼‰
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    if (shotBubble.y > SCREEN_H) {
        shotBubble.isActive = false;
    }
    if (shotBubble.isActive) {
        for (int r = 0; r < STAGE_ROWS; r++) {
            for (int c = 0; c < STAGE_COLS; c++) {
<<<<<<< HEAD
                // ‚»‚±‚Éƒoƒuƒ‹‚ª‚ ‚éê‡‚Ì‚İ”»’è
=======
                // ãã“ã«ãƒãƒ–ãƒ«ãŒã‚ã‚‹å ´åˆã®ã¿åˆ¤å®š
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
                if (field[r][c] != 0) {
                    float targetX = (float)GetX(r, c);
                    float targetY = (float)GetY(r);

                    float dx = shotBubble.x - targetX;
                    float dy = shotBubble.y - targetY;
<<<<<<< HEAD
                    float distSq = dx * dx + dy * dy; // ‹——£‚Ì2æ

                    // ”¼Œa20‚È‚çA’¼Œa40B40‚Ì2æ‚Å‚ ‚é1600‚æ‚è¬‚³‚¯‚ê‚ÎÚG
                    if (distSq < (B_RADIUS * 2) * (B_RADIUS * 2)) {
                        // “–‚½‚Á‚½I
                        FixBubble(); // ŒÅ’èˆ—‚Ö
=======
                    float distSq = dx * dx + dy * dy; // è·é›¢ã®2ä¹—

                    // åŠå¾„20ãªã‚‰ã€ç›´å¾„40ã€‚40ã®2ä¹—ã§ã‚ã‚‹1600ã‚ˆã‚Šå°ã•ã‘ã‚Œã°æ¥è§¦
                    if (distSq < (B_RADIUS * 2) * (B_RADIUS * 2)) {
                        // å½“ãŸã£ãŸï¼
                        FixBubble(); // å›ºå®šå‡¦ç†ã¸
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
                        return;
                    }
                }
            }
        }

<<<<<<< HEAD
        // “Vˆä‚É“–‚½‚Á‚½”»’è
        if (shotBubble.y <= OFFSET_Y) {
            shotBubble.y = OFFSET_Y; // ‚ß‚è‚İ–h~F“Vˆä‚Ì‚‚³‚ÉŒÅ’è
=======
        // å¤©äº•ã«å½“ãŸã£ãŸåˆ¤å®š
        if (shotBubble.y <= OFFSET_Y) {
            shotBubble.y = OFFSET_Y; // ã‚ã‚Šè¾¼ã¿é˜²æ­¢ï¼šå¤©äº•ã®é«˜ã•ã«å›ºå®š
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
            FixBubble();
            return;
        }
    }
}

<<<<<<< HEAD
// Á‹Œó•â‚ÌƒŠƒXƒgistd::vector‚È‚Ç‚ğg‚¤‚Æ•Ö—˜j
=======
// æ¶ˆå»å€™è£œã®ãƒªã‚¹ãƒˆï¼ˆstd::vectorãªã©ã‚’ä½¿ã†ã¨ä¾¿åˆ©ï¼‰
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
std::vector<std::pair<int, int>> eraseList;
bool checked[STAGE_ROWS][STAGE_COLS];

void Stage::CheckConnect(int r, int c, int color) {
<<<<<<< HEAD
    // ”ÍˆÍŠO‚È‚çI—¹
    if (r < 0 || r >= STAGE_ROWS || c < 0 || c >= STAGE_COLS) return;
    // ‚·‚Å‚Éƒ`ƒFƒbƒNÏ‚İA‚Ü‚½‚ÍF‚ªˆá‚¦‚ÎI—¹
    if (checked[r][c] || field[r][c] != color) return;

    // ƒ`ƒFƒbƒNÏ‚İ‚É‚·‚é
    checked[r][c] = true;
    eraseList.push_back({ r, c }); // Á‹Œó•â‚É’Ç‰Á

    // —×‚è‡‚¤6•ûŒü‚É‘Î‚µ‚Ä©•ª©g‚ğŒÄ‚Ño‚·iÄ‹Aj
    // ‹ô”sEŠï”s‚Å—×‚ÌˆÊ’u‚ª­‚µ•Ï‚í‚é‚Ì‚Å’ˆÓI
    int dr[6] = { -1, -1, 0, 0, 1, 1 };
    int dc[6];
    if (r % 2 == 0) {
        int temp[] = { -1, 0, -1, 1, -1, 0 }; // ‹ô”s‚Ì—×
        for (int i = 0; i < 6; i++) dc[i] = temp[i];
    }
    else {
        int temp[] = { 0, 1, -1, 1, 0, 1 };  // Šï”s‚Ì—×
=======
    // ç¯„å›²å¤–ãªã‚‰çµ‚äº†
    if (r < 0 || r >= STAGE_ROWS || c < 0 || c >= STAGE_COLS) return;
    // ã™ã§ã«ãƒã‚§ãƒƒã‚¯æ¸ˆã¿ã€ã¾ãŸã¯è‰²ãŒé•ãˆã°çµ‚äº†
    if (checked[r][c] || field[r][c] != color) return;

    // ãƒã‚§ãƒƒã‚¯æ¸ˆã¿ã«ã™ã‚‹
    checked[r][c] = true;
    eraseList.push_back({ r, c }); // æ¶ˆå»å€™è£œã«è¿½åŠ 

    // éš£ã‚Šåˆã†6æ–¹å‘ã«å¯¾ã—ã¦è‡ªåˆ†è‡ªèº«ã‚’å‘¼ã³å‡ºã™ï¼ˆå†å¸°ï¼‰
    // å¶æ•°è¡Œãƒ»å¥‡æ•°è¡Œã§éš£ã®ä½ç½®ãŒå°‘ã—å¤‰ã‚ã‚‹ã®ã§æ³¨æ„ï¼
    int dr[6] = { -1, -1, 0, 0, 1, 1 };
    int dc[6];
    if (r % 2 == 0) {
        int temp[] = { -1, 0, -1, 1, -1, 0 }; // å¶æ•°è¡Œã®éš£
        for (int i = 0; i < 6; i++) dc[i] = temp[i];
    }
    else {
        int temp[] = { 0, 1, -1, 1, 0, 1 };  // å¥‡æ•°è¡Œã®éš£
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
        for (int i = 0; i < 6; i++) dc[i] = temp[i];
    }

    for (int i = 0; i < 6; i++) {
        CheckConnect(r + dr[i], c + dc[i], color);
    }
}

void Stage::CheckSafe(int r, int c) {
    if (r < 0 || r >= STAGE_ROWS || c < 0 || c >= STAGE_COLS) return;
    if (isSafe[r][c] || field[r][c] == 0) return;

<<<<<<< HEAD
    // “Vˆä‚©‚çŒq‚ª‚Á‚Ä‚¢‚é
=======
    // å¤©äº•ã‹ã‚‰ç¹‹ãŒã£ã¦ã„ã‚‹
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
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
<<<<<<< HEAD
    // ‘S‚Ä‚ğfalse
    for (int r = 0; r < STAGE_ROWS; r++)
        for (int c = 0; c < STAGE_COLS; c++) isSafe[r][c] = false;


=======
    // å…¨ã¦ã‚’false
    for (int r = 0; r < STAGE_ROWS; r++)
        for (int c = 0; c < STAGE_COLS; c++) isSafe[r][c] = false;

    
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    for (int c = 0; c < STAGE_COLS; c++) {
        if (field[0][c] != 0) {
            CheckSafe(0, c);
        }
    }

<<<<<<< HEAD
    // Á‹i‚Ü‚½‚Í—‰º‚³‚¹‚éj
    for (int r = 0; r < STAGE_ROWS; r++) {
        for (int c = 0; c < STAGE_COLS; c++) {
            if (field[r][c] != 0 && !isSafe[r][c]) {
                field[r][c] = 0;
=======
    // æ¶ˆå»ï¼ˆã¾ãŸã¯è½ä¸‹ã•ã›ã‚‹ï¼‰
    for (int r = 0; r < STAGE_ROWS; r++) {
        for (int c = 0; c < STAGE_COLS; c++) {
            if (field[r][c] != 0 && !isSafe[r][c]) {
                field[r][c] = 0; 
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
            }
        }
    }
}

void Stage::ScrollDown() {
    ceilingOffset += SCROLL_STEP;

<<<<<<< HEAD
    // ‚à‚µ“Vˆä‚Ìu–_v‚âu•Çv‚Ì‰æ‘œ‚ª‚ ‚é‚È‚çA‚»‚Ì•`‰æˆÊ’u‚à‚±‚ê‚É‡‚í‚¹‚é
=======
    // ã‚‚ã—å¤©äº•ã®ã€Œæ£’ã€ã‚„ã€Œå£ã€ã®ç”»åƒãŒã‚ã‚‹ãªã‚‰ã€ãã®æç”»ä½ç½®ã‚‚ã“ã‚Œã«åˆã‚ã›ã‚‹
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0

}

void Stage::FixBubble() {
<<<<<<< HEAD
    // 1. ­‚µ–ß‚·i‚±‚ê‚ÍOKj
    shotBubble.x -= shotBubble.vx;
    shotBubble.y -= shotBubble.vy;

    // 2. s(r)‚ğŒvZ
=======
    // 1. å°‘ã—æˆ»ã™ï¼ˆã“ã‚Œã¯OKï¼‰
    shotBubble.x -= shotBubble.vx;
    shotBubble.y -= shotBubble.vy;

    // 2. è¡Œ(r)ã‚’è¨ˆç®—
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    int r = (int)((shotBubble.y - OFFSET_Y + ceilingOffset) / ROW_HEIGHT + 0.5f);

    if (shotBubble.y <= OFFSET_Y + ceilingOffset + B_RADIUS) {
        r = 0;
    }

<<<<<<< HEAD
    // “Vˆä‚æ‚èã‚És‚«‰ß‚¬‚½ê‡‚Í0s–Ú‚É‚·‚é
    if (r < 0) r = 0;
    // ’ê‚ğ“Ë‚«”²‚¯‚½ê‡‚ÍŒÅ’è‚¹‚¸‚ÉÁ‹
=======
    // å¤©äº•ã‚ˆã‚Šä¸Šã«è¡ŒãéããŸå ´åˆã¯0è¡Œç›®ã«ã™ã‚‹
    if (r < 0) r = 0;
    // åº•ã‚’çªãæŠœã‘ãŸå ´åˆã¯å›ºå®šã›ãšã«æ¶ˆå»
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    if (r >= STAGE_ROWS) {
        shotBubble.isActive = false;
        return;
    }

<<<<<<< HEAD
    // 3. —ñ(c)‚ğŒvZ
    float currentOffsetX = (r % 2 == 0) ? OFFSET_X : OFFSET_X + B_RADIUS;
    int c = (int)((shotBubble.x - currentOffsetX) / (B_RADIUS * 2) + 0.4f);

    // šd—vF—ñ(c)‚Ì”ÍˆÍŠOƒ`ƒFƒbƒN‚Æ•â³
    if (c < 0) c = 0;
    if (c >= STAGE_COLS) c = STAGE_COLS - 1;

    // ‘¦À‚ÉƒtƒB[ƒ‹ƒh‚ÉŒÅ’è‚·‚éiƒAƒjƒ[ƒVƒ‡ƒ“–³‚µj
    field[r][c] = shotBubble.color;

    // Á‹‚Æ—‰º”»’è
    ProcessErase(r, c);
    DropFloatingBubbles();

    // ’e‚ğ”ñƒAƒNƒeƒBƒu‚É‚·‚é
    shotBubble.isActive = false;

    shotCount++; // ”­Ë‰ñ”‚ğƒJƒEƒ“ƒg
    if (shotCount >= SHOT_LIMIT) {
        ScrollDown();  // “Vˆä‚ğ‰º‚°‚éŠÖ”‚ğŒÄ‚Ô
        shotCount = 0; // ƒJƒEƒ“ƒgƒŠƒZƒbƒg
=======
    // 3. åˆ—(c)ã‚’è¨ˆç®—
    float currentOffsetX = (r % 2 == 0) ? OFFSET_X : OFFSET_X + B_RADIUS;
    int c = (int)((shotBubble.x - currentOffsetX) / (B_RADIUS * 2) + 0.4f);

    // â˜…é‡è¦ï¼šåˆ—(c)ã®ç¯„å›²å¤–ãƒã‚§ãƒƒã‚¯ã¨è£œæ­£
    if (c < 0) c = 0;
    if (c >= STAGE_COLS) c = STAGE_COLS - 1;

    field[r][c] = shotBubble.color;

    // æ¶ˆå»ã¨è½ä¸‹åˆ¤å®š
    ProcessErase(r, c);
    DropFloatingBubbles();

    // å¼¾ã‚’éã‚¢ã‚¯ãƒ†ã‚£ãƒ–ã«ã™ã‚‹
    shotBubble.isActive = false;

    shotCount++; // ç™ºå°„å›æ•°ã‚’ã‚«ã‚¦ãƒ³ãƒˆ
    if (shotCount >= SHOT_LIMIT) {
        ScrollDown();  // å¤©äº•ã‚’ä¸‹ã’ã‚‹é–¢æ•°ã‚’å‘¼ã¶
        shotCount = 0; // ã‚«ã‚¦ãƒ³ãƒˆãƒªã‚»ãƒƒãƒˆ
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    }
}

void Stage::ProcessErase(int startR, int startC) {
<<<<<<< HEAD
    // 1. ‰º€”õ
=======
    // 1. ä¸‹æº–å‚™
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    eraseList.clear();
    for (int i = 0; i < STAGE_ROWS; i++)
        for (int j = 0; j < STAGE_COLS; j++) checked[i][j] = false;

<<<<<<< HEAD
    // 2. ‚Â‚È‚ª‚è‚ğ’²‚×‚é
    CheckConnect(startR, startC, field[startR][startC]);

    // 3. 3‚ÂˆÈã‚È‚ç field ‚ğ 0i‹ój‚É‚·‚é
    if (eraseList.size() >= 3) {
        for (auto p : eraseList) {
            field[p.first][p.second] = 0;
            // ‚±‚±‚ÅuŠ„‚ê‚éƒGƒtƒFƒNƒgv‚ğo‚·ƒtƒ‰ƒO‚ğ—§‚Ä‚é‚ÆÅ‚I
=======
    // 2. ã¤ãªãŒã‚Šã‚’èª¿ã¹ã‚‹
    CheckConnect(startR, startC, field[startR][startC]);

    // 3. 3ã¤ä»¥ä¸Šãªã‚‰ field ã‚’ 0ï¼ˆç©ºï¼‰ã«ã™ã‚‹
    if (eraseList.size() >= 3) {
        for (auto p : eraseList) {
            field[p.first][p.second] = 0;
            // ã“ã“ã§ã€Œå‰²ã‚Œã‚‹ã‚¨ãƒ•ã‚§ã‚¯ãƒˆã€ã‚’å‡ºã™ãƒ•ãƒ©ã‚°ã‚’ç«‹ã¦ã‚‹ã¨æœ€é«˜ï¼
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
        }
    }
}

bool isSafe[STAGE_ROWS][STAGE_COLS];




int Stage::GetX(int r, int c) {
    int x = OFFSET_X + (c * B_RADIUS * 2);
<<<<<<< HEAD
    if (r % 2 != 0) { // Šï”s‚È‚ç”¼•ª‚¸‚ç‚·
=======
    if (r % 2 != 0) { // å¥‡æ•°è¡Œãªã‚‰åŠåˆ†ãšã‚‰ã™
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
        x += B_RADIUS;
    }
    return x;
}

int Stage::GetY(int r) {
    return OFFSET_Y + ceilingOffset + (r * ROW_HEIGHT);
}

void Stage::Draw() {

    DrawGraph(0, 0, stage_1_3_image, TRUE);
<<<<<<< HEAD

=======
    
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    for (int r = 0; r < STAGE_ROWS; r++) {
        for (int c = 0; c < STAGE_COLS; c++) {
            int colorNum = field[r][c];
            if (colorNum != 0) {
                int drawX = GetX(r, c);
                int drawY = GetY(r);

<<<<<<< HEAD
                // ‰¼‚Ì‰~‚ğ•`‰æ
                // F”Ô†‚É‰‚¶‚ÄF‚ğØ‚è‘Ö‚¦‚é
                unsigned int color;
                switch (colorNum) {
                case 1: color = GetColor(255, 0, 0); break; // Ô
                case 2: color = GetColor(0, 255, 0); break; // —Î
                case 3: color = GetColor(0, 0, 255); break; // Â
                case 4: color = GetColor(255, 255, 0); break; // ‰©
                default: color = GetColor(255, 255, 255); break;
                }
                DrawCircle(drawX, drawY, B_RADIUS - 1, color, TRUE);
=======
                // ä»®ã®å††ã‚’æç”»
                // è‰²ç•ªå·ã«å¿œã˜ã¦è‰²ã‚’åˆ‡ã‚Šæ›¿ãˆã‚‹
                unsigned int color;
                switch (colorNum) {
                case 1: color = GetColor(255, 0, 0); break; // èµ¤
                case 2: color = GetColor(0, 255, 0); break; // ç·‘
                case 3: color = GetColor(0, 0, 255); break; // é’
                case 4: color = GetColor(255, 255, 0); break; // é»„
                default: color = GetColor(255, 255, 255); break;
                }
                DrawCircle(drawX, drawY, B_RADIUS-1, color, TRUE);
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
            }
        }
    }

    int ceilingImgY = (OFFSET_Y + ceilingOffset) - CEILING_IMAGE_HEIGHT;
<<<<<<< HEAD
    //DrawGraph(CEILING_OFFSET_X, ceilingImgY, ceiling_image, TRUE);

    // ƒLƒƒƒmƒ“‚ğ•`‰æ
=======
    DrawGraph(CEILING_OFFSET_X, ceilingImgY, ceiling_image, TRUE);

    // ã‚­ãƒ£ãƒãƒ³ã‚’æç”»
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    cannon.Draw();

    if (!shotBubble.isActive) {
        unsigned int cCode;
        switch (cannon.currentColor) {
        case 1: cCode = GetColor(255, 0, 0);   break;
<<<<<<< HEAD
        case 2: cCode = GetColor(0, 255, 0);   break; // ƒtƒB[ƒ‹ƒh‚Ì—Î‚Æ‡‚í‚¹‚é
=======
        case 2: cCode = GetColor(0, 255, 0);   break; // ãƒ•ã‚£ãƒ¼ãƒ«ãƒ‰ã®ç·‘ã¨åˆã‚ã›ã‚‹
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
        case 3: cCode = GetColor(0, 0, 255);   break;
        case 4: cCode = GetColor(255, 255, 0); break;
        default: cCode = GetColor(255, 255, 255); break;
        }
        DrawCircle((int)cannon.x, (int)cannon.y, B_RADIUS - 1, cCode, TRUE);
    }
<<<<<<< HEAD
    // ”ò‚ñ‚Å‚¢‚éƒoƒuƒ‹‚ğ•`‰æ
    shotBubble.Draw();

    // ƒ}ƒEƒX‚ÌÀ•W‚ğŠi”[‚·‚é•Ï”
    int mx, my;
    GetMousePoint(&mx, &my);

    // ‰æ–Ê¶ã‚ÉŒ»İ‚Ìƒ}ƒEƒXÀ•W‚ğ•\¦
=======
    // é£›ã‚“ã§ã„ã‚‹ãƒãƒ–ãƒ«ã‚’æç”»
    shotBubble.Draw();

    // ãƒã‚¦ã‚¹ã®åº§æ¨™ã‚’æ ¼ç´ã™ã‚‹å¤‰æ•°
    int mx, my;
    GetMousePoint(&mx, &my);

    // ç”»é¢å·¦ä¸Šã«ç¾åœ¨ã®ãƒã‚¦ã‚¹åº§æ¨™ã‚’è¡¨ç¤º
>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0
    DrawFormatString(0, 0, GetColor(255, 255, 255), "X=%d Y=%d", mx, my);
}

// Procedural wrappers
<<<<<<< HEAD
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

=======
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


>>>>>>> 87c477732e4cb1e60f6b3e5d81b8d61b0456bda0

