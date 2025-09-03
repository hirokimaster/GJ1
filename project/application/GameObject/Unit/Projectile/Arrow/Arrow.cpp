#include "Arrow.h"

void Arrow::Initialize()
{
	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("TempModel/cube.obj");
	TextureManager::Load("resources/TempTexture/white.png");
	// object生成
	Projectile::CreateObject("TempModel/cube.obj", "TempTexture/white.png");

	active_ = false; // 非アクティブ
}

void Arrow::Update()
{
	Projectile::Update();
	object_.lock()->worldTransform.translate.z += 1.0f;
}

//void Arrow::OnHit(BaseUnit* target)
//{
//	target;
//}
