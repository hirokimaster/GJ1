#pragma once
#include <string>
#include <externals/Json/json.hpp>

class SharedGameData {
public: //初期化
	void Init();
private:
	SharedGameData() = default;
	~SharedGameData() = default;
	// コピーコンストラクタと代入演算子を削除
	const SharedGameData& operator=(const SharedGameData&) = delete;
public:
	static SharedGameData* GetInstance();

public: // Getter
	uint32_t GetStageId() const { return stageId; } // ステージ番号取得
	void SetStageId(uint32_t id) { stageId = id; }
	uint32_t GetMaxUnitCount() const { return maxUnitCount; } // 最大配置可能ユニット数取得

	// JSONからロード
	void LoadFromJson(const std::string& filePath);
private:


	// ステージ番号やプレイヤー共通データ
	uint32_t stageId = 0; // ステージ番号
	uint32_t maxUnitCount = 0; /// 最大配置可能ユニット数

};