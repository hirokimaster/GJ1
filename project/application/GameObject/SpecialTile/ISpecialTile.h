#pragma once
#include <application/GameObject/Unit/BaseUnit.h>

class ISpecialTile {
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ISpecialTile() = default;

	/// <summary>
	/// ユニットが入った時の処理
	/// </summary>
	/// <param name="unit"></param>
	virtual void OnUnitEnter(BaseUnit*& unit) = 0;

#pragma region getter

	virtual const GridPosition GetGridPosition()const = 0;

#pragma endregion

#pragma region setter

	virtual void SetGridPosition(const GridPosition& position) = 0;

#pragma endregion

};
