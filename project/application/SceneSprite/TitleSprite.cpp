/**
* @file TitleSprite.cpp
* @brief タイトルシーンで表示するスプライトの生成
* @author 仁平 琉乃
*/

#include "TitleSprite.h"

void TitleSprite::Initialize()
{
	// 調整項目追加
	AddAdjustmentVariables();
	// 調整項目適用
	ApplyAdjustmentVariables();
	// タイトルのスプライト
	spriteTitlePosition_ = { 640, 360 };
	spriteTitle_.reset(Sprite::Create(TextureManager::GetTexHandle("TempTexture/white.png"), spriteTitlePosition_));
	spriteTitle_->SetAnchorPoint({ 0.5f,0.5f });
	spriteTitle_->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	spriteTitle_->SetScale({ 30.0f, 30.0f });

}

void TitleSprite::Update()
{
}

void TitleSprite::Draw()
{
	spriteTitle_->Draw();
}

void TitleSprite::AddAdjustmentVariables()
{
	
}

void TitleSprite::ApplyAdjustmentVariables()
{
	
}
