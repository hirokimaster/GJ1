#include "BaseUnit.h"
#include "application/GameObject/TileMap/TileMap.h"

void BaseUnit::CreateObject(const std::string& modelName, const std::string& textureName)
{
	// object共通の初期化
	BaseInstancingObject::Initialize(modelName, textureName);
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
	BaseInstancingObject::Update(); // object共通の更新処理
}
