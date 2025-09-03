#pragma once
#include <memory>
#include <vector>
#include "application/GameObject/TeamTile/TeamTile.h"
class TileMap
{
public:
	void LoadTile(std::vector<std::unique_ptr<TeamTile>>& teamTiles);

public: // Getter
	int GetMaxRow()const { return maxRow_; }
	int GetMaxCol()const { return maxCol_; }

private:
	// 最大行数
	int maxRow_ = 0;
	// 最大列数
	int maxCol_ = 0;
};
