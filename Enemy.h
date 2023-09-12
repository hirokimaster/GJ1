#pragma once
#include "Novice.h"
#include "Sprite.h"
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

	/// <summary>
	/// UI
	/// </summary>
	void DrawUI();

	int Life_;

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
	float speed; // 落ちる速度
	float speed2;
	int timer_;
	int type_;
	int EnemyStopTimer_[100];
	int EnemyStop_[100];
	int EnemyStopTimer2_[100];
	int EnemyStop2_[100];
	int Point_;
	int Catch_;
	// int Catch_;
	int bomB = Novice::LoadTexture("bomB.png");
	int bomA = Novice::LoadTexture("bomA.png");
	int game = Novice::LoadTexture("BG.png");
	int game1 = Novice::LoadTexture("BG1.png");
	int game2 = Novice::LoadTexture("BG2.png");
	int game3 = Novice::LoadTexture("BG3.png");
	int life = Novice::LoadTexture("Life.png");
	int num = Novice::LoadTexture("number.png");
	int score = Novice::LoadTexture("score1.png");

};