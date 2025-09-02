#include "SelectScene.h"

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Initialize()
{
	// ポストエフェクト初期化
	postEffect_ = std::make_unique<PostProcess>();
	postEffect_->Initialize();

	LoadTextureFile(); // texture読み込み

	selectSprite_ = std::make_unique<SelectSprite>();
	selectSprite_->Initialize();
}

void SelectScene::Update()
{
	if (Input::GetInstance()->PressedKey(DIK_SPACE)) {
		GameManager::GetInstance()->ChangeScene("GAME");
	}

	if (Input::GetInstance()->PressedKey(DIK_RETURN)) {
		GameManager::GetInstance()->ChangeScene("TITLE");
	}
}

void SelectScene::Draw()
{
	postEffect_->Draw();
}

void SelectScene::PostProcessDraw()
{
	postEffect_->PreDraw();
	selectSprite_->Draw();
	postEffect_->PostDraw();
}

void SelectScene::LoadTextureFile()
{
	TextureManager::Load("resources/TempTexture/white.png");
}