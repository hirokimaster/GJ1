/**
* @file GameScene.cpp
* @brief ゲームシーン
* @author 仁平 琉乃
*/

#include "GameScene.h"
#include "engine/3d/ObjectManager/ObjectManager.h"
#include "application/GameObject/TileMap/TileMap.h"
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
  
	TileMap::LoadTile(teamTiles_);
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

	for (auto& tile : teamTiles_) {
		tile->Update();
	}
	ObjectManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	postEffect_->Draw();
	ObjectManager::GetInstance()->Draw(gameCamera_->GetCamera());
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
	else if (!isGameClear && !isGameOver) {
		gameSprite_->Draw();
	}
	
	postEffect_->PostDraw();
}

void GameScene::Collision()
{
}

void GameScene::LoadTextureFile()
{
	TextureManager::Load("resources/TempTexture/white.png");
	TextureManager::Load("resources/UI/ui.png");
	TextureManager::Load("resources/UI/s.png");
}

