#include "Archer.h"

void Archer::Initialize(Vector2 pos) {

	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("Unit/Archer/blue_ken.obj");
	TextureManager::Load("resources/Unit/Archer/ken.png");
	// object生成
	BaseUnit::CreateObject("Unit/Archer/blue_ken.obj", "Unit/Archer/ken.png");
	object_.lock()->worldTransform.translate = { pos.x,1.5f,pos.y };
	object_.lock()->worldTransform.scale = { 0.3f,0.3f,0.3f };
	object_.lock()->color = { 1.0f,1.0f,1.0f,1.0f };

}

void Archer::Update()
{
	// ユニット共通の更新処理
	BaseUnit::Update();
	// デバック用の移動、攻撃

	shotTimer_++;
	
	CaptureTile(); // タイル占領
	if (CanAttackInFront() ) {
		Attack();
		moveTimer_ = 0;
	}
	else if (CanAttackInBack()) {
		moveTimer_ = 0;
	}
	else if(!CanAttackInFront() || !CanAttackInBack()){
		Move();
	}
	

}

void Archer::Attack()
{
	if (shotTimer_ >= 120) {
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
		switch (teamId_) {
		case TileMode::BLUE:
			if(tileMap_->GetTileMap(selfX, targetY) == TileMode::RED_ARCHER) {
				return true;
			}
		break;

		}
	}

	return false;
}

bool Archer::CanAttackInBack()
{
	// 自分のタイル座標
	int selfX = static_cast<int>(object_.lock()->worldTransform.translate.x / 2);
	int selfY = static_cast<int>(object_.lock()->worldTransform.translate.z / 2);

	// 前方向に2マスまで調べる
	for (int dy = 1; dy <= 2; ++dy) {
		// yを反転（TileMapの行数を知る必要がある）
		int targetY = tileMap_->GetMaxRow() - 1 - selfY + dy; // CSVの可読性を上げるために奥が0行目のため修正

		// マップ外チェック
		if (targetY < 0 || targetY >= tileMap_->GetMaxRow()) {
			continue;
		}
		// そのマスに敵がいるか
		switch (teamId_) {
		case TileMode::RED:
			if (tileMap_->GetTileMap(selfX, targetY) == TileMode::BLUE_ARCHER) {
				return true;
			}
			break;
		}
	}

	return false;
}

void Archer::Move()
{
	moveTimer_++;
	if (moveTimer_ >= 240) {
		object_.lock()->worldTransform.translate.z += velocity_.y;
		moveTimer_ = 0;
	}
}
