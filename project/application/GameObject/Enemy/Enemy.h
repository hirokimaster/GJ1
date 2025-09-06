#pragma once
#include "application/GameObject/TileMap/TileMap.h"
#include <application/GameObject/Unit/UnitFactory.h>

class Enemy
{
public:
	void Init();
	void Update();

	void SpawnUnit(); // ユニット出現

	void DebugDraw(); // デバッグ描画
public:
	bool CanSpawnHere(int x, int y);

public: // Setter
	void SetTileMap(TileMap* tileMap) { tileMap_ = tileMap; }

private:

	void SelectUnit(); // unit選択

private:
	int teamId_ = TileMode::RED;
	int roleId_ = TileMode::RED_ARCHER;
	TileMap* tileMap_;    // マップ参照
	Vector2 selectedTile_; // 現在選択中タイル

	// 後で書き換えて
	std::vector<std::unique_ptr<BaseUnit>> units_;
	std::unique_ptr<ProjectilePool> projectilePool_;

	int32_t selectNum_ = 0; // unit洗濯用の番号
};
