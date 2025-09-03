#include "SelectScene.h"

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Initialize()
{
	camera_.Initialize();
	// ポストエフェクト初期化
	postEffect_ = std::make_unique<PostProcess>();
	postEffect_->Initialize();

	LoadTextureFile(); // texture読み込み

	selectSprite_ = std::make_unique<SelectSprite>();
	selectSprite_->Initialize();

	// スカイドーム
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();
}

void SelectScene::Update()
{
	camera_.UpdateMatrix();
	if (Input::GetInstance()->PressedKey(DIK_SPACE)) {
		GameManager::GetInstance()->ChangeScene("GAME");
	}

	if (Input::GetInstance()->PressedKey(DIK_RETURN)) {
		GameManager::GetInstance()->ChangeScene("TITLE");
	}
	
	skydome_->Update();
	ObjectManager::GetInstance()->Update();
}

void SelectScene::Draw()
{
	selectSprite_->Draw();
	ObjectManager::GetInstance()->Draw(camera_);
	//postEffect_->Draw();
}

void SelectScene::PostProcessDraw()
{
	/*postEffect_->PreDraw();
	postEffect_->PostDraw();*/
}

void SelectScene::LoadTextureFile()
{
	TextureManager::Load("resources/TempTexture/white.png");
	TextureManager::Load("resources/UI/select.png");
	TextureManager::Load("resources/UI/selectUI.png");
}