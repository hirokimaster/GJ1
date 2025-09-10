#include "Archer.h"
#include "application/GameObject/TileMap/TileMap.h"

void Archer::Initialize(Vector2 pos) {

	// object生成
	BaseUnit::CreateObject("Unit/Archer/yumi_move2.obj", "Unit/Archer/ken.png");
	BaseUnit::CreateHpObject();
	object_.lock()->worldTransform.translate = { pos.x,1.0f,pos.y };
	object_.lock()->worldTransform.scale = { 0.3f,0.3f,0.3f };
	object_.lock()->color = { 1.0f,1.0f,1.0f,1.0f };

	// weponのmodel、テクスチャのロード
	TextureManager::Load("resources/Unit/sword/ken.png");
	// weapon生成
	weaponObject_ = ObjectManager::GetInstance()->CreateInstancingObject("Unit/Archer/yumi.obj", TextureManager::GetTexHandle("Unit/sword/ken.png"));
	weaponObject_.lock()->worldTransform.parent = &object_.lock()->worldTransform;
	weaponObject_.lock()->worldTransform.translate = { 0.0f,0.0f,0.0f };
	weaponObject_.lock()->color.w = 0.0f;


}

void Archer::Update()
{
	
	// デバック用の移動、攻撃

	shotTimer_++;
	

	if (CanAttackInFront() ) {
		weaponObject_.lock()->color.w = 1.0f;
		object_.lock()->color.w = 0.0f;
		attackVelocity_.z = 0.1f;
		Attack();
		moveTimer_ = 0;
	}
	else if (CanAttackInBack()) {
		weaponObject_.lock()->color.w = 1.0f;
		object_.lock()->color.w = 0.0f;
		attackVelocity_.z = -0.1f;
		Attack();
		moveTimer_ = 0;
	}
	else if(!CanAttackInFront() && !CanAttackInBack()){
		weaponObject_.lock()->color.w = 0.0f;
		object_.lock()->color.w = 1.0f;
		Move();
	}
	CaptureTile(); // タイル占領
	if (projectilePool_) {
		CheckAttackHit();
	}
  
	// ユニット共通の更新処理
	BaseUnit::Update();

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
			if (teamId_ == TileMode::BLUE) {
				arrow->SetPosition({
				object_.lock()->worldTransform.translate.x,
				object_.lock()->worldTransform.translate.y + 1.0f,
				object_.lock()->worldTransform.translate.z  }); // 位置
			}
			else if (teamId_ == TileMode::RED) {
				arrow->SetPosition({
				object_.lock()->worldTransform.translate.x,
				object_.lock()->worldTransform.translate.y + 1.0f,
				object_.lock()->worldTransform.translate.z}); // 位置
				arrow->SetRotate({ 0.0f,3.1415f,0.0f });
			}
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
			if(
				tileMap_->GetTileMap(selfX, targetY) == TileMode::RED_ARCHER ||
				tileMap_->GetTileMap(selfX, targetY) == TileMode::RED_SWORDSMAN ||
				tileMap_->GetTileMap(selfX, targetY) == TileMode::RED_WARRIOR) {
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
			if (
				tileMap_->GetTileMap(selfX, targetY) == TileMode::BLUE_ARCHER ||
				tileMap_->GetTileMap(selfX, targetY) == TileMode::BLUE_SWORDSMAN || 
				tileMap_->GetTileMap(selfX, targetY) == TileMode::BLUE_WARRIOR) {
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

		if (selfX == attackPos.x && targetY == attackPos.z) {
			switch (teamId_)
			{
			case BLUE:
				if (projectile->GetRoleId() == TileMode::RED_ARCHER) {
					// 死亡処理
					if (hp_ <= 50) {
						hp_ = 0;
					}
					else {
						hp_ -= 50;
					}
					projectile->Deactivate();

				}
				else if (projectile->GetRoleId() == TileMode::RED_SWORDSMAN) {
					// 死亡処理
					if (hp_ <= 50) {
						hp_ = 0;
					}
					else {
						hp_ -= 50;
					}
					projectile->Deactivate();

				}
				else if (projectile->GetRoleId() == TileMode::RED_WARRIOR) {
					// 死亡処理
					if (hp_ <= 50) {
						hp_ = 0;
					}
					else {
						hp_ -= 50;
					}
					projectile->Deactivate();

				}
				break;
			case RED:
				if (projectile->GetRoleId() == TileMode::BLUE_ARCHER) {
					// 死亡処理
					if (hp_ <= 50) {
						hp_ = 0;
					}
					else {
						hp_ -= 50;
					}
					projectile->Deactivate();

				}
				else if (projectile->GetRoleId() == TileMode::BLUE_SWORDSMAN) {
					// 死亡処理
					if (hp_ <= 50) {
						hp_ = 0;
					}
					else {
						hp_ -= 50;
					}
					projectile->Deactivate();

				}
				else if (projectile->GetRoleId() == TileMode::BLUE_WARRIOR) {
					// 死亡処理
					if (hp_ <= 50) {
						hp_ = 0;
					}
					else {
						hp_ -= 50;
					}
					projectile->Deactivate();

				}
				break;
			}
			if (hp_ <= 0) {
				hp_ = 0;
			}
		}
	}
}
