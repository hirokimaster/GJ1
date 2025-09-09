#include "BaseUnit.h"

void BaseUnit::CreateObject(const std::string& modelName, const std::string& textureName)
{
	// object共通の初期化
	BaseInstancingObject::Initialize(modelName, textureName);
}

void BaseUnit::CreateHpObject()
{
	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("TempModel/cube.obj");
	TextureManager::Load("resources/TempTexture/white.png");
	hpObject_ = ObjectManager::GetInstance()->CreateInstancingObject("TempModel/cube.obj", TextureManager::GetTexHandle("TempTexture/white.png"));
	hpObject_.lock()->worldTransform.translate = { 0.0f,2.0f,0.0f };	
	hpObject_.lock()->worldTransform.scale = { static_cast<float>(hp_ / 150),0.1f,0.1f};
}

void BaseUnit::CaptureTile()
{
	// 自分のタイル座標
	int selfX = static_cast<int>(object_.lock()->worldTransform.translate.x / 2);
	int selfY = static_cast<int>(object_.lock()->worldTransform.translate.z / 2);

	int targetY = tileMap_->GetMaxRow() - 1 - selfY; // CSVの可読性を上げるために奥が0行目のため修正
	gridPosition_ = { selfX,targetY };
	// タイルの色が自分の役職IDでなかったら
	if (tileMap_->GetTileMap(selfX, targetY) != roleId_) {
		tileMap_->SetTileMap(gridPosition_.x, gridPosition_.z, roleId_); // タイルの色を変える
		// 前フレームにとったタイルの色を役職ではなく自チームにする
		if (tileMap_->GetTileMap(prevGridPosition_.x, prevGridPosition_.z) == roleId_) {
			tileMap_->SetTileMap(prevGridPosition_.x, prevGridPosition_.z, teamId_);
		}
	}
	
	prevGridPosition_ = gridPosition_;
}


void BaseUnit::Update() {
	// HP更新
	if (auto hpObj = hpObject_.lock()) {
		hpObj->worldTransform.translate = {
			object_.lock()->worldTransform.translate.x,
			object_.lock()->worldTransform.translate.y + 2.0f,
			object_.lock()->worldTransform.translate.z
		};
		hpObj->worldTransform.scale = {static_cast<float>(hp_) / 150,0.1f,0.1f };
		hpObj->worldTransform.UpdateMatrix(); // HP表示用オブジェクト更新
	}
	if (hp_ <= 0) {
		object_.lock()->isAlive = false;
		hpObject_.lock()->isAlive = false;
		weaponObject_.lock()->isAlive = false;
		// 前フレームにとったタイルの色を役職ではなく自チームにする
		if (tileMap_->GetTileMap(gridPosition_.x, gridPosition_.z) == roleId_) {
			tileMap_->SetTileMap(gridPosition_.x, gridPosition_.z, teamId_);
		}
	}

	if(weaponObject_.lock()) {
		weaponObject_.lock()->worldTransform.UpdateMatrix(); // weapon更新
	}
	BaseInstancingObject::Update(); // object共通の更新処理
}
