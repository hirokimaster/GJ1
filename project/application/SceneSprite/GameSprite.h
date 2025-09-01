/**
* @file GameSprite.h
* @brief ゲームシーンのスプライト
* @author 仁平 琉乃
*/

#pragma once
#include "engine/2d/Sprite/Sprite.h"
#include "engine/Input/Input.h"
#include "application/GameManager/GameManager.h"

class GameScene;

class GameSprite {
public:
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

private:

	/// <summary>
	/// 調整項目の追加
	/// </summary>
	void AddAdjustmentVariables();

	/// <summary>
	/// 調整項目の適用
	/// </summary>
	void ApplyAdjustmentVariables();

private:
};

