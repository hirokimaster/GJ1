#pragma once
#include "engine/3d/BaseObject/BaseIndividualObject.h"
#include "application/GameObject/TileMap/TileMap.h"
#include "application/GameObject/Unit/BaseUnit.h"
#include <application/GameObject/Unit/UnitFactory.h>
#include <application/AdjustmentVariables/AdjustmentVariables.h>

class Player : BaseIndividualObject
{
public:
	void Init();
	void Update();
	void SelectTile(); // 選択

	void MoveSelectTile(); // タイル移動
	void SpawnUnit(); // ユニット出現

	/// <summary>
	/// playerのUI描画
	/// </summary>
	/// <param name="camera"></param>
	void DrawUI(const Camera& camera);

	void DebugDraw(); // デバッグ描画
public:
	bool CanSpawnHere(int x, int y);

	uint32_t GetMaxUnitCount() { return maxUnitCount_ - currentUnitCount_; }

public: // Setter
	void SetTileMap(TileMap* tileMap) { tileMap_ = tileMap; }

	void SetProjectilePool(ProjectilePool* ptr) { projectilePool_ = ptr; }

	void SetMaxUnitCount(uint32_t count) { maxUnitCount_ = count; }

	void SetSelectTile(const Vector2& pos) { selectedTile_ = pos; MoveSelectTile(); }

private:

	/// <summary>
	/// ユニット選択
	/// </summary>
	void SelectUnit();

	/// <summary>
	/// ロール変更
	/// </summary>
	void RoleChange();

	/// <summary>
	/// 調整項目の追加
	/// </summary>
	void AddAdjustmentVariables();

	/// <summary>
	/// 調整項目の適用
	/// </summary>
	void ApplyAdjustmentVariables();

private:
	// チーム && 役職ID
	int teamId_ = TileMode::BLUE;  
	int roleId_ = TileMode::BLUE_ARCHER;

	TileMap* tileMap_;    // マップ参照
	Vector2 selectedTile_; // 現在選択中タイル

	// 後で書き換えて
	std::vector<std::unique_ptr<BaseUnit>> units_;
	int32_t selectNum_ = 0; // unit洗濯用の番号
	ProjectilePool* projectilePool_ = nullptr;
	std::unique_ptr<Object3dPlacer> selectObject_;
	Vector3 selectObjectPosition_{};
	float rotateY_ = std::numbers::pi_v<float>;

	uint32_t maxUnitCount_ = 0; // 最大ユニット数
	uint32_t currentUnitCount_ = 0; // 現在のユニット数
};

