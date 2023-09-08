#pragma once
#include "Novice.h"
#include "Vector2.h"

class Enemy {
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 敵発生
	/// </summary>
	void EnemyOccur();

private:
	Vector2 pos_[100]; // position
	Vector2 pos2_[100];
	float radius_ = 50.0f;
	int isAlive_[100]; // 生存フラグ
	int isAlive2_[100];
	int mousePosX_; // mouseのposition
	int mousePosY_;
	int move_[100]; // マウスで動かすフラグ
	int move2_[100];
	float speed[100]; // 落ちる速度
	float speed2[100];
	int timer_; 
	int type_;
};