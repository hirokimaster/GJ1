#include "Player.h"
#include "engine/Input/Input.h"
#include "engine/3d/ObjectManager/ObjectManager.h"
#include "engine/3d/Model/ModelManager.h"
#include "engine/Graphics/TextureManager/TextureManager.h"
#include <application/GameObject/Unit/Projectile/ProjectilePool.h>
#include <application/GameObject/Unit/Archer/Archer.h>
void Player::Init() {
	// 調整項目
	AddAdjustmentVariables();
	ApplyAdjustmentVariables();
  
	selectedTile_ = { 0,0 }; // 初期選択タイル
	TextureManager::Load("resources/TempTexture/white2.png");
	// モデルのロード
	ModelManager::LoadObjModel("PlayerTargetTile/PlayerTargetTile.obj");
	// object共通の初期化
	BaseIndividualObject::Initialize("PlayerTargetTile/PlayerTargetTile.obj", "TempTexture/white2.png");
	object_.lock()->SetColor({ 0.0f,0.0f,0.6f,1.0f });

	// 選択してるユニットのモデル
	selectObject_ = std::make_unique<Object3dPlacer>();
	selectObject_->Initialize();
	selectObject_->SetModel("Unit/Archer/yumi.obj");
	selectObject_->SetTexHandle(TextureManager::GetTexHandle("Unit/Archer/ken.png"));
	selectObject_->SetPosition({ selectObjectPosition_ });
	selectObject_->SetScale({ 0.2f,0.2f,0.2f });
	selectObject_->SetRotate({ 0,rotateY_,0 });
}

void Player::Update() {
	std::erase_if(units_, [](const std::unique_ptr<BaseUnit>& unit) {
		return !unit->GetIsAlive();
		});
	SelectTile();
	DebugDraw();
	SelectUnit();
	RoleChange();
	selectObjectPosition_.x = camera_->translate.x - 4.0f;
	selectObject_->SetPosition(selectObjectPosition_ );
	if (Input::GetInstance()->PressedKey(DIK_P)) {
		SpawnUnit();
	}
	for (auto& unit : units_) {
		unit->Update();
		if (!unit->IsAlive()) {
			GPUParticle* particle = ParticleManager::GetInstance()->GetParticle("unitDeadParticle");
			particle->SetPosition({
				unit->GetPosition().x,
				unit->GetPosition().y + 1.0f,
				unit->GetPosition().z }
				);
			particle->SetColor(color_);
			particle->SetIsActive(true);
			particle->SetLifeTime(60);
			deadUnits_.push_back(particle);
		}
	}

	for(auto& deadUnit : deadUnits_) {
		// particleの位置
		if (deadUnit->GetIsDead()) {
			deadUnit->SetIsActive(false);
			deadUnit = nullptr;
		}
		else if(!deadUnit->GetIsDead()){
			
		}
	}

	BaseIndividualObject::Update(); // object共通の更新処理

	// 選択ユニットの回転
	rotateY_ += 0.015f;
	selectObject_->SetRotate({ 0,rotateY_,0 });
	selectObject_->Update();

}

void Player::SelectTile() {
	if (Input::GetInstance()->PressedKey(DIK_D)) {
		// 参照の外じゃなかったら
		if (tileMap_->GetMaxCol() - 1 > selectedTile_.x) {
			selectedTile_.x += 1;
		}
	}
	else if (Input::GetInstance()->PressedKey(DIK_A)) {
		// 参照の外じゃなかったら
		if (selectedTile_.x > 0) {
			selectedTile_.x -= 1;
		}
	}
	else if (Input::GetInstance()->PressedKey(DIK_W)) {
		// 参照の外じゃなかったら
		if (selectedTile_.y > 0) {
			selectedTile_.y -= 1;
		}
	}
	else if (Input::GetInstance()->PressedKey(DIK_S)) {
		// 参照の外じゃなかったら
		if (tileMap_->GetMaxRow() - 1 > selectedTile_.y) {
			selectedTile_.y += 1;
		}
	}
	MoveSelectTile();
}

void Player::MoveSelectTile()
{
	object_.lock()->SetPosition({ selectedTile_.x * 2.0f,0.0f, (tileMap_->GetMaxRow() - 1 - selectedTile_.y) * 2.0f });
}

void Player::SpawnUnit() {
	int x = (int)selectedTile_.x;
	int y = (int)selectedTile_.y;
	if (currentUnitCount_ < maxUnitCount_) {
		if (CanSpawnHere(x, y)) {
			// yを反転（TileMapの行数を知る必要がある）
			int reversedY = tileMap_->GetMaxRow() - 1 - y; // CSVの可読性を上げるために奥が0行目のため修正
			// ユニット
			std::unique_ptr<BaseUnit> unit;
			if (selectNum_ == 0) {
				unit = UnitFactory::Create("archer");
				roleId_ = TileMode::BLUE_ARCHER;
			}
			else if (selectNum_ == 1) {
				unit = UnitFactory::Create("warrior");
				roleId_ = TileMode::BLUE_WARRIOR;
			}
			else if (selectNum_ == -1) {
				unit = UnitFactory::Create("swordsman");
				roleId_ = TileMode::BLUE_SWORDSMAN;
			}

			unit->Initialize({ (float)x * 2.0f,(float)reversedY * 2.0f });
			unit->SetProjectile(projectilePool_);
			unit->SetTileMap(tileMap_);
			unit->SetGridPosition(x, y);
			unit->SetTeamId(teamId_);
			unit->SetRoleId(roleId_);
			unit->SetColor({ 0.3f,0.3f,1.0f,1.0f });
			unit->SetVelocity({ 0.0f,2.00f });
			units_.push_back(std::move(unit));
			currentUnitCount_++;
		}
		
	}

}

void Player::DrawUI(const Camera& camera)
{
	selectObject_->Draw(camera);
}

void Player::DebugDraw()
{
#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::Text("selectedTileX:%d", (int)selectedTile_.x);
	ImGui::Text("selectedTileY:%d", (int)selectedTile_.y);
	ImGui::Text("-1:swordsman, 0:archer, 1:warrior, num:%d", selectNum_);
	ImGui::End();

	ApplyAdjustmentVariables();
	selectObject_->SetPosition(selectObjectPosition_);
#endif // _DEBUG

}

bool Player::CanSpawnHere(int x, int y)
{
	int tileValue = tileMap_->GetTileMap(x, y);
	if (tileValue != teamId_) return false; // 自チームタイルでない

	for (auto& unit : units_) {
		if (unit->GetGridPosition().x == x && unit->GetGridPosition().z == y)
			return false; // すでにユニットがいる
	}
	return true;
}

void Player::SelectUnit()
{
	if (Input::GetInstance()->PressedKey(DIK_LEFT)) {
		selectNum_ -= 1;
		if (selectNum_ < -1) {
			selectNum_ = 1; // 左端を超えたら右端へ
		}
		rotateY_ = std::numbers::pi_v<float>;
	}
	else if (Input::GetInstance()->PressedKey(DIK_RIGHT)) {
		selectNum_ += 1;
		if (selectNum_ > 1) {
			selectNum_ = -1; // 右端を超えたら左端へ
		}
		rotateY_ = std::numbers::pi_v<float>;
	}

	//selectNum_ = std::clamp(selectNum_, -1, 1); // 制限しとく

	if (selectNum_ == 0) {
		selectObject_->SetModel("Unit/Archer/yumi.obj");
		selectObject_->SetTexHandle(TextureManager::GetTexHandle("Unit/Archer/ken.png"));
	}
	else if (selectNum_ == 1) {
		selectObject_->SetModel("Unit/gardian/tate.obj");
		selectObject_->SetTexHandle(TextureManager::GetTexHandle("Unit/sword/ken.png"));
	}
	else if (selectNum_ == -1) {
		selectObject_->SetModel("Unit/sword/blue_ken.obj");
		selectObject_->SetTexHandle(TextureManager::GetTexHandle("Unit/sword/ken.png"));
	}

}

void Player::RoleChange()
{
	// ロールチェンジ
	for (auto& spTile : tileMap_->GetSpecialTile()) {
		for (auto& unit : units_) {
			if (spTile->GetGridPosition().x == unit->GetGridPosition().x &&
				spTile->GetGridPosition().z == unit->GetGridPosition().z) {
				spTile->OnUnitEnter(unit);
			}
		}
	}
}

void Player::AddAdjustmentVariables()
{
	AdjustmentVariables* variables = AdjustmentVariables::GetInstance();
	const char* groupName = "Player";
	// グループを追加
	variables->CreateGroup(groupName);
	// アイテム追加
	variables->AddItem(groupName, "selectObjectPosition", selectObjectPosition_);
}

void Player::ApplyAdjustmentVariables()
{
	// jsonから読み込んだ値を適用
	AdjustmentVariables* variables = AdjustmentVariables::GetInstance();
	const char* groupName = "Player";
	selectObjectPosition_ = variables->GetValue<Vector3>(groupName, "selectObjectPosition");
}
