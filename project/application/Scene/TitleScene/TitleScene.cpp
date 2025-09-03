/**
* @file TitleScene.cpp
* @brief タイトルシーン
* @author 仁平 琉乃
*/

#include "TitleScene.h"
#include "engine/3d/ObjectManager/ObjectManager.h"
TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	// ポストエフェクト初期化
	postEffect_ = std::make_unique<PostProcess>();
	postEffect_->Initialize();

	LoadTextureFile(); // texture読み込み

	titleSprite_ = std::make_unique<TitleSprite>();
	titleSprite_->Initialize();

	// スカイドーム
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();
}

void TitleScene::Update()
{
	if (Input::GetInstance()->PressedKey(DIK_SPACE)) {
		GameManager::GetInstance()->ChangeScene("SELECT");
	}

	ObjectManager::GetInstance()->Update();
}

void TitleScene::Draw()
{

	titleSprite_->Draw();
	//ObjectManager::GetInstance()->Draw();
	//postEffect_->Draw();
}

void TitleScene::PostProcessDraw()
{
	/*postEffect_->PreDraw();
	postEffect_->PostDraw();*/
}

void TitleScene::LoadTextureFile()
{
	TextureManager::Load("resources/TempTexture/white.png");
	TextureManager::Load("resources/UI/space.png");
	TextureManager::Load("resources/UI/title.png");
}
