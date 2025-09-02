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

	spritePositionGame_ = { 320, 540 };
	spriteGame_.reset(Sprite::Create(TextureManager::GetTexHandle("UI/ui.png"), spritePositionGame_));
	spriteGame_->SetAnchorPoint({ 0.5f,0.5f });
	spriteGame_->SetColor({ 1.0f,1.0f,1.0f,1.0f });
}

void GameSprite::Update()
{
}

void GameSprite::Draw()
{
	spriteGame_->Draw();
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


