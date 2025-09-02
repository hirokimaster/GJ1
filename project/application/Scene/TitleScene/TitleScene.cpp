/**
* @file TitleScene.cpp
* @brief タイトルシーン
* @author 仁平 琉乃
*/

#include "TitleScene.h"

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
}

void TitleScene::Update()
{
	if (Input::GetInstance()->PressedKey(DIK_SPACE)) {
		GameManager::GetInstance()->ChangeScene("SELECT");
	}
}

void TitleScene::Draw()
{
	postEffect_->Draw();
}

void TitleScene::PostProcessDraw()
{
	postEffect_->PreDraw();
	titleSprite_->Draw();
	postEffect_->PostDraw();
}

void TitleScene::LoadTextureFile()
{
	TextureManager::Load("resources/TempTexture/white.png");
	TextureManager::Load("resources/UI/space.png");
	TextureManager::Load("resources/UI/title.png");
}
