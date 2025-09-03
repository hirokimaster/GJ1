#include "Projectile.h"


void Projectile::CreateObject(const std::string& modelName, const std::string& textureName) {
	// object共通の初期化
	BaseInstancingObject::Initialize(modelName, textureName);
}

void Projectile::Update() {
	// object共通の更新
	BaseInstancingObject::Update();
}