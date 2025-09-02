#include "SelectSprite.h"

void SelectSprite::Initialize()
{
	// 調整項目追加
	AddAdjustmentVariables();
	// 調整項目適用
	ApplyAdjustmentVariables();
	// タイトルのスプライト
	spriteSelectPosition_ = { 640, 360 };
	spriteSelect_.reset(Sprite::Create(TextureManager::GetTexHandle("TempTexture/white.png"), spriteSelectPosition_));
	spriteSelect_->SetAnchorPoint({ 0.5f,0.5f });
	spriteSelect_->SetColor({ 0.3f,1.0f,1.0f,1.0f });
	spriteSelect_->SetScale({ 30.0f, 30.0f });

}

void SelectSprite::Update()
{
}

void SelectSprite::Draw()
{
	spriteSelect_->Draw();
}

void SelectSprite::AddAdjustmentVariables()
{
}

void SelectSprite::ApplyAdjustmentVariables()
{
	
}