#include "Player.h"
#include "engine/Input/Input.h"
#include "engine/3d/ObjectManager/ObjectManager.h"
#include "engine/3d/Model/ModelManager.h"
#include "engine/Graphics/TextureManager/TextureManager.h"
#include <application/GameObject/Unit/Projectile/ProjectilePool.h>
#include <application/GameObject/Unit/Archer/Archer.h>
void Player::Init() {
	selectedTile_ = {0,0}; // 初期選択タイル
	TextureManager::Load("resources/TempTexture/white2.png");
	ModelManager::LoadObjModel("PlayerTargetTile/PlayerTargetTile.obj");
	// object共通の初期化
	BaseIndividualObject::Initialize("PlayerTargetTile/PlayerTargetTile.obj", "TempTexture/white2.png");
	object_.lock()->SetColor({ 0.0f,0.0f,0.6f,1.0f });
}

void Player::Update() {
	SelectTile();
	DebugDraw();
	SelectUnit();
	if (Input::GetInstance()->PressedKey(DIK_P)) {
		SpawnUnit();
	}
	for(auto & unit: units_){
		unit->Update();
	}
	
	BaseIndividualObject::Update(); // object共通の更新処理
}

void Player::SelectTile() {
	if (Input::GetInstance()->PressedKey(DIK_D)) {
		// 参照の外じゃなかったら
		if (tileMap_->GetMaxCol() - 1> selectedTile_.x) {
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
		if (tileMap_->GetMaxRow() -1 > selectedTile_.y) {
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
    if (CanSpawnHere(x, y)) {
		// yを反転（TileMapの行数を知る必要がある）
		int reversedY = tileMap_->GetMaxRow() - 1 - y; // CSVの可読性を上げるために奥が0行目のため修正

		// ユニット
		std::unique_ptr<BaseUnit> unit;
		if (selectNum_ == 0) {
			unit = UnitFactory::Create("archer");
		}
		else if (selectNum_ == 1) {
			unit = UnitFactory::Create("warrior");
		}
	
		unit->Initialize({ (float)x * 2.0f,(float)reversedY * 2.0f });
		unit->SetProjectile(projectilePool_);
		unit->SetTileMap(tileMap_);
		unit->SetGridPosition(x, y);
		units_.push_back(std::move(unit));
    }
}

void Player::DebugDraw()
{
#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::Text("selectedTileX:%d", (int)selectedTile_.x);
	ImGui::Text("selectedTileY:%d", (int)selectedTile_.y);
	ImGui::Text("0:archer, 1:warrior, num:%d", selectNum_);
	ImGui::End();
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
	if (Input::GetInstance()->PressedKey(DIK_LEFT) && selectNum_ >= 1) {
		selectNum_ -= 1;
	}
	else if (Input::GetInstance()->PressedKey(DIK_RIGHT) && selectNum_ <= 0) {
		selectNum_ += 1;
	}

	selectNum_ = std::clamp(selectNum_, -1, 1); // 制限しとく
}
