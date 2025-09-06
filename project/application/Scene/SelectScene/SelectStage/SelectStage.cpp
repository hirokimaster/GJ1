#include "SelectStage.h"

void SelectStage::Initialize(int num)
{
	myNum_ = num;

	// selectのスプライト
	spriteStagePosition_ = { 640.0f + myNum_ * 220, 360.0f };
	stageSprite_.reset(Sprite::Create(TextureManager::GetTexHandle("TempTexture/white.png"), spriteStagePosition_));
	stageSprite_->SetAnchorPoint({ 0.5f,0.5f });
	stageSprite_->SetColor({ 0.3f,1.0f,1.0f,1.0f });
	stageSprite_->SetScale({ 1.0f, 1.0f });
}

void SelectStage::Update(int num)
{
	// 自分の番号と選ばれた番号の差分
	int offsetFromCenter = myNum_ - num;

	// x座標を中央 (640.0f) からオフセット
	float baseX = 640.0f;
	float offsetX = 220.0f * offsetFromCenter;
	float posX = baseX + offsetX;

	stageSprite_->SetPosition({ posX, 464.0f });

	// 拡大縮小の加算変化量（±10.0f程度）
	float addSize = 0.0f;

	if (num == myNum_) {
		addSize = 10.0f * std::sinf(timer_); // -10.0f〜+10.0f を繰り返す
	}

	// サイズは「固定値 + 変化量」として設定
	stageSprite_->SetSize({ 100.0f + addSize, 100.0f + addSize });

	timer_ += 0.1f;

	if (timer_ > 6.283f) { // 2π ≒ 6.283
		timer_ = 0.0f;
	}
}

void SelectStage::Draw()
{
	stageSprite_->Draw();
}
