#include "TileMap.h"
#include <string>
#include <fstream>
#include <sstream>
void TileMap::LoadTile()
{
    std::ifstream file("resources/Stage/rensyu.csv");
    if (!file.is_open()) {
        assert(false && "Failed to open CSV file");
    };

    std::vector<std::vector<int>> rawCells;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<int> row;

        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stoi(cell));
        }
        rawCells.push_back(row);
    }

    maxRow_ = static_cast<int>(rawCells.size());
    maxCol_ = rawCells.empty() ? 0 : static_cast<int>(rawCells[0].size());


    float tileSize = 2.0f;
    float startZ = 0.0f;

    // 保持
    map_ = rawCells;
    tiles_.resize(maxRow_);

    for (int rowIndex = 0; rowIndex < maxRow_; ++rowIndex) {
        tiles_[rowIndex].resize(maxCol_);
        for (int colIndex = 0; colIndex < maxCol_; ++colIndex) {
            auto teamTile = std::make_unique<TeamTile>();

            int value = map_[rowIndex][colIndex];
            int reversedRow = maxRow_ - 1 - rowIndex;

            // 9番だったらロール変えタイル
            if (value == 9) {
                GridPosition pos = { colIndex, rowIndex };
                specialTiles_.push_back(std::make_unique<RoleChangeTile>(pos, "warrior"));
            }

            Vector2 position{
                colIndex * tileSize,
                startZ + (reversedRow * tileSize)
            };

            teamTile->Initialize(position, value, rowIndex);
            tiles_[rowIndex][colIndex] = std::move(teamTile);
        }
    }
}

void TileMap::Update()
{
    for (int row = 0; row < maxRow_; ++row) {
        for (int col = 0; col < maxCol_; ++col) {
            if (tiles_[row][col]) {
                tiles_[row][col]->Update();
            }
        }
    }
}

bool TileMap::IsAllBlue() const {
    for (int row = 0; row < maxRow_; ++row) {
        for (int col = 0; col < maxCol_; ++col) {
            if ((map_[row][col] != TileMode::BLUE) && (map_[row][col] != TileMode::BLUE_ARCHER) && (map_[row][col] != TileMode::BLUE_WARRIOR) && (map_[row][col] != TileMode::BLUE_SWORDSMAN)) { // 1 を青にしたなら
                return false;
            }
        }
    }
    return true;
}

bool TileMap::IsEnemyAtFrontLine() const
{
    for (int col = 0; col < maxCol_; ++col) {
        if (map_[maxRow_ - 1][col] == TileMode::RED_ARCHER || map_[maxRow_ - 1][col] == TileMode::RED_SWORDSMAN || map_[maxRow_ - 1][col] == TileMode::RED_WARRIOR) { // 敵のタイルが最前線にあるか
            return true;
        }
	}
    return false;
}

int TileMap::GetTileMap(int x, int y)
{
    if (y >= 0 && y < maxRow_ && x >= 0 && x < maxCol_) {
        return map_[y][x];
    }
    return 0; // 範囲外は0（空白）を返す
}

void TileMap::SetTileMap(int x, int y, int value)
{
    if (y >= 0 && y < maxRow_ && x >= 0 && x < maxCol_) {
        map_[y][x] = value;
        if (tiles_[y][x]) {
            tiles_[y][x]->SetTileMode(value); // TeamTile 側にも反映
        }
    }
}
