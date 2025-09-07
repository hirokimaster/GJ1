#include "Sword.h"

void Sword::Initialize()
{
	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("TempModel/cube.obj");
	TextureManager::Load("resources/TempTexture/white.png");

	// object生成
	Projectile::CreateObject("TempModel/cube.obj", "TempTexture/white.png");

	object_.lock()->worldTransform.translate.x = -10.0f;
	object_.lock()->worldTransform.translate.y = 1.0f;
	object_.lock()->worldTransform.scale = { 0.4f,0.4f,0.4f };
	active_ = false; // 非アクティブ
}

void Sword::Update()
{
	object_.lock()->worldTransform.translate.z += velocity_.y;
	Projectile::Update();
}
