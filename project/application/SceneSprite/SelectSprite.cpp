#include "SelectSprite.h"

void SelectSprite::Initialize()
{
	// 調整項目追加
	AddAdjustmentVariables();
	// 調整項目適用
	ApplyAdjustmentVariables();
	// selectのスプライト
	spriteSelectPosition_ = { 640, 260 };
	spriteSelect_.reset(Sprite::Create(TextureManager::GetTexHandle("UI/select.png"), spriteSelectPosition_));
	spriteSelect_->SetAnchorPoint({ 0.5f,0.5f });
	spriteSelect_->SetColor({ 0.3f,1.0f,1.0f,1.0f });
	spriteSelect_->SetScale({ 3.0f, 3.0f });

	spriteSpacePosition_ = { 640, 600 };
	spriteSpace_.reset(Sprite::Create(TextureManager::GetTexHandle("UI/selectUI.png"), spriteSpacePosition_));
	spriteSpace_->SetAnchorPoint({ 0.5f,0.5f });
	spriteSpace_->SetColor({ 1.0f,1.0f,1.0f,1.0f });

}

void SelectSprite::Update()
{
}

void SelectSprite::Draw()
{
	spriteSelect_->Draw();
	spriteSpace_->Draw();
}

void SelectSprite::AddAdjustmentVariables()
{
}

void SelectSprite::ApplyAdjustmentVariables()
{
	
}