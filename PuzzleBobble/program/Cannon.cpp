#include "Cannon.h"
#include "DxLib.h"
#include "Stage.h"

extern int cannon_image;

Cannon::Cannon() : x(0), y(0), angle(CANNON_DEFAULT_DEG) {}

void Cannon::Init(float startX, float startY) {
    x = startX;
    y = startY;
    angle = CANNON_DEFAULT_DEG;
}

void Cannon::Update() {
    if (CheckHitKey(KEY_INPUT_LEFT))  angle -= CANNON_ROTATE_SPEED;
    if (CheckHitKey(KEY_INPUT_RIGHT)) angle += CANNON_ROTATE_SPEED;

    if (angle < CANNON_MIN_DEG) angle = CANNON_MIN_DEG;
    if (angle > CANNON_MAX_DEG) angle = CANNON_MAX_DEG;
}

void Cannon::Draw() {
    DrawRotaGraph((int)x, (int)y, 1.0, TO_RADIAN(angle + 90.0f), cannon_image, TRUE);
}