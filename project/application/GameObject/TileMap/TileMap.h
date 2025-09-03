#pragma once
#include <memory>
#include <vector>
#include "application/GameObject/TeamTile/TeamTile.h"
class TileMap
{
public:
	void LoadTile();

	void Update();

public: // Getter
	int GetMaxRow()const { return maxRow_; }
	int GetMaxCol()const { return maxCol_; }

	int GetTileMap(int x, int y);

public: // Setter
	void SetTileMap(int x, int y, int value);

private:
	// 最大行数
	int maxRow_ = 0;
	// 最大列数
	int maxCol_ = 0;
	// タイルの本体
	std::vector<std::vector<std::unique_ptr<TeamTile>>> tiles_;
	// マップデータ
	std::vector<std::vector<int>> map_;
};
