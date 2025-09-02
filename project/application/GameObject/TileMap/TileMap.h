#pragma once
#include <memory>
#include <vector>
#include "application/GameObject/TeamTile/TeamTile.h"
class TileMap
{
public:
	static void LoadTile(std::vector<std::unique_ptr<TeamTile>>& teamTiles);
private:
	std::vector<std::unique_ptr<TeamTile>> tiles_;
};
