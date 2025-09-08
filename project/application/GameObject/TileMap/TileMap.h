#pragma once
#include <memory>
#include <vector>
#include "application/GameObject/TeamTile/TeamTile.h"
#include <application/GameObject/SpecialTile/RoleChangeTile/RoleChangeTile.h>

class TileMap
{
public:
	TileMap() {};
	~TileMap() {};


	void LoadTile();

	void Update();

public:
	bool IsAllBlue() const;
	//　敵チームが最前線まで来ているか
	bool IsEnemyAtFrontLine() const;

public: // Getter
	int GetMaxRow()const { return maxRow_; }
	int GetMaxCol()const { return maxCol_; }

	int GetTileMap(int x, int y);

	const std::vector<std::unique_ptr<ISpecialTile>>& GetSpecialTile() { return specialTiles_; }

public: // Setter
	void SetTileMap(int x, int y, int value);

private:
	// 最大行数
	int maxRow_ = 0;
	// 最大列数
	int maxCol_ = 0;
	// 青チームのタイル数
	int blueCount_ = 0;
	// タイルの本体
	std::vector<std::vector<std::unique_ptr<TeamTile>>> tiles_;
	// マップデータ
	std::vector<std::vector<int>> map_;
	// チェンジタイル
	std::vector<std::unique_ptr<ISpecialTile>> specialTiles_;
};
