#include "Archer.h"

void Archer::Initialize(Vector2 pos) {

	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("Unit/Archer/yumi.obj");
	TextureManager::Load("resources/Unit/Archer/ken.png");
	// object生成
	BaseUnit::CreateObject("Unit/Archer/yumi.obj", "Unit/Archer/ken.png");
	object_.lock()->worldTransform.translate = { pos.x,1.0f,pos.y };
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
		attackVelocity_.z = 0.1f;
		Attack();
		moveTimer_ = 0;
	}
	else if (CanAttackInBack()) {
		attackVelocity_.z = -0.1f;
		Attack();
		moveTimer_ = 0;
	}
	else if(!CanAttackInFront() || !CanAttackInBack()){
		Move();
	}
	if (projectilePool_) {
		CheckAttackHit();
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
			arrow->SetTeamId(teamId_); // チームID
			arrow->SetRoleId(roleId_); // 役職ID
			arrow->SetVelocity(attackVelocity_); // 速度
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

void Archer::CheckAttackHit()
{
	for (auto& projectile : projectilePool_->GetProjectiles()) {
		if (!projectile->GetIsActive()) continue; // 無効弾はスキップ

		GridPosition attackPos = {
			static_cast<int32_t>(projectile->GetPos().x / 2),
			static_cast<int32_t>(projectile->GetPos().z / 2)
		};
		attackPos.z = tileMap_->GetMaxRow() - 1 - attackPos.z;

		int selfX = static_cast<int>(object_.lock()->worldTransform.translate.x / 2);
		int selfY = static_cast<int>(object_.lock()->worldTransform.translate.z / 2);
		int targetY = tileMap_->GetMaxRow() - 1 - selfY;

		if (tileMap_->GetTileMap(selfX, targetY) == tileMap_->GetTileMap(attackPos.x, attackPos.z)) {
			switch (teamId_)
			{
			case BLUE:
				if (projectile->GetTeamId() == TileMode::RED) {
					// 死亡処理
					hp_ = 0;
					object_.lock()->isAlive = false;
					projectile->Deactivate();
					tileMap_->SetTileMap(selfX, targetY, teamId_); // タイルを自分のチームに変更
				}
				break;
			case RED:
				if (projectile->GetTeamId() == TileMode::BLUE) {
					// 死亡処理
					hp_ = 0;
					object_.lock()->isAlive = false;
					projectile->Deactivate();
					tileMap_->SetTileMap(selfX, targetY, teamId_); // タイルを自分のチームに変更
				}
				break;
			}
		}
	}
}
