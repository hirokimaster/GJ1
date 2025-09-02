#include "GameOverSprite.h"

void GameOverSprite::Initialize()
{
	// 調整項目追加
	AddAdjustmentVariables();
	// 調整項目適用
	ApplyAdjustmentVariables();

	// セレクトのスプライト
	spritePositionSelect_ = { 320, 540 };
	spriteReturnSelect_.reset(Sprite::Create(TextureManager::GetTexHandle("TempTexture/white.png"), spritePositionSelect_));
	spriteReturnSelect_->SetAnchorPoint({ 0.5f,0.5f });
	spriteReturnSelect_->SetColor({ 0.3f,1.0f,1.0f,1.0f });
	spriteReturnSelect_->SetScale({ 30.0f, 5.0f });

	// リトライのスプライト
	spritePositionRetry_ = { 960, 540 };
	spriteRetry_.reset(Sprite::Create(TextureManager::GetTexHandle("TempTexture/white.png"), spritePositionRetry_));
	spriteRetry_->SetAnchorPoint({ 0.5f,0.5f });
	spriteRetry_->SetColor({ 1.0f,0.3f,1.0f,1.0f });
	spriteRetry_->SetScale({ 30.0f, 5.0f });

}

void GameOverSprite::Update()
{
}

void GameOverSprite::Draw()
{
	spriteReturnSelect_->Draw();
	spriteRetry_->Draw();
}

void GameOverSprite::AddAdjustmentVariables()
{

}

void GameOverSprite::ApplyAdjustmentVariables()
{

}