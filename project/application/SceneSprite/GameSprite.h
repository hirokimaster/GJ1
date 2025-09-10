/**
* @file GameSprite.h
* @brief ゲームシーンのスプライト
* @author 仁平 琉乃
*/

#pragma once
#include "engine/2d/Sprite/Sprite.h"
#include "engine/Input/Input.h"
#include "application/GameManager/GameManager.h"
#include "GameOverSprite.h"
#include "ClearSprite.h"

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

	/// <summary>
	/// クリア描画
	/// </summary>
	void ClearDraw();

	/// <summary>
	/// ゲームオーバー描画
	/// </summary>
	void GameOverDraw();

	void SetNumber(int digit);

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
	std::unique_ptr<GameOverSprite> gameOverSprite_ = nullptr;
	std::unique_ptr<ClearSprite> gameClearSprite_ = nullptr;

	std::unique_ptr<Sprite> spriteGame_ = nullptr;
	Vector2 spritePositionGame_{};

	std::unique_ptr<Sprite> spriteNumGame_ = nullptr;
	Vector2 spriteNumPositionGame_{};

	std::unique_ptr<Sprite> spriteYajirusi_ = nullptr;
	Vector2 spriteYajirusiPositionGame_{};

	std::unique_ptr<Sprite> spriteSousa_ = nullptr;
	Vector2 spriteSousaPositionGame_{};

	uint32_t numHandle_ = 0;
};

