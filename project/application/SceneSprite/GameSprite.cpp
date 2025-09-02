#include "GameSprite.h"
#include "application/Scene/GameScene/GameScene.h"
/**
* @file GameSprite.cpp
* @brief ゲームシーンのスプライト
* @author 仁平 琉乃
*/

void GameSprite::Initialize()
{
	// 調整項目追加
	AddAdjustmentVariables();
	// 調整項目適用
	ApplyAdjustmentVariables();

	gameOverSprite_ = std::make_unique<GameOverSprite>();
	gameOverSprite_->Initialize();

	gameClearSprite_ = std::make_unique<ClearSprite>();
	gameClearSprite_->Initialize();
}

void GameSprite::Update()
{
}

void GameSprite::Draw()
{
}

void GameSprite::ClearDraw()
{
	gameClearSprite_->Draw();
}

void GameSprite::GameOverDraw()
{
	gameOverSprite_->Draw();
}

void GameSprite::AddAdjustmentVariables()
{
}

void GameSprite::ApplyAdjustmentVariables()
{
}


