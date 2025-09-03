#include "Warrior.h"

void Warrior::Initialize() {

	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("TempModel/cube.obj");
	TextureManager::Load("resources/TempTexture/white.png");
	// object生成
	BaseUnit::CreateObject("TempModel/cube.obj", "TempTexture/white.png");
}

void Warrior::Update()
{
	// ユニット共通の更新処理
	BaseUnit::Update();
}

void Warrior::Attack()
{
}
