#include "TileMap.h"
#include <string>
#include <fstream>
#include <sstream>
void TileMap::LoadTile(std::vector<std::unique_ptr<TeamTile>>& teamTiles)
{
    std::ifstream file("resources/Stage/rensyu.csv");
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

    int totalRows = static_cast<int>(rawCells.size());
    int totalCols = rawCells.empty() ? 0 : static_cast<int>(rawCells[0].size());

    float centerX = (totalCols - 1) / 2.0f;
   // float centerY = (totalRows - 1) / 2.0f;
    float tileSize = 2.0f;

 

    // 最前列のZ位置を固定（例：0.0f に固定）
    float startZ = 0.0f;

    for (int rowIndex = 0; rowIndex < totalRows; ++rowIndex) {
        for (int colIndex = 0; colIndex < totalCols; ++colIndex) {
            std::unique_ptr<TeamTile> teamTile = std::make_unique<TeamTile>();

            Vector2 position{
                (colIndex - centerX) * tileSize,
                startZ + (rowIndex * tileSize)  // 手前から奥に向かって増加
            };

            teamTile->Initialize(position);
            teamTiles.push_back(std::move(teamTile));
        }
    }



}
