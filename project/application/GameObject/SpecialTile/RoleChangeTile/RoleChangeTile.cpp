#include <application/GameObject/SpecialTile/RoleChangeTile/RoleChangeTile.h>
#include <application/GameObject/TileMap/TileMap.h>

void RoleChangeTile::OnUnitEnter(std::unique_ptr<BaseUnit>& unit)
{
	// ユニットがnullだったら止める
	if (!unit) return;

	if (active_) {

		active_ = false;

		if (unit->GetName() == "warrior") {
			roleName_ = "swordsman";
			if (unit->GetTeamId() == TileMode::BLUE) {
				roleId_ = TileMode::BLUE_SWORDSMAN;
				teamId_ = TileMode::BLUE;
			}
			else if (unit->GetTeamId() == TileMode::RED) {
				roleId_ = TileMode::RED_SWORDSMAN;
				teamId_ = TileMode::RED;
			}
		}
		else if (unit->GetName() == "swordsman") {
			roleName_ = "archer";
			if (unit->GetTeamId() == TileMode::BLUE) {
				roleId_ = TileMode::BLUE_ARCHER;
				teamId_ = TileMode::BLUE;
			}
			else if (unit->GetTeamId() == TileMode::RED) {
				roleId_ = TileMode::RED_ARCHER;
				teamId_ = TileMode::RED;
			}
		}
		else if (unit->GetName() == "archer") {
			roleName_ = "warrior";
			if (unit->GetTeamId() == TileMode::BLUE) {
				roleId_ = TileMode::BLUE_WARRIOR;
				teamId_ = TileMode::BLUE;
			}
			else if (unit->GetTeamId() == TileMode::RED) {
				roleId_ = TileMode::RED_WARRIOR;
				teamId_ = TileMode::RED;
			}
		}

		// 現在のマスを保存
		GridPosition oldPosition = unit->GetGridPosition();
		int reversedY = unit->GetTileMap()->GetMaxRow() - 1 - oldPosition.z; // CSVの可読性を上げるために奥が0行目のため修正
		// 新しいユニットを生成
		auto newUnit = UnitFactory::Create(roleName_);
		newUnit->Initialize({ oldPosition.x * 2.0f,reversedY * 2.0f });
		newUnit->SetTeamId(teamId_);
		newUnit->SetRoleId(roleId_);
		newUnit->SetGridPosition(oldPosition.x, oldPosition.z);
		newUnit->SetProjectile(unit->GetProjectile());
		newUnit->SetTileMap(unit->GetTileMap());
		if (teamId_ == TileMode::BLUE) {
			newUnit->SetColor({ 0.3f,0.3f,1.0f,1.0f });
		}
		else if (teamId_ == TileMode::RED) {
			newUnit->SetColor({ 1.0f,0.3f,0.3f,1.0f });
			newUnit->SetRotate({ 0.0f,3.1415f,0.0f });
			newUnit->SetVelocity({ 0.0f,-2.000f });
		}
		

		unit->SetIsDead();
		unit = std::move(newUnit); // 差し替え

	}
}
