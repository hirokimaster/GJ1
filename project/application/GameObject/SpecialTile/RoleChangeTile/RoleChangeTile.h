#pragma once
#include <application/GameObject/SpecialTile/ISpecialTile.h>
#include <application/GameObject/Unit/UnitFactory.h>

class RoleChangeTile : public ISpecialTile {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position"></param>
	/// <param name="roleName"></param>
	RoleChangeTile(const GridPosition& position, const std::string& roleName)
		:position_(position), roleName_(roleName) {
	}

	/// <summary>
	/// ユニットが来た時の処理
	/// </summary>
	/// <param name="unit"></param>
	void OnUnitEnter(BaseUnit* unit)override;

private:
	GridPosition position_{};
	std::string roleName_;
};
