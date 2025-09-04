#pragma once
#include "engine/3d/BaseObject/BaseInstancingObject.h"
#include <string>
#include <application/GameObject/Unit/Projectile/ProjectilePool.h>
#include "application/GameObject/TileMap/TileMap.h"
struct GridPosition {
	int32_t x; // 横
	int32_t z;	// 奥行
};

class BaseUnit : public BaseInstancingObject {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="name"></param>
	/// <param name="hp"></param>
	/// <param name="attack"></param>
	BaseUnit(const std::string& name, uint32_t hp, uint32_t attack)
		: name_(name), hp_(hp), attack_(attack){}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseUnit() {};

	/// <summary>
	/// object生成
	/// </summary>
	/// <param name="modelName"></param>
	/// <param name="textureName"></param>
	void CreateObject(const std::string& modelName, const std::string& textureName);


	/// <summary>
	/// タイルを占領
	/// </summary>
	void CaptureTile();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize(Vector2 pos) = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 攻撃
	/// </summary>
	virtual void Attack() = 0;

	/// <summary>
	/// ダメージ食らった
	/// </summary>
	/// <param name="damage"></param>
	void TakeDamage(uint32_t damage) {
		hp_ = hp_ - damage;
	}

	/// <summary>
	/// アクションを起こす範囲
	/// </summary>
	/// <param name="targetPosition"></param>
	/// <returns></returns>
	virtual bool IsInActionRange(const GridPosition& targetPosition) const = 0;

	/// <summary>
	/// 後で消す
	/// </summary>
	/// <returns></returns>
	virtual bool CanAttackInFront() = 0;

#pragma region getter
	
	bool GetIsAlive() const { return hp_ > 0; }

	const std::string GetName() const { return name_; }

	const GridPosition GetGridPosition() const { return gridPosition_; }

	ProjectilePool* GetProjectile()const { return projectilePool_; }

	TileMap* GetTileMap()const { return tileMap_; }

#pragma endregion

#pragma region setter

	void SetGridPosition(int32_t x, int32_t z) { gridPosition_ = { x,z }; }

	void SetProjectile(ProjectilePool* ptr) { projectilePool_ = ptr; }

	void SetTileMap(TileMap* tileMap) { tileMap_ = tileMap; }

#pragma endregion

protected:
	std::string name_; // 役職の名前
	uint32_t hp_; // ライフ
	uint32_t attack_; // 攻撃力
	GridPosition gridPosition_{}; // 位置
	ProjectilePool* projectilePool_ = nullptr;
	TileMap* tileMap_ = nullptr;
};
