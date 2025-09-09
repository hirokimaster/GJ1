#include "Shield.h"

void Shield::Initialize()
{
	// object生成
	Projectile::CreateObject("Unit/gardian/tatedake.obj", "Unit/sword/ken.png");

	object_.lock()->worldTransform.translate.x = -10.0f;
	object_.lock()->worldTransform.translate.y = 0.0f;
	object_.lock()->worldTransform.scale = { 0.31f,0.31f,0.31f };
	active_ = false; // 非アクティブ
}

void Shield::Update()
{
	object_.lock()->worldTransform.translate.z += velocity_.y;

	Projectile::Update();
}
