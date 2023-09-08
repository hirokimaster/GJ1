#include "Enemy.h"
#include <time.h>

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy(){}

/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize() {
	for (int i = 0; i < 10; ++i) {
		pos_[i] = {0.0f, 0.0f};
		pos2_[i] = {0.0f, 0.0f};
		move_[i] = {false};
		move2_[i] = {false};
		isAlive_[i] = {false};
		isAlive2_[i] = {false};
	}

	timer_ = 50;
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
	for (int i = 0; i < 10; ++i) {
		speed[i] = 2.0f;
		// 押してるとき動かせる
		if (Novice::IsPressMouse(0) && pos_[i].x <= mousePosX_ && pos_[i].y <= mousePosY_ &&
		    pos_[i].x + radius_ >= mousePosX_ && pos_[i].y + radius_ >= mousePosY_) {
			speed[i] = 0.0f; // 止める
			move_[i] = true;
		}

		if (Novice::IsPressMouse(0) == false) {
			move_[i] = false;
		}

		if (move_[i] && Novice::IsPressMouse(0)) {
			// マウスで動かす
			pos_[i].x = (float)mousePosX_ - radius_ / 2.0f;
			pos_[i].y = (float)mousePosY_ - radius_ / 2.0f;
		}

		if (pos_[i].x >= 1000 && pos_[i].y <= 640 && pos_[i].y >= 360) {
			speed[i] = 0.0f;
		}

			pos_[i].y += speed[i]; // 落下

		
	}

	// タイプ2
	for (int i = 0; i < 10; ++i) {
		    speed2[i] = 2.0f;
		    // 押してるとき動かせる
		    if (Novice::IsPressMouse(0) && pos2_[i].x <= mousePosX_ && pos2_[i].y <= mousePosY_ &&
		        pos2_[i].x + radius_ >= mousePosX_ && pos2_[i].y + radius_ >= mousePosY_) {
			    speed2[i] = 0.0f; // 止める
			    move2_[i] = true;
		    }

		    if (Novice::IsPressMouse(0) == false) {
			    move2_[i] = false;
		    }

		    if (move2_[i] && Novice::IsPressMouse(0)) {
			    // マウスで動かす
			    pos2_[i].x = (float)mousePosX_ - radius_ / 2.0f;
			    pos2_[i].y = (float)mousePosY_ - radius_ / 2.0f;
		    }

			if (pos2_[i].x <= 280 && pos2_[i].y <= 640 && pos2_[i].y >= 360) {
			    speed2[i] = 0.0f;
		    }

		    pos2_[i].y += speed2[i]; // 落下

		   
	}
	
}

/// <summary>
/// 描画
/// </summary>
void Enemy::Draw() { 

	Novice::DrawBox(0, 360,280, 280, 0.0f, WHITE, kFillModeSolid);
	Novice::DrawBox(1000, 360, 280, 280, 0.0f, WHITE, kFillModeSolid);

	// タイプ1
	for (int i = 0; i < 10; i++) {
		if (isAlive_[i]) {
			Novice::DrawBox((int)pos_[i].x, (int)pos_[i].y, (int)radius_, (int)radius_, 0.0f, RED, kFillModeSolid);
		}
	}

	// タイプ2
	for (int i = 0; i < 10; i++) {
		if (isAlive2_[i]) {
			Novice::DrawBox(
			    (int)pos2_[i].x, (int)pos2_[i].y, (int)radius_, (int)radius_, 0.0f, BLUE,
			    kFillModeSolid);
		}
	}
	
	/*
	// debug
	Novice::ScreenPrintf(0, 0, "Mouse X : %d", mousePosX_);
	Novice::ScreenPrintf(0, 20, "Mouse Y : %d", mousePosY_);
	*/
}

/// <summary>
/// 発生処理
/// </summary>
void Enemy::EnemyOccur() {
		
	--timer_;
	if (timer_ % 50 == 0) {
	    type_ = rand() % 2;
	    if (type_ == 0) {
		    for (int i = 0; i < 10; i++) {
			    if (isAlive_[i] == false) {
				    isAlive_[i] = true;
				    pos_[i].x = 640.0f;
				    pos_[i].y = 0;
				    break;
			    }
		    }
		} else if (type_ == 1) {
		
		    for (int i = 0; i < 10; i++) {
				if (isAlive2_[i] == false) {
					isAlive2_[i] = true;
					pos2_[i].x = 640.0f;
					pos2_[i].y = 0;
					break;
				}
			}
		
		}

		timer_ = 50;
	}

	for (int i = 0; i < 10; i++) {

		if (pos_[i].y >= 640) {
				isAlive_[i] = false;
		}
	}

	for (int i = 0; i < 10; i++) {
		
		if (pos2_[i].y >= 640) {
			isAlive2_[i] = false;
		}
		
	}

}