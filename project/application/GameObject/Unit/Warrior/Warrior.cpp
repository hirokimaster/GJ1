#include "Warrior.h"

void Warrior::Initialize(Vector2 pos) {

	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("TempModel/cube.obj");
	TextureManager::Load("resources/TempTexture/white.png");
	// object生成
	BaseUnit::CreateObject("TempModel/cube.obj", "TempTexture/white.png");
	object_.lock()->worldTransform.translate = { pos.x,1.5f,pos.y };
	object_.lock()->worldTransform.scale = { 0.5f,0.5f,0.5f };
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
