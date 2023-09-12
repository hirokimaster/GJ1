#include "Enemy.h"
#include "Novice.h"
#include <time.h>

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy() {}

/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize() {
	for (int i = 0; i < 100; ++i) {
		pos_[i] = {0.0f, 0.0f};
		pos2_[i] = {0.0f, 0.0f};
		move_[i] = {false};
		move2_[i] = {false};
		isAlive_[i] = {false};
		isAlive2_[i] = {false};

		EnemyStopTimer_[i] = {20};
		EnemyStop_[i] = {false};
	}

	speed = 2.0f;
	speed2 = 2.0f;

	Point_ = 0;
	timer_ = 80;
	Life_ = 4;
	Catch_ = 0;

}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update() {

	// 発生
	EnemyOccur();

	// マウスの位置を取得
	Novice::GetMousePosition(&mousePosX_, &mousePosY_);

	// タイプ1
	for (int i = 0; i < 100; ++i) {

		if (isAlive_[i] == false) {
			pos_[i].y = -50;
		}

		// 押してるとき動かせる
		if (Novice::IsPressMouse(0) && pos_[i].x <= mousePosX_ && pos_[i].y <= mousePosY_ &&
		    pos_[i].x + radius_ >= mousePosX_ && pos_[i].y + radius_ >= mousePosY_ &&
		    move_[i] == false) {
			move_[i] = true;
			Catch_ = true;
		}

		if (Novice::IsPressMouse(0) == false) {
			move_[i] = false;
			Catch_ = false;
		}

		if (move_[i] && Novice::IsPressMouse(0)) {
			// マウスで動かす
			pos_[i].x = (float)mousePosX_ - radius_ / 2.0f;
			pos_[i].y = (float)mousePosY_ - radius_ / 2.0f;
		}

		if (pos_[i].x >= 1000 && pos_[i].y <= 640 && pos_[i].y >= 360) {
			// speed = 0.0f;

			if (isAlive_[i]) {
				isAlive_[i] = false;

				if (isAlive_[i] == false) {
					Point_ += 1;
					speed += 0.2f;
					speed2 += 0.2f;
				}
			}
		}

		pos_[i].y += speed; // 落下
	}

	// タイプ2
	for (int i = 0; i < 100; ++i) {

		if (isAlive2_[i] == false) {
			pos2_[i].y = -50;
		}

		// 押してるとき動かせる
		if (Novice::IsPressMouse(0) && pos2_[i].x <= mousePosX_ && pos2_[i].y <= mousePosY_ &&
		    pos2_[i].x + radius_ >= mousePosX_ && pos2_[i].y + radius_ >= mousePosY_ &&
		    move2_[i] == false) {
			// speed2 = 0.0f; // 止める
			move2_[i] = true;
			Catch_ = true;
		}

		if (Novice::IsPressMouse(0) == false) {
			move2_[i] = false;
			Catch_ = false;
		}

		if (move2_[i] && Novice::IsPressMouse(0)) {
			// マウスで動かす
			pos2_[i].x = (float)mousePosX_ - radius_ / 2.0f;
			pos2_[i].y = (float)mousePosY_ - radius_ / 2.0f;
		}

		if (pos2_[i].x <= 280 && pos2_[i].y <= 640 && pos2_[i].y >= 360) {
			// speed2 = 0.0f;

			if (isAlive2_[i]) {
				isAlive2_[i] = false;

				if (isAlive2_[i] == false) {
					Point_ += 1;
					speed += 0.2f;
					speed2 += 0.2f;
				}
			}
		}

		pos2_[i].y += speed2; // 落下
	}
}

/// <summary>
/// 描画
/// </summary>
void Enemy::Draw() {

	if (Life_ == 4) {
		Novice::DrawSprite(0, 0, game, 1.0f, 1.0f, 0.0f, WHITE);
	} else if (Life_ == 3) {
		Novice::DrawSprite(0, 0, game1, 1.0f, 1.0f, 0.0f, WHITE);
	} else if (Life_ == 2) {
		Novice::DrawSprite(0, 0, game2, 1.0f, 1.0f, 0.0f, WHITE);
	} else if (Life_ == 1) {
		Novice::DrawSprite(0, 0, game3, 1.0f, 1.0f, 0.0f, WHITE);
	}

	// タイプ1
	for (int i = 0; i < 100; i++) {
		if (isAlive_[i]) {
			Novice::DrawSprite(
			    (int)pos_[i].x, (int)pos_[i].y, bomA, 2.0f, 2.0f,0.0f,WHITE);
		}
	}

	// タイプ2
	for (int i = 0; i < 100; i++) {
		if (isAlive2_[i]) {
			Novice::DrawSprite((int)pos2_[i].x, (int)pos2_[i].y, bomB, 2.0f, 2.0f, 0.0f, WHITE);
		}
	}

	Novice::ScreenPrintf(0, 40, "point : %d", Point_);
}

/// <summary>
/// 発生処理
/// </summary>
void Enemy::EnemyOccur() {

	--timer_;
	if (timer_ % 70 == 0) {
		type_ = rand() % 2;
		if (type_ == 0) {
			for (int i = 0; i < 100; i++) {
				if (isAlive_[i] == false) {
					isAlive_[i] = true;
					pos_[i].x = 600.0f;
					pos_[i].y = 50;
					break;
				}
			}
		} else if (type_ == 1) {

			for (int i = 0; i < 100; i++) {
				if (isAlive2_[i] == false) {
					isAlive2_[i] = true;
					pos2_[i].x = 600.0f;
					pos2_[i].y = 50;
					break;
				}
			}
		}

		timer_ = 70;
	}

	for (int i = 0; i < 100; i++) {

		if (pos_[i].y >= 640 && Catch_ == false) {
			isAlive_[i] = false;
			Life_--;
		}
	}

	for (int i = 0; i < 100; i++) {

		if (pos2_[i].y >= 640 && Catch_ == false) {
			isAlive2_[i] = false;
			Life_--;
		}
	}
}

/// <summary>
/// UI
/// </summary>

void Enemy::DrawUI() { 
	for (int i = 0; i < Life_; ++i) {
		if (i == 0) {
			Novice::DrawSprite(960, 20, life, 1.0f, 1.0f, 0.0f, WHITE);
		} else if (i == 1) {
			Novice::DrawSprite(1040, 20, life, 1.0f, 1.0f, 0.0f, WHITE);
		} else if (i == 2) {
			Novice::DrawSprite(1120, 20, life, 1.0f, 1.0f, 0.0f, WHITE);
		} else{
			Novice::DrawSprite(1200, 20, life, 1.0f, 1.0f, 0.0f, WHITE);
		}
	}

	Novice::DrawSprite(10, 10, score, 1.0f, 1.0f, 0.0f, WHITE);

	int eachNumber[3] = {};
	int number = Point_;
	int keta = 100;
	for (int i = 0; i < 3; i++) {
		eachNumber[i] = number / keta;
		number = number % keta;
		keta = keta / 10;
	}

	// 描画
	for (int i = 0; i < 3; i++) {
		Novice::DrawQuad(i * 26 + 200, 0, i * 26 + 32 + 200, 0, i * 26 + 200, 64, i * 26 + 32 + 200, 64, eachNumber[i] * 32 , 0, 32, 64, num, WHITE);
	}

	

}