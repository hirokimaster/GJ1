/**
* @file Loader.h
* @brief Blenderから出力したjsonファイルの読み込み
* @author 仁平 琉乃
*/

#pragma once
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include "externals/Json/json.hpp"
#include "engine/Math/Vector3.h"
#include "engine/3d/Model/ModelManager.h"
#include <numbers>
#include "engine/3d/BaseObject/BaseInstancingObject.h"

// レベルデータ
struct LevelData {
	// オブジェクト一個分のデータ
	struct ObjectData {
		std::string fileName;
		Vector3 translate;
		Vector3 rotate;
		Vector3 scale;
		std::vector<Vector3> controlPoint;
		uint32_t eventNum;
	};
	// オブジェクトのコンテナ
	std::vector<ObjectData>objects;
};

// 前方宣言
class ObjectManager;

class Loader {
public:

	/// <summary>
	/// ロードしたデータを記録
	/// </summary>
	void Record();

#pragma region getter

	const std::map<std::string, std::vector<LevelData::ObjectData>>& GetObjectDatas() const {return objectDatas_;}

#pragma endregion


private:

	/// <summary>
	/// leveldataのロード
	/// </summary>
	/// <param name="fileName"></param>
	LevelData* Load(const std::string& fileName);

private:
	std::map<std::string, std::unique_ptr<Model>>  models_;
	std::map<std::string, std::vector<LevelData::ObjectData>> objectDatas_;
	LevelData* levelData_;
};