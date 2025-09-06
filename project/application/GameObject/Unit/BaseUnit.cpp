#include "BaseUnit.h"

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

	// そのマスに敵がいるか
	if (tileMap_->GetTileMap(selfX, targetY) != teamId_) {
		tileMap_->SetTileMap(selfX, targetY, teamId_); // 持っているteamのIdに変更
	}
}


void BaseUnit::Update() {
	BaseInstancingObject::Update(); // object共通の更新処理
}
