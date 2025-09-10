#pragma once

#include "engine/2d/Sprite/Sprite.h"
#include "application/AdjustmentVariables/AdjustmentVariables.h"

class GameOverSprite {
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
	std::unique_ptr<Sprite> spriteReturnSelect_ = nullptr;
	Vector2 spritePositionSelect_{};

	std::unique_ptr<Sprite> spriteRetry_ = nullptr;
	Vector2 spritePositionRetry_{};
};