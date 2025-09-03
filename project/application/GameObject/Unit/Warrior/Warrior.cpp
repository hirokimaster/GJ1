#include "Warrior.h"

void Warrior::Initialize(Vector2 pos) {

	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("TempModel/cube.obj");
	TextureManager::Load("resources/TempTexture/white.png");
	// object生成
	BaseUnit::CreateObject("TempModel/cube.obj", "TempTexture/white.png");
	object_.lock()->worldTransform.translate = { pos.x,0.0f,pos.y };
}

void Warrior::Update()
{
	// ユニット共通の更新処理
	BaseUnit::Update();
}

void Warrior::Attack()
{
}
