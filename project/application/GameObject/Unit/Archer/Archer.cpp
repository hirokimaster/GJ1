#include "Archer.h"

void Archer::Initialize(Vector2 pos) {

	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("TempModel/cube.obj");
	TextureManager::Load("resources/TempTexture/white.png");
	// object生成
	BaseUnit::CreateObject("TempModel/cube.obj", "TempTexture/white.png");
	object_.lock()->worldTransform.translate = { pos.x,1.5f,pos.y };
	object_.lock()->worldTransform.scale = { 0.5f,0.5f,0.5f };
	object_.lock()->color = { 0.7f,0.7f,1.0f,1.0f };

}

void Archer::Update()
{
	// ユニット共通の更新処理
	BaseUnit::Update();
	// デバック用の移動、攻撃
	if (Input::GetInstance()->PressedKey(DIK_W)) {
		object_.lock()->worldTransform.translate.y += 1.0f;
	}
	shotTimer_++;
	
	if (CanAttackInFront()) {
		Attack();
	}
	

}

void Archer::Attack()
{
	if (shotTimer_ >=30) {
		// プールから取ってくる
		Projectile* baseArrow = projectilePool_->Get("arrow");
		// 取れたかチェックする
		if (baseArrow) {
			Arrow* arrow = dynamic_cast<Arrow*>(baseArrow);
			arrow->Activate(); // アクティブにする
			arrow->SetPosition(object_.lock()->worldTransform.translate); // 発射位置
		}
		shotTimer_ = 0;
	}
}

bool Archer::IsInActionRange(const GridPosition& targetPosition) const
{
	int32_t dist = std::abs(gridPosition_.x - targetPosition.x) + std::abs(gridPosition_.z - targetPosition.z);
	return (dist >= minRange_ && dist <= maxRange_);
}

bool Archer::CanAttackInFront()
{
	// 自分のタイル座標
	int selfX = static_cast<int>(object_.lock()->worldTransform.translate.x / 2);
	int selfY = static_cast<int>(object_.lock()->worldTransform.translate.z / 2);

	// 前方向に2マスまで調べる
	for (int dy = 1; dy <= 2; ++dy) {
		// yを反転（TileMapの行数を知る必要がある）
		int targetY = tileMap_->GetMaxRow() - 1 - selfY - dy; // CSVの可読性を上げるために奥が0行目のため修正

		// マップ外チェック
		if (targetY < 0 || targetY >= tileMap_->GetMaxRow()) {
			continue;
		}

		// そのマスに敵がいるか
		if (tileMap_->GetTileMap(selfX, targetY) == 2) {
			return true;
		}
	}

	return false;
}
