#include "Warrior.h"
#include "application/GameObject/TileMap/TileMap.h"
#include "engine/Input/Input.h"
#include "application/GameSound/GameSound.h"
void Warrior::Initialize(Vector2 pos) {
	TextureManager::Load("resources/Unit/Archer/ken.png");
	// object生成
	BaseUnit::CreateObject("Unit/gardian/hito.obj", "Unit/sword/ken.png");
	BaseUnit::CreateHpObject();
	object_.lock()->worldTransform.translate = { pos.x,1.0f,pos.y };
	object_.lock()->worldTransform.scale = { 0.31f,0.31f,0.31f };
	object_.lock()->color = { 1.0f,0.0f,0.0f,1.0f };
	attackVelocity_ = { 0.0f,0.1f,0.1f };

	// weponのmodel、テクスチャのロード
	moveVelo = 1;
	// weapon生成
	weaponObject_ = ObjectManager::GetInstance()->CreateInstancingObject("Unit/gardian/tatedake.obj", TextureManager::GetTexHandle("Unit/sword/ken.png"));
	weaponObject_.lock()->worldTransform.parent = &object_.lock()->worldTransform;
	weaponObject_.lock()->worldTransform.translate = { 0.0f,3.0f,2.0f };

}

void Warrior::Update()
{
	attackTimer_++;
	

#ifdef _DEBUG
	if (Input::GetInstance()->PressedKey(DIK_Y) && attackTimer_ >= 120) {
		Attack();
		isAttack_ = true;
	}
	ImGui::Begin("swordsman");
	ImGui::DragFloat3("translate,", &weaponObject_.lock()->worldTransform.translate.x);
	ImGui::End();
#endif // _DEBUG

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
	else if (!CanAttackInFront() && !CanAttackInBack()) {
		Move();
	}
	CaptureTile(); // タイル占領
	if (projectilePool_) {
		CheckAttackHit();
	}
	// 攻撃中は透明、非攻撃中は不透明
	if (isAttack_) {
		weaponObject_.lock()->color.w = 0.0f;
	}
	else if (!isAttack_) {
		weaponObject_.lock()->color.w = 1.0f;

	}
	// ユニット共通の更新処理
	BaseUnit::Update();
}

void Warrior::Attack()
{


	if (attackTimer_ >= 120) {
		// プールから取ってくる
		Projectile* baseShield = projectilePool_->Get("shield");
		// 取れたかチェックする
		if (baseShield) {
			Shield* shield = dynamic_cast<Shield*>(baseShield);
			shield->Activate(); // アクティブにする
			
			if (teamId_ == TileMode::BLUE) {
				shield->SetPosition({
				object_.lock()->worldTransform.translate.x,
				object_.lock()->worldTransform.translate.y + 1.0f,
				object_.lock()->worldTransform.translate.z + 0.5f }); // 位置
			}
			else if (teamId_ == TileMode::RED) {
				shield->SetPosition({
				object_.lock()->worldTransform.translate.x,
				object_.lock()->worldTransform.translate.y + 1.0f,
				object_.lock()->worldTransform.translate.z - 0.5f }); // 位置
				shield->SetRotate({ 0.0f,3.1415f,0.0f });
			}
			shield->SetColor(object_.lock()->color); // 色
			shield->SetTeamId(teamId_); // チームID
			shield->SetRoleId(roleId_); // 役職ID
			shield->SetVelocity(attackVelocity_); // 速度
			GameSound::SoundPlaySE("shield");
	
		}
		attackTimer_ = 0;
	}


}

bool Warrior::IsInActionRange(const GridPosition& targetPosition) const
{
	targetPosition;
	return false;
}
bool Warrior::CanAttackInFront() {
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

bool Warrior::CanAttackInBack() {
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

void Warrior::Move()
{
	int selfY = static_cast<int>(object_.lock()->worldTransform.translate.z / 2);
	int targetY = tileMap_->GetMaxRow() - 1 - selfY; // CSVの可読性を上げるために奥が0行目のため修正
	moveTimer_+= moveVelo;
	if (moveTimer_ >= 420) {
		if (targetY < tileMap_->GetMaxRow() - 1 && teamId_ == TileMode::RED) {
			object_.lock()->worldTransform.translate.z += velocity_.y;
		}
		else if (targetY > 0 && teamId_ == TileMode::BLUE) {
			object_.lock()->worldTransform.translate.z += velocity_.y;
		}
		moveVelo = 4 ;
		moveTimer_ = 0;
	}
}
void Warrior::CheckAttackHit()
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
					if (hp_ <= 10) {
						hp_ = 0;
					}
					else {
						hp_ -= 10;
					}
					GameSound::SoundPlaySE("shotHit");
					projectile->Deactivate();

				}
				else if (projectile->GetRoleId() == TileMode::RED_SWORDSMAN) {
					// 死亡処理
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
					if (hp_ <= 10) {
						hp_ = 0;
					}
					else {
						hp_ -= 10;
					}
					GameSound::SoundPlaySE("shotHit");
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
			

		}
	}
}
