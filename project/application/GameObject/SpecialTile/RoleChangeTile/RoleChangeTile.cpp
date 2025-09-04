#include <application/GameObject/SpecialTile/RoleChangeTile/RoleChangeTile.h>
#include <application/GameObject/Unit/UnitFactory.h>

void RoleChangeTile::OnUnitEnter(std::unique_ptr<BaseUnit>& unit)
{
	// ユニットがnullだったら止める
	if (!unit) return;

	// 現在のマスを保存
	GridPosition oldPosition = unit->GetGridPosition();

	// 新しいユニットを生成
	auto newUnit = UnitFactory::Create(roleName_);
	newUnit->Initialize({ (float)oldPosition.x,(float)oldPosition.z });
	newUnit->SetProjectile(unit->GetProjectile());
	newUnit->SetTileMap(unit->GetTileMap());

	unit = std::move(newUnit); // 差し替え
}
