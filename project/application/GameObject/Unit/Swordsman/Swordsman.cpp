#include "Swordsman.h"
#include "engine/Input/Input.h"
void Swordsman::Initialize(Vector2 pos) {

	// object生成
	BaseUnit::CreateObject("Unit/sword/blue_ken.obj", "Unit/sword/ken.png");
	BaseUnit::CreateHpObject();
	object_.lock()->worldTransform.translate = { pos.x,1.0f,pos.y };
	object_.lock()->worldTransform.scale = { 0.31f,0.31f,0.31f };
	object_.lock()->color = { 1.0f,0.0f,0.0f,1.0f };
	attackVelocity_ = { 0.0f,0.1f,0.1f };
	
}

void Swordsman::Update()
{
	attackTimer_++;


#ifdef _DEBUG
	if (Input::GetInstance()->PressedKey(DIK_Y) && attackTimer_ >= 120) {
		Attack();
	}
#endif // _DEBUG


	if (CanAttackInFront()) {
		attackVelocity_.z = 1.1f;
		Attack();
		moveTimer_ = 0;
	}
	else if (CanAttackInBack()) {
		attackVelocity_.z = -0.1f;
		Attack();
		moveTimer_ = 0;
	}
	else if (!CanAttackInFront() && !CanAttackInBack()) {
		Move();
	}
	CaptureTile(); // タイル占領
	if (projectilePool_) {
		CheckAttackHit();
	}
	// ユニット共通の更新処理
	BaseUnit::Update();
}

void Swordsman::Attack()
{
	if (attackTimer_ >= 120) {
		//剣の初期化
		Projectile* baseSword = projectilePool_->Get("sword");
		// 取れたかチェックする
		if (baseSword) {
			Sword* sword = dynamic_cast<Sword*>(baseSword);
			sword->Activate(); // アクティブにする
			sword->SetPosition({
				object_.lock()->worldTransform.translate.x,
				object_.lock()->worldTransform.translate.y + 2.0f,
				object_.lock()->worldTransform.translate.z + 1.0f}); // 位置
			sword->SetTeamId(teamId_); // チームID
			sword->SetRoleId(roleId_); // 役職ID
			sword->SetVelocity(attackVelocity_); // 速度
		}
	}
	attackTimer_ = 0;
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
	int dy = 1;
	// yを反転（TileMapの行数を知る必要がある）
	int targetY = tileMap_->GetMaxRow() - 1 - selfY - dy; // CSVの可読性を上げるために奥が0行目のため修正
	// マップ外チェック
	if (targetY < 0 || targetY >= tileMap_->GetMaxRow()) {
		return false;
	}
	// そのマスに敵がいるか
	switch (teamId_) {
	case TileMode::BLUE:
		if (
			tileMap_->GetTileMap(selfX, targetY) == TileMode::RED_ARCHER ||
			tileMap_->GetTileMap(selfX, targetY) == TileMode::RED_SWORDSMAN ||
			tileMap_->GetTileMap(selfX, targetY) == TileMode::RED_WARRIOR) {
			return true;
		}
		break;

	}
	return false;
}

bool Swordsman::CanAttackInBack() {
	// 自分のタイル座標
	int selfX = static_cast<int>(object_.lock()->worldTransform.translate.x / 2);
	int selfY = static_cast<int>(object_.lock()->worldTransform.translate.z / 2);
	// 前方向に2マスまで調べる
	int dy = 1;
	// yを反転（TileMapの行数を知る必要がある）
	int targetY = tileMap_->GetMaxRow() - 1 - selfY + dy; // CSVの可読性を上げるために奥が0行目のため修正
	// マップ外チェック
	if (targetY < 0 || targetY >= tileMap_->GetMaxRow()) {
		return false;
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
				if (projectile->GetTeamId() == TileMode::RED) {
					// 死亡処理
					hp_ -= 50;
					projectile->Deactivate();
	
				}
				break;
			case RED:
				if (projectile->GetTeamId() == TileMode::BLUE) {
					// 死亡処理
					hp_ -= 50;
					projectile->Deactivate();
				}
				break;
			}
		}
	}
}
