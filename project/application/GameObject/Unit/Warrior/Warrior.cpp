#include "Warrior.h"

void Warrior::Initialize(Vector2 pos) {

	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("Unit/sword/blue_ken.obj");
	TextureManager::Load("resources/Unit/sword/ken.png");
	// object生成
	BaseUnit::CreateObject("Unit/sword/blue_ken.obj", "Unit/sword/ken.png");
	object_.lock()->worldTransform.translate = { pos.x,1.0f,pos.y };
	object_.lock()->worldTransform.scale = { 0.31f,0.31f,0.31f };
	object_.lock()->color = { 1.0f,0.0f,0.0f,1.0f };
}

void Warrior::Update()
{


	// ユニット共通の更新処理
	BaseUnit::Update();

}

void Warrior::Attack()
{
}

bool Warrior::CanAttackInFront()
{
	return false;
}

bool Warrior::IsInActionRange(const GridPosition& targetPosition) const
{
	targetPosition;
	return false;
}
