#include "Archer.h"

void Archer::Initialize() {

	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("TempModel/cube.obj");
	TextureManager::Load("resources/TempTexture/white.png");
	// object生成
	BaseUnit::CreateObject("TempModel/cube.obj", "TempTexture/white.png");
}

void Archer::Update()
{
	// ユニット共通の更新処理
	BaseUnit::Update();
	// デバック用の移動、攻撃
	if (Input::GetInstance()->PressedKey(DIK_W)) {
		object_.lock()->worldTransform.translate.y += 1.0f;
	}

	if (Input::GetInstance()->PressedKey(DIK_R)) {
		Attack();
	}

}

void Archer::Attack()
{
	// プールから取ってくる
	Projectile* baseArrow = projectilePool_->Get("arrow");
	// 取れたかチェックする
	if (baseArrow) {
		Arrow* arrow = dynamic_cast<Arrow*>(baseArrow);
		arrow->Activate(); // アクティブにする
	}
}

bool Archer::IsInActionRange(const GridPosition& targetPosition) const
{
	int32_t dist = std::abs(gridPosition_.x - targetPosition.x) + std::abs(gridPosition_.z - targetPosition.z);
	return (dist >= minRange_ && dist <= maxRange_);
}
