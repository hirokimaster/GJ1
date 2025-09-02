#include "BaseUnit.h"

void BaseUnit::CreateObject(const std::string& modelName, const std::string& textureName)
{
	// object共通の初期化
	BaseInstancingObject::Initialize(modelName, textureName);
}

void BaseUnit::Update() {
	BaseInstancingObject::Update(); // object共通の更新処理
}