/**
* @file GameScene.cpp
* @brief ゲームシーン
* @author 仁平 琉乃
*/

#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	gameCamera_ = std::make_unique<GameCamera>();
	gameCamera_->Init();

	// ポストエフェクト初期化
	postEffect_ = std::make_unique<PostProcess>();
	postEffect_->Initialize();

	LoadTextureFile(); // texture読み込み

	gameSprite_ = std::make_unique<GameSprite>();
	gameSprite_->Initialize();

	isGameOver = false;
	isGameClear = false;
}

void GameScene::Update()
{
	gameCamera_->Update();

	if (Input::GetInstance()->PressedKey(DIK_G)) {
		isGameOver = true;
	}
	if (Input::GetInstance()->PressedKey(DIK_C)) {
		isGameClear = true;
	}

	if (isGameOver) {
		if (Input::GetInstance()->PressedKey(DIK_S)) {
			GameManager::GetInstance()->ChangeScene("SELECT");
		}
	}
	else if (isGameClear) {
		if (Input::GetInstance()->PressedKey(DIK_S)) {
			GameManager::GetInstance()->ChangeScene("SELECT");
		}
	}
}

void GameScene::Draw()
{
	postEffect_->Draw();
}

void GameScene::PostProcessDraw()
{
	postEffect_->PreDraw();

	if (isGameClear) {
		gameSprite_->ClearDraw();
	}
	else if (isGameOver) {
		gameSprite_->GameOverDraw();
	}
	
	postEffect_->PostDraw();
}

void GameScene::Collision()
{
}

void GameScene::LoadTextureFile()
{
	TextureManager::Load("resources/TempTexture/white.png");
}

