#pragma once
#include "engine/3d/BaseObject/BaseIndividualObject.h"
#include "application/GameObject/TileMap/TileMap.h"
#include "application/GameObject/Unit/BaseUnit.h"
#include <application/GameObject/Unit/UnitFactory.h>
class Player : BaseIndividualObject
{
public:
	void Init();
	void Update();
	void SelectTile(); // 選択

	void MoveSelectTile(); // タイル移動
	void SpawnUnit(); // ユニット出現

	void DebugDraw(); // デバッグ描画
public:
	bool CanSpawnHere(int x, int y);

public: // Setter
	void SetTileMap(TileMap* tileMap) { tileMap_ = tileMap; }

	void SetProjectilePool(ProjectilePool* ptr) { projectilePool_ = ptr; }

private:

	void SelectUnit(); // unit選択

private:
	// チーム && 役職ID
	int teamId_ = TileMode::BLUE;  
	int roleId_ = TileMode::BLUE_ARCHER;

	TileMap* tileMap_;    // マップ参照
	Vector2 selectedTile_; // 現在選択中タイル

	// 後で書き換えて
	std::vector<std::unique_ptr<BaseUnit>> units_;
	int32_t selectNum_ = 0; // unit洗濯用の番号
	ProjectilePool* projectilePool_ = nullptr;
};

