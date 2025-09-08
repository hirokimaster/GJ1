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
	void OnUnitEnter(std::unique_ptr<BaseUnit>& unit)override;

#pragma region getter

	const GridPosition GetGridPosition()const { return position_; };

#pragma endregion

#pragma region setter

	void SetGridPosition(const GridPosition& position) { position_ = position; };

#pragma endregion

private:
	GridPosition position_{};
	std::string roleName_;
};
