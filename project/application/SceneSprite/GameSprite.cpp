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
	//AddAdjustmentVariables();
	// 調整項目適用
	//ApplyAdjustmentVariables();

	gameOverSprite_ = std::make_unique<GameOverSprite>();
	gameOverSprite_->Initialize();

	gameClearSprite_ = std::make_unique<ClearSprite>();
	gameClearSprite_->Initialize();

	spritePositionGame_ = { 150, 340 };
	spriteGame_.reset(Sprite::Create(TextureManager::GetTexHandle("UI/haiti.png"), spritePositionGame_));
	spriteGame_->SetAnchorPoint({ 0.5f,0.5f });
	spriteGame_->SetColor({ 1.0f,1.0f,1.0f,1.0f });

	spriteNumPositionGame_ = { 135, 340 };
	numHandle_ = TextureManager::GetTexHandle("UI/num.png");
	spriteNumGame_.reset(Sprite::Create(numHandle_, spriteNumPositionGame_));
	spriteNumGame_->SetAnchorPoint({ 0.5f,0.5f });
	spriteNumGame_->SetColor({ 1.0f,1.0f,1.0f,1.0f });

	spriteYajirusiPositionGame_ = { 135, 540 };
	spriteYajirusi_.reset(Sprite::Create(TextureManager::GetTexHandle("UI/yazirusi.png"), spriteYajirusiPositionGame_));
	spriteYajirusi_->SetAnchorPoint({ 0.5f,0.5f });
	spriteYajirusi_->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	spriteYajirusi_->SetScale({1.3f, 1.3f});

	spriteSousaPositionGame_ = { 210, 100 };
	spriteSousa_.reset(Sprite::Create(TextureManager::GetTexHandle("UI/sousa.png"), spriteSousaPositionGame_));
	spriteSousa_->SetAnchorPoint({ 0.5f,0.5f });
	spriteSousa_->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	spriteSousa_->SetScale({ 0.6f, 0.6f });

	// 初期値は「0」
	SetNumber(4);
}

void GameSprite::Update()
{
}

void GameSprite::Draw()
{
	spriteGame_->Draw();
	spriteNumGame_->Draw();
	spriteYajirusi_->Draw();
	spriteSousa_->Draw();
}

void GameSprite::ClearDraw()
{
	gameClearSprite_->Draw();
}

void GameSprite::GameOverDraw()
{
	gameOverSprite_->Draw();
}

void GameSprite::SetNumber(int digit)
{
	// テクスチャ全体サイズを取得
	float texWidth = 553.0f;
	float texHeight = 68.0f;

	float digitWidth = texWidth / 10.0f;   // 55.3
	float digitHeight = texHeight;         // 68

	// 小数切り捨てで整数に
	int dWidth = static_cast<int>(digitWidth);   // 55
	int dHeight = static_cast<int>(digitHeight); // 68

	// 切り出し範囲（UV用）は小数のまま
	float left = digit * digitWidth;
	Vector2 leftTop(left, 0.0f);
	Vector2 size(digitWidth, digitHeight);

	// UV用
	spriteNumGame_->SetTextureLeftTop(leftTop);
	spriteNumGame_->SetTextureSize(size);

	// 実際に描画するサイズは整数化
	spriteNumGame_->SetSize({ (float)dWidth, (float)dHeight });

}

void GameSprite::AddAdjustmentVariables()
{
}

void GameSprite::ApplyAdjustmentVariables()
{
}


