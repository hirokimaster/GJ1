#include "TileMap.h"
#include <string>
#include <fstream>
#include <sstream>
void TileMap::LoadTile(std::vector<std::unique_ptr<TeamTile>>& teamTiles)
{
    std::ifstream file("resources/Stage/stage1.csv");
    if (!file.is_open()) {
		assert(false && "Failed to open CSV file");
    };

    std::vector<std::vector<std::string>> rawCells;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        rawCells.push_back(row);
    }

    maxRow_ = static_cast<int>(rawCells.size());
    maxCol_ = rawCells.empty() ? 0 : static_cast<int>(rawCells[0].size());

    float centerX = (maxCol_ - 1) / 2.0f;
   // float centerY = (totalRows - 1) / 2.0f;
    float tileSize = 2.0f;

 

    // 最前列のZ位置を固定（例：0.0f に固定）
    float startZ = 0.0f;

    for (int rowIndex = 0; rowIndex < maxRow_; ++rowIndex) {
        for (int colIndex = 0; colIndex < maxCol_; ++colIndex) {
            std::unique_ptr<TeamTile> teamTile = std::make_unique<TeamTile>();

            int value = std::stoi(rawCells[rowIndex][colIndex]); // CSV値取得

            // 行を逆にして手前から奥に配置
            int reversedRow = maxRow_ - 1 - rowIndex;

            Vector2 position{
                (colIndex - centerX) * tileSize,
                startZ + (reversedRow * tileSize)
            };

            teamTile->Initialize(position, value,rowIndex);
            teamTiles.push_back(std::move(teamTile));
        }
    }



}
