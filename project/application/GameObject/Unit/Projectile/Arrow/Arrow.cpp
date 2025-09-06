#include "Arrow.h"

void Arrow::Initialize()
{
	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("Unit/Archer/Arrow/arrow.obj");
	TextureManager::Load("resources/Unit/Archer/ken.png");
	// object生成
	Projectile::CreateObject("Unit/Archer/Arrow/arrow.obj", "Unit/Archer/ken.png");

	object_.lock()->worldTransform.translate.y = 1.0f;
	object_.lock()->worldTransform.scale = { 0.4f,0.4f,0.4f };
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
