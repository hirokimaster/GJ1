#pragma once
#include <application/GameObject/Unit/BaseUnit.h>
#include <memory>

class ISpecialTile {
public:
	ISpecialTile() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ISpecialTile() = default;

	/// <summary>
	/// ユニットが入った時の処理
	/// </summary>
	/// <param name="unit"></param>
	virtual void OnUnitEnter(std::unique_ptr<BaseUnit>& unit) = 0;

#pragma region getter

	virtual const GridPosition GetGridPosition()const = 0;

#pragma endregion

#pragma region setter

	virtual void SetGridPosition(const GridPosition& position) = 0;

#pragma endregion

};
