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
	void SetProjectilePool(ProjectilePool* ptr) { projectilePool_ = ptr; }

private:
	
	void SelectUnit(); // unit選択
	void ChageRole();

private:
	int teamId_ = TileMode::RED;
	int roleId_ = TileMode::RED_ARCHER;
	TileMap* tileMap_ = nullptr;    // マップ参照
	Vector2 selectedTile_; // 現在選択中タイル

	// 後で書き換えて
	std::vector<std::unique_ptr<BaseUnit>> units_;
	ProjectilePool* projectilePool_ = nullptr;

	int32_t selectNum_ = 0; // unit洗濯用の番号
};
