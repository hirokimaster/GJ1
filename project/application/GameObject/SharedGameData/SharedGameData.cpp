#include "SharedGameData.h"
#include <fstream>

using json = nlohmann::json;

SharedGameData* SharedGameData::GetInstance() {
    static SharedGameData instance;
    return &instance;
}

void SharedGameData::LoadFromJson(const std::string& filePath) {
    std::ifstream ifs(filePath);
    if (!ifs.is_open()) return;

    json j;
    ifs >> j;

    stageId = j.value("stageId", 0);
    maxUnitCount = j.value("maxUnitCount", 0);
    bgmFile = j.value("bgmFile", ""); // ← 読み込み
}