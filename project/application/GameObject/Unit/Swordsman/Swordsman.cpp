#include "Swordsman.h"

void Swordsman::Initialize(Vector2 pos) {

	// object生成
	BaseUnit::CreateObject("Unit/sword/blue_ken.obj", "Unit/sword/ken.png");
	object_.lock()->worldTransform.translate = { pos.x,1.0f,pos.y };
	object_.lock()->worldTransform.scale = { 0.31f,0.31f,0.31f };
	object_.lock()->color = { 1.0f,0.0f,0.0f,1.0f };
}

void Swordsman::Update()
{

	CaptureTile(); // タイル占領
	if (CanAttackInFront()) {
		attackVelocity_.z = 0.1f;
		Attack();
		moveTimer_ = 0;
	}
	else if (CanAttackInBack()) {
		attackVelocity_.z = -0.1f;
		Attack();
		moveTimer_ = 0;
	}
	else if (!CanAttackInFront() || !CanAttackInBack()) {
		Move();
	}
	if (projectilePool_) {
		CheckAttackHit();
	}
	// ユニット共通の更新処理
	BaseUnit::Update();
}

void Swordsman::Attack()
{
}

bool Swordsman::IsInActionRange(const GridPosition& targetPosition) const
{
	targetPosition;
	return false;
}
bool Swordsman::CanAttackInFront() {
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
			if (tileMap_->GetTileMap(selfX, targetY) == TileMode::RED_ARCHER) {
				return true;
			}
			break;

		}
	}

	return false;
}

bool Swordsman::CanAttackInBack() {
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

void Swordsman::Move()
{
	int selfY = static_cast<int>(object_.lock()->worldTransform.translate.z / 2);
	int targetY = tileMap_->GetMaxRow() - 1 - selfY; // CSVの可読性を上げるために奥が0行目のため修正
	moveTimer_++;
	if (moveTimer_ >= 240) {
		if (targetY < tileMap_->GetMaxRow() - 1 && teamId_ == TileMode::RED) {
			object_.lock()->worldTransform.translate.z += velocity_.y;
		}
		else if (targetY > 0 && teamId_ == TileMode::BLUE) {
			object_.lock()->worldTransform.translate.z += velocity_.y;
		}
		moveTimer_ = 0;
	}
}
void Swordsman::CheckAttackHit()
{
}
