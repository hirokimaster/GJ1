/**
* @file GameScene.cpp
* @brief ゲームシーン
* @author 仁平 琉乃
*/

#include "GameScene.h"
#include "engine/3d/ObjectManager/ObjectManager.h"

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
  
	// プール
	projectilePool_ = std::make_unique<ProjectilePool>();
	projectilePool_->Initialize();

	// ユニット
	archer_ = std::make_unique<Archer>("Archer");
	archer_->Initialize();
	archer_->SetProjectile(projectilePool_.get());

	tileMap_ = std::make_unique<TileMap>();
	tileMap_->LoadTile();

	// スカイドーム
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();

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

	if (Input::GetInstance()->PressedKey(DIK_M)) {
		if (tileMap_->GetTileMap(2, 1) == 0) {
			tileMap_->SetTileMap(2, 1, 2);
		}
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

	tileMap_->Update();

	// プール
	projectilePool_->Update();
	// ユニット
	archer_->Update();

	skydome_->Update();
  
	ObjectManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	ObjectManager::GetInstance()->Draw(gameCamera_->GetCamera());

	if (isGameClear) {
		gameSprite_->ClearDraw();
	}
	else if (isGameOver) {
		gameSprite_->GameOverDraw();
	}
	else if (!isGameClear && !isGameOver) {
		gameSprite_->Draw();
	}

	//postEffect_->Draw();
}

void GameScene::PostProcessDraw()
{
	/*postEffect_->PreDraw();
	postEffect_->PostDraw();*/
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

