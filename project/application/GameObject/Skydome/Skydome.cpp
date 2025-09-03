#include "Skydome.h"
#include "engine/3d/ObjectManager/ObjectManager.h"
#include "engine/3d/Model/ModelManager.h"
#include "engine/Graphics/TextureManager/TextureManager.h"


void Skydome::Init()
{
	TextureManager::Load("resources/TempTexture/white2.png");
	ModelManager::LoadObjModel("Skydome/skydome.obj");
	// object共通の初期化
	// object共通の初期化
	BaseIndividualObject::Initialize("Skydome/skydome.obj", "TempTexture/white2.png", ColliderType::AABB);
	object_.lock()->SetEnableLighting(false);
	object_.lock()->SetScale({ 150.0f,150.0f,150.0f });
	object_.lock()->SetColor({0.6f,0.6f,0.6f,1.0f});

}

void Skydome::Update()
{
	BaseIndividualObject::Update(); // object共通の更新処理
}
