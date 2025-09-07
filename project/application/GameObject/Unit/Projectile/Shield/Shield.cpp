#include "Shield.h"

void Shield::Initialize()
{
	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("TempModel/cube.obj");
	TextureManager::Load("resources/TempTexture/white.png");

	// object生成
	Projectile::CreateObject("TempModel/cube.obj", "TempTexture/white.png");

	object_.lock()->worldTransform.translate.x = -10.0f;
	object_.lock()->worldTransform.translate.y = 1.0f;
	object_.lock()->worldTransform.scale = { 0.6f,0.6f,0.2f };
	active_ = false; // 非アクティブ
}

void Shield::Update()
{
	object_.lock()->worldTransform.translate.z += velocity_.y;
	Projectile::Update();
}
