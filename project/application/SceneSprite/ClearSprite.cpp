#include "ClearSprite.h"
/**
* @file ClaerSprite.cpp
* @brief クリアシーンのスプライト
* @author 仁平 琉乃
*/

void ClearSprite::Initialize()
{
	// 調整項目追加
	AddAdjustmentVariables();
	// 調整項目適用
	ApplyAdjustmentVariables();

	// セレクトのスプライト
	spritePositionSelect_ = { 320, 540 };
	spriteReturnSelect_.reset(Sprite::Create(TextureManager::GetTexHandle("UI/backSelect.png"), spritePositionSelect_));
	spriteReturnSelect_->SetAnchorPoint({ 0.5f,0.5f });
	spriteReturnSelect_->SetColor({ 0.3f,1.0f,1.0f,1.0f });

	// 次ステージのスプライト
	spritePositionNextStage_ = { 960, 540 };
	spriteNextStage_.reset(Sprite::Create(TextureManager::GetTexHandle("UI/next.png"), spritePositionNextStage_));
	spriteNextStage_->SetAnchorPoint({ 0.5f,0.5f });
	spriteNextStage_->SetColor({ 1.0f,1.0f,0.3f,1.0f });
}

void ClearSprite::Update()
{
}

void ClearSprite::Draw()
{
	spriteReturnSelect_->Draw();
	spriteNextStage_->Draw();
}

void ClearSprite::AddAdjustmentVariables()
{
}

void ClearSprite::ApplyAdjustmentVariables()
{
}
