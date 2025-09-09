#include "Sword.h"

void Sword::Initialize()
{
	// object生成
	Projectile::CreateObject("Unit/sword/kendake.obj", "Unit/sword/ken.png");
	object_.lock()->worldTransform.translate.x = -10.0f;
	object_.lock()->worldTransform.translate.y = 1.0f;
	object_.lock()->worldTransform.scale = { 0.31f,0.31f,0.31f };
	active_ = false; // 非アクティブ
}

void Sword::Update()
{
	object_.lock()->worldTransform.translate.y -= velocity_.y;
	Projectile::Update();
}
