#include "Enemy.h"
#include "engine/Input/Input.h"
#include "engine/3d/ObjectManager/ObjectManager.h"
#include "engine/3d/Model/ModelManager.h"
#include "engine/Graphics/TextureManager/TextureManager.h"
#include <application/GameObject/Unit/Projectile/ProjectilePool.h>
#include <application/GameObject/Unit/Archer/Archer.h>

void Enemy::Init() {
	selectedTile_ = { 0,0 }; // 初期選択タイル

	SpawnUnit();
}

void Enemy::Update() {
	std::erase_if(units_, [](const std::unique_ptr<BaseUnit>& unit) {
		return !unit->GetIsAlive();
		});
	DebugDraw();
	SelectUnit();
	for (auto& unit : units_) {
		unit->Update();
	}
}

void Enemy::SpawnUnit() {
	int rows = tileMap_->GetMaxRow();
	int cols = tileMap_->GetMaxCol();

	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			if (CanSpawnHere(x, y)) {
				int value = tileMap_->GetTileMap(x, y);
				// yを反転（TileMapの行数を知る必要がある）
				int reversedY = tileMap_->GetMaxRow() - 1 - y; // CSVの可読性を上げるために奥が0行目のため修正

				switch (value) {
				case TileMode::RED_ARCHER: { // RED_ARCHER
					// ユニット
					roleId_ = TileMode::RED_ARCHER;
					std::unique_ptr<BaseUnit> unit;
					unit = UnitFactory::Create("archer");
					unit->Initialize({ (float)x * 2.0f,(float)reversedY * 2.0f });
					unit->SetRotate({0.0f,3.1415f,0.0f});
					unit->SetTileMap(tileMap_);
					unit->SetGridPosition(x, y);
					unit->SetTeamId(teamId_);
					unit->SetRoleId(roleId_);
					unit->SetColor({ 1.0f,0.3f,0.3f,1.0f });
					unit->SetVelocity({0.0f,-2.000f});
					unit->SetProjectile(projectilePool_);
					units_.push_back(std::move(unit));
					break;
				}
				case TileMode::RED_WARRIOR: { // RED_WARRIOR
					// ユニット
					roleId_ = TileMode::RED_WARRIOR;
					std::unique_ptr<BaseUnit> unit;
					unit = UnitFactory::Create("archer");
					unit->Initialize({ (float)x * 2.0f,(float)reversedY * 2.0f });
					unit->SetRotate({ 0.0f,3.1415f,0.0f });
					unit->SetTileMap(tileMap_);
					unit->SetGridPosition(x, y);
					unit->SetTeamId(teamId_);
					unit->SetRoleId(roleId_);
					unit->SetColor({ 1.0f,0.3f,0.3f,1.0f });
					unit->SetVelocity({ 0.0f,-2.000f });
					unit->SetProjectile(projectilePool_);
					units_.push_back(std::move(unit));
					break;
				}
				case TileMode::RED_SWORDSMAN: {// RED_SWORDSMAN
					// ユニット
					roleId_ = TileMode::RED_SWORDSMAN;
					std::unique_ptr<BaseUnit> unit;
					unit = UnitFactory::Create("swordsman");
					unit->Initialize({ (float)x * 2.0f,(float)reversedY * 2.0f });
					unit->SetRotate({ 0.0f,3.1415f,0.0f });
					unit->SetTileMap(tileMap_);
					unit->SetGridPosition(x, y);
					unit->SetTeamId(teamId_);
					unit->SetRoleId(roleId_);
					unit->SetColor({ 1.0f,0.3f,0.3f,1.0f });
					unit->SetVelocity({ 0.0f,-2.000f });
					unit->SetProjectile(projectilePool_);
					units_.push_back(std::move(unit));
					break;
				}
				default:
					break;
				}
			}
		}
	}
}

void Enemy::DebugDraw()
{
#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::Text("selectedTileX:%d", (int)selectedTile_.x);
	ImGui::Text("selectedTileY:%d", (int)selectedTile_.y);
	ImGui::Text("0:archer, 1:warrior, num:%d", selectNum_);
	ImGui::End();
#endif // _DEBUG

}

bool Enemy::CanSpawnHere(int x, int y)
{
	//int tileValue = tileMap_->GetTileMap(x, y);

	for (auto& unit : units_) {
		if (unit->GetGridPosition().x == x && unit->GetGridPosition().z == y)
			return false; // すでにユニットがいる
	}
	return true;
}

void Enemy::SelectUnit()
{
	if (Input::GetInstance()->PressedKey(DIK_LEFT) && selectNum_ >= 1) {
		selectNum_ -= 1;
	}
	else if (Input::GetInstance()->PressedKey(DIK_RIGHT) && selectNum_ <= 0) {
		selectNum_ += 1;
	}

	selectNum_ = std::clamp(selectNum_, -1, 1); // 制限しとく
}
